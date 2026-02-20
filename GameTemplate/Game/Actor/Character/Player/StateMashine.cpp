#include "stdafx.h"
#include "StateMashine.h"
#include "Player.h"
#include "PlayerState.h"


StateMashine::StateMashine()
{
	// ステートの生成
	stateList_[enPlayerState::Idle] = new IdleState(this);
	stateList_[enPlayerState::Walk] = new WalkState(this);
	stateList_[enPlayerState::Run] = new RunState(this);
	stateList_[enPlayerState::Jump] = new JumpState(this);
	stateList_[enPlayerState::Fall] = new FallState(this);
}

StateMashine::~StateMashine()
{
	for (auto* state : stateList_) // 生成したステートを削除
	{
		delete state;
		state = nullptr;
	}
}

void StateMashine::Update()
{
	ChangeState(); // ステートを変更するか確認
	currentState_->Update(); // 現在のステートの更新
}

void StateMashine::Setup(Player* player)
{
	currentState_ = stateList_[enPlayerState::Idle]; // 初期ステートを待機に設定

	owner_ = player; // プレイヤーへのポインタを保存
	ownerStatus_= owner_->GetPlayerStatus(); // プレイヤーステータスへのポインタを取得
}

void StateMashine::ChangeState()
{
	// ステートを変更するか確認
	CheckChangeState();

	// ステートを変更する場合
	if (nextState_ != nullptr && currentState_ != nextState_)
	{
		currentState_->Exit();		// 現在のステートを終了
		currentState_ = nextState_; // 新しいステートに変更
		currentState_->Enter();		// 新しいステートを開始
		nextState_ = nullptr;		// 次のステートをリセット
	}

	currentState_->Update(); // 現在のステートの更新
}

void StateMashine::CheckChangeState()
{
	if (currentState_ == stateList_[enPlayerState::Jump])
	{
		if (!owner_->IsOnGrounded())
		{
			return; // ジャンプ中で地面についていない場合は、他のステートに変更しない
		}
	}

	// 地面についていないなら落下ステートに変更
	if (!owner_->IsOnGrounded() && currentState_ != stateList_[enPlayerState::Jump])
	{
		nextState_ = stateList_[enPlayerState::Fall];
		return;
	}

	if (ChangeStateJump())
	{
		nextState_ = stateList_[enPlayerState::Jump]; // ジャンプステートに変更
	}

	else if (ChangeStateRun())
	{
		nextState_ = stateList_[enPlayerState::Run]; // 走りステートに変更
	}
	
	else if (ChangeStateWalk())
	{
		nextState_ = stateList_[enPlayerState::Walk]; // 歩きステートに変更
	}
	else {
		nextState_ = stateList_[enPlayerState::Idle]; // 待機ステートに変更
	}
}

bool StateMashine::ChangeStateWalk()
{
	if (inputAmount_ >= 0.01f) { return true; }
	return false;
}

bool StateMashine::ChangeStateRun()
{
	if (isInputA_ && direction_.Length() >= 0.01f) { return true; }
	return false;
}

bool StateMashine::ChangeStateJump()
{
	if (isInputB_&& owner_->IsOnGrounded())
	{
		return true;
	}
	return false;
}
