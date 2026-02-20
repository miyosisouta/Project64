#include "stdafx.h"
#include "PlayerState.h"
#include "Actor/ActorStatus.h"
#include "Actor/Character/Player/StateMashine.h"
#include "Actor/Character/Player/Player.h"

/*************** 待機ステート用クラス **************/

IdleState::IdleState(StateMashine* owner)
	: IState(owner)
{
}

void IdleState::Enter()
{
	// 待機アニメーションを再生
	owner_->GetPlayer()->GetModelRender().PlayAnimation(Player::enPlayerAnimaitonState::Idle);
}

void IdleState::Update()
{
}

void IdleState::Exit()
{
}


/*************** 歩きステート用クラス **************/

WalkState::WalkState(StateMashine* owner)
	: IState(owner)
{
}

void WalkState::Enter()	
{
	// 歩きアニメーションを再生
	owner_->GetPlayer()->GetModelRender().PlayAnimation(Player::enPlayerAnimaitonState::Walk);
}

void WalkState::Update()
{
	// 入力量が0.01以下なら更新しない
	if (owner_->GetInputAmount() <= 0.01f) { return; }

	// 移動方向を取得
	Vector3 moveDir = owner_->GetDirection();
	// 移動量を計算
	Vector3 move = moveDir * owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetWalkSpeed() * owner_->GetInputAmount();


	owner_->SetMoveVector(move); // ステートマシンに移動ベクトルを設定
}

void WalkState::Exit()
{
	owner_->SetMoveVector(Vector3::Zero); // ステートマシンに移動ベクトルをリセット
}

/*************** 走りステート用クラス ***************/

RunState::RunState(StateMashine* owner)
	: IState(owner)
{
}

void RunState::Enter()
{
	// 走りアニメーションを再生
	owner_->GetPlayer()->GetModelRender().PlayAnimation(Player::enPlayerAnimaitonState::Run);
}

void RunState::Update()
{
	// 入力量が0.01以下なら更新しない
	if (owner_->GetInputAmount() <= 0.01f) { return; }

	// 移動方向を取得
	Vector3 moveDir = owner_->GetDirection();
	// 移動量を計算
	Vector3 move = moveDir * owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetRunSpeed() * owner_->GetInputAmount();

	owner_->SetMoveVector(move); // ステートマシンに移動ベクトルを設定
}

void RunState::Exit()
{
	owner_->SetMoveVector(Vector3::Zero); // ステートマシンに移動ベクトルをリセット
}

/*************** ジャンプステート用クラス ***************/

JumpState::JumpState(StateMashine* owner)
	: IState(owner)
{
}

void JumpState::Enter()
{
	// ジャンプアニメーションを再生
	owner_->GetPlayer()->GetModelRender().PlayAnimation(Player::enPlayerAnimaitonState::Jump);
	// ジャンプの力を保存
	currentPosY = owner_->GetPlayerStatus()->GetJumpPower();
}

void JumpState::Update()
{
	// 移動方向を取得
	Vector3 moveDir = owner_->GetDirection();
	Vector3 move = moveDir;

	// XZ方向（前後左右）の移動処理
	if (owner_->IsInputA()) {
		move *= owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetRunSpeed() * owner_->GetInputAmount();
	}
	else {
		move *= owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetWalkSpeed() * owner_->GetInputAmount();
	}

	// Y方向（上下）の移動処理：毎フレーム重力を引くだけ！
	currentPosY -= owner_->GetPlayerStatus()->GetFallSpeed();
	move.y = currentPosY;

	// ステートマシンに移動ベクトルを設定
	owner_->SetMoveVector(move);
}

void JumpState::Exit()
{
	owner_->SetMoveVector(Vector3::Zero); // ステートマシンに移動ベクトルをリセット
}


/*************** 落下ステート用クラス ***************/

FallState::FallState(StateMashine* owner)
	: IState(owner)
{
	currentPosY = 0.0f; // 落ちるスピードを初期化
}

void FallState::Enter()
{
}

void FallState::Update()
{
	Vector3 moveDir = owner_->GetDirection();
	Vector3 move = moveDir;

	if (owner_->IsInputA()) {
		move *= owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetRunSpeed() * owner_->GetInputAmount();
	}
	else {
		move *= owner_->GetPlayerStatus()->GetBasicSpeed() * owner_->GetPlayerStatus()->GetWalkSpeed() * owner_->GetInputAmount();
	}

	// 毎フレーム重力を引いて落ちるスピードを加速させる
	currentPosY -= owner_->GetPlayerStatus()->GetFallSpeed();
	move.y = currentPosY;

	owner_->SetMoveVector(move);
}

void FallState::Exit()
{
	owner_->SetMoveVector(Vector3::Zero); // ステートマシンに移動ベクトルをリセット
}
