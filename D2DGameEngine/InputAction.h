#pragma once

#include "IInputDevice.h"

class Deligator0
{
public:
    using CallBackFunction = std::function<void()>;
    using CallBcakMAp = std::map<uintptr_t, CallBackFunction>;

    template <typename Class>
    void RemoveFunction(Class* instance)
    {
        FuctionList.erase(reinterpret_cast<uintptr_t>(instance));
    }

    void InvokeFunction()
    {
        for (const auto& pair : FuctionList)
        {
            pair.second();
        }
    }

    template <typename Class, typename Function>
    void AddFunction(Class* _instance, Function&& _function)
    {
        CallBackFunction callback = [_instance, _function]()
            {
                (_instance->*_function)();
            };
        FuctionList[reinterpret_cast<uintptr_t>(_instance)] = callback;
    }

private:
    CallBcakMAp FuctionList;
};

// Ŀ�ǵ�� ������ Tap�� ��츸 �Ǵ��ؼ� �ȴ�.
   // ���� KeyDown�� ����..?
   // ���� Ŭ���� ��� Ŭ���̾�Ʈ ���̵忡�� {static bool���� ������ GetClock���� ���ؼ� �Ǵ� �� ����..?}
   // ->���ٸ� �̿��ؼ� ��ü ���ο��� �ð� Ȯ�� ����...? ¿���� �ð� ����
enum InputState { KeyDown, KeyHold, KeyUp, None };

/// <summary>
/// ���� Ű ����Ʈ�� �����ѵ� ����Ŭ���� ���� ����?
/// ����Ŭ���� ���߿� ���� �Լ� ���ν� ���ڷ� �ִ� AddCommandLimitedTime(Class* instance, std::vector<int>& keyList??? int key, Function&& function, InputState KeyState, float deltaTime)�� ���� 
///         bool                    PreveState[InputSize] = { 0 };��
///         std::pair<bool,float>   PreveState[InputSize] = { 0 };��
/// ���� �ؾ��� ��????
/// </summary>

/// <summary>
/// ������ 1���� �Լ��� ������ �Ǵµ�
/// std::shared_ptr<Deligator0> ExcuteFunction[None] = { nullptr };��
/// ����Ʈ�� ����� ������ ���� ����? ����
/// </summary>
struct CommandNode
{
    int Command = -1;
    std::map<int, CommandNode*> NextCommandNode;
    InputState CurState = InputState::None;
    //Input�� ��� ������ ���ڰ� 0
    std::shared_ptr<Deligator0> ExcuteFunction[None] = { nullptr };
};

class InputAction
{
public:
    static InputAction* GetInstance();
    static void DestroyInputAction();

public:
    void Update(const float& deltaTime);

    //Object�� Ŀ�ǵ帮��Ʈ(���ϵ� ����)�� Function�� ���� ��Ű�� ���
    void AddInputKey(int key, BYTE Device = KeyBoardInput);

    // �� Ŀ�ǵ忡 �Ѱ�ü�� �� function�� ����
    // ���� ��ü�� ���� Ŀ�ǵ忡 �Լ��� �߰��� ��� ���� ��������.
    template <typename Class, typename Function>
    void AddCommand(Class* instance, const std::vector<int>& keyList, Function&& function, InputState KeyState, BYTE Device = KeyBoardInput)
    {
        //Find & Make
        CommandNode* curNode = &HeadNode;
        for (int depth = keyList.size() - 1; depth >= 0; depth--)
        {
            std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(keyList[depth + Device]);
            if (it == curNode->NextCommandNode.end())
            {
                CommandNode* temp = new CommandNode();
                temp->Command = keyList[depth + Device];
                curNode->NextCommandNode.insert({ keyList[depth + Device], temp });
                curNode = temp;
            }
            else
            {
                curNode = it->second;
            }
        }

        //Function Mapping
        if (curNode->ExcuteFunction[KeyState] == nullptr)
        {
            curNode->ExcuteFunction[KeyState] = std::make_shared<Deligator0>();
        }
        curNode->ExcuteFunction[KeyState]->AddFunction(instance, function);
    }
    template <typename Class, typename Function>
    void AddCommand(Class* instance, int keyList, Function&& function, InputState KeyState, BYTE Device = KeyBoardInput)
    {
        //Find & Make
        CommandNode* curNode = &HeadNode;

        std::map<int, CommandNode*>::iterator it = curNode->NextCommandNode.find(keyList + Device);
        if (it == curNode->NextCommandNode.end())
        {
            CommandNode* temp = new CommandNode();
            temp->Command = keyList + Device;
            curNode->NextCommandNode.insert({ keyList + Device, temp });
            curNode = temp;
        }
        else
        {
            curNode = it->second;
        }


        //Function Mapping
        if (curNode->ExcuteFunction[KeyState] == nullptr)
        {
            curNode->ExcuteFunction[KeyState] = std::make_shared<Deligator0>();
        }
        curNode->ExcuteFunction[KeyState]->AddFunction(instance, function);
    }
    template <typename Class>
    void DeleteCommand(Class* instance, const std::vector<int>& keyList, InputState KeyState, BYTE Device = KeyBoardInput)
    {
        //Find
        CommandNode* curNode = &HeadNode;
        CommandNode* prevNode = nullptr;
        std::map<int, CommandNode*>::iterator it;
        int depth;
        //keyList.size()�� 0�̸� Error
        for (depth = keyList.size() - 1; depth >= 0; depth--)
        {
            it = curNode->NextCommandNode.find(keyList[depth + Device]);
            if (it == curNode->NextCommandNode.end())
            {
                return;
            }
            prevNode = curNode;
            curNode = it->second;
        }
        curNode->ExcuteFunction[KeyState]->RemoveFunction(instance);
        curNode->ExcuteFunction[KeyState] = nullptr;
        for (auto curFuction : curNode->ExcuteFunction)
        {
            if (curFuction != nullptr)
                return;
        }
        if (curNode->NextCommandNode.size() == 0)
        {
            if (nullptr != prevNode)
                prevNode->NextCommandNode.erase(keyList[depth + 1 + Device]);
            delete curNode;
        }
    }
    template <typename Class>
    void DeleteCommand(Class* instance, int keyList, InputState KeyState, BYTE Device = KeyBoardInput)
    {
        //Find
        CommandNode* curNode = &HeadNode;
        CommandNode* prevNode = curNode;
        std::map<int, CommandNode*>::iterator it;
        it = curNode->NextCommandNode.find(keyList + Device);
        if (it == curNode->NextCommandNode.end())
        {
            return;
        }
        curNode = it->second;
        curNode->ExcuteFunction[KeyState]->RemoveFunction(instance);
        curNode->ExcuteFunction[KeyState] = nullptr;
        for (auto curFuction : curNode->ExcuteFunction)
        {
            if (curFuction != nullptr)
                return;
        }
        if (curNode->NextCommandNode.size() == 0)
        {
            if (nullptr != prevNode)
                prevNode->NextCommandNode.erase(keyList + Device);
            delete curNode;
        }
    }

private:
    // �Լ� ����
    void InvokeFunction(std::vector<int>& keyList, InputState KeyState);
    void InvokeFunction(int keyList, InputState KeyState);

    // Tap�� �� Ű �������� ���� �ִ� Ŀ�ǵ���� Ȯ���ؼ� ���� ������ �ϼ��Ǵ� Ŀ�ǵ带 ����
    bool FindHoldCommand(CommandNode*& curNode, std::vector<int>& TapCommandList, int size);

private:
    //Ű �Է� ó��
    static constexpr size_t InputSize = 300;
    bool                    PreveState[InputSize] = { false };
    bool                    CurState[InputSize] = { false };

private:
    //Object�� Ŀ�ǵ帮��Ʈ(���ϵ� ����)�� Function�� ���� ��Ű�� ���
    std::vector<int>    CommandStream;
    std::vector<int>    TapCommandStream;
    float               StreamTime = 0;
    float               MaxStreamTime = 0.2f;
    std::vector<int>    InputData;

    //Object�� Ŀ�ǵ帮��Ʈ(���ϵ� ����)�� Function�� ���� ��Ű�� ����
    CommandNode    HeadNode;  //Command = -1, Excute�� ����. // �Ҵ��� ������ ��ü���� ���ְ� ����Ʈ�� �ѹ��� �ϱ�

private:
    InputAction() {};
    ~InputAction() {};

    static InputAction* pInstance;
};
