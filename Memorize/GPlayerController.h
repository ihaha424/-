#pragma once
#include "../D2DGameEngine/PlayerController.h"
#include "../D2DGameEngine/Debug.h"
#include "Skill.h"

class GPlayerController : public PlayerController
{
	LOG_REGISTER_OBJ(GPlayerController)
	Math::Vector2 destPos;

	//���� �ߵ����� ��ų
	class Skill* nowSkill = nullptr;

	//��ų �ν��Ͻ� �� 
	using SkillRegistry = std::unordered_multimap<std::type_index, class Skill*>;
	SkillRegistry skills;


public:
	GPlayerController(class World* _world);
	virtual void SetupInputComponent() override;

	/**
	 * @brief ������ ��ų�� ���
	 * @tparam T : Skill ��ӹ��� Ŭ����
	 */
	template <typename T>
	void StartSkill();

	/**
	 * @brief ���� �ߵ����� ��ų�� �����ϴ�. 
	 */
	void EndSkill();

	virtual void BeginPlay() override;
	virtual void Update(float _dt) override;

	void MovePlayer();
};

template<typename T>
inline void GPlayerController::StartSkill()
{
	if (nowSkill) return;
	auto range = skills.equal_range(std::type_index(typeid(T)));
	if (range.first != skills.end()) {
		nowSkill = range.first->second;
		nowSkill->UseSkill();
	}
}
