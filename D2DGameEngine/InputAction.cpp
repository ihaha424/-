#include "framework.h"
#include "InputAction.h"

InputAction* InputAction::pInstance = nullptr;
InputAction* InputAction::GetInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new InputAction();
	}
	return pInstance;
}
void InputAction::DestroyInputAction()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void InputAction::Update(const float& deltaTime)
{
	CommandStream.clear();
	TapCommandStream.clear();

	//CommandStream.push_back();

	//��ǲ�� �� 0.2�� ���� �ʱ�ȭ Ű���ָ鼭 Tap -> �ʱ�ȭ Tap ->�ʱ�ȭ �ݺ��ϸ� �ɵ�? ���Ҹ��� �ù�
	StreamTime += deltaTime;
	for (int i = 0; i < InputSize; i++)
	{
		if (CurState[i])
		{
			if (PreveState[i])
				CommandStream.push_back(i);		//Hold�� �׳� �߰�
			else
				TapCommandStream.push_back(i);	//KeyDown
		}
		else
			if (PreveState[i])
				InvokeFunction(i, KeyUp);		//KeyUp�� �ٷ� ���� ���Ŵϱ�?
	}

	// KeyDown(Tap) ����
	int CommandStreamSize = CommandStream.size();
	for (auto tapKey : TapCommandStream)
	{
		CommandNode* curNode = &HeadNode;
		std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(tapKey);
		if (it == curNode->NextCommandNode.end())
		{
			continue; //Tap�� �Է��� ���ٴ� ��.
		}
		curNode = it->second;
		std::vector<int> TapCommandList;
		TapCommandList.push_back(tapKey);
		if (FindHoldCommand(curNode, TapCommandList, CommandStreamSize))
			InvokeFunction(TapCommandList, KeyDown);
	}

	// KeyHold ����
	for (auto holdKey : CommandStream)
		InvokeFunction(holdKey, KeyHold);

	//�������� �Ѱܼ� �ʱ�ȭ ��Ű�� ���� Update�� ������ �� && ó��
	memmove(PreveState, CurState, InputSize);
	memset(CurState, 0, InputSize);
}

// -> CommandNode�� CurState�� ���ȴ��� üũ�ϸ� �ξ� ���� �����ѵ�???? �� ��¥ �ʹ� �ʰ� �ƴ޾Ҵ�.
// ���� �����ִ� Ű�� �޾Ƽ� Ȯ�� �� �ʿ���� ���� ��尡 �����ִ��� Ȯ���ϸ�...? -> �ٵ� �� ��쿡���¸� ��� �ʿ� �� ������Ʈ�ؾ��ϴ� ������ �ֱ�� ��.
// �� �ϸ� �ɰ� ���⵵ ������ �Ⱒ
bool InputAction::FindHoldCommand(CommandNode*& curNode, std::vector<int>& TapCommandList, int size)
{
	CommandNode* tempNode = curNode;
	std::map<int, bool> CheckRepeate;
	for (auto n : TapCommandList)
		CheckRepeate[n] = true;
	for (int i = 0; i < size; i++)
	{
		if (CheckRepeate[CommandStream[i]]) // TapCommandList�� �ߺ� üũ Ex> a e a e�� Ŀ�ǵ� ����
			continue;
		std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(CommandStream[i]);
		if (it != curNode->NextCommandNode.end())
		{
			TapCommandList.push_back(CommandStream[i]);
			curNode = it->second;
			if (FindHoldCommand(curNode, TapCommandList, size))
				return true;
			else
			{
				curNode = tempNode;
				TapCommandList.pop_back();
			}
		}
	}
	if (curNode->ExcuteFunction[KeyDown] != nullptr)
		return true;
	return false;
}

// ��Ʈ�� �ڸ��� �÷��� �Է��� ��� �Ǿ����� �����ϱ� - ������, Ű����
// Update���� ��Ʈ�� �����ϱ�?
void InputAction::AddInputKey(int key, BYTE Device)
{
	CurState[key + Device] = true;
}

void InputAction::InvokeFunction(std::vector<int>& keyList, InputState KeyState)
{
	//Find
	CommandNode* curNode = &HeadNode;
	for (int depth = 0; depth < keyList.size(); depth++)
	{
		std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(keyList[depth]);
		if (it == curNode->NextCommandNode.end())
		{
			return;
		}
		curNode = it->second;
	}

	if (curNode->ExcuteFunction[KeyState] != nullptr)
		curNode->ExcuteFunction[KeyState]->InvokeFunction();
}

void InputAction::InvokeFunction(int keyList, InputState KeyState)
{
	//Find
	CommandNode* curNode = &HeadNode;
	std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(keyList);
	if (it == curNode->NextCommandNode.end())
	{
		return;
	}
	curNode = it->second;

	if (curNode->ExcuteFunction[KeyState] != nullptr)
		curNode->ExcuteFunction[KeyState]->InvokeFunction();
}