#include "stdafx.h"
#include "PlayerState.h"
#include "Actor/ActorStatus.h"
#include "Actor/Character/Player/StateMashine.h"
#include "Actor/Character/Player/Player.h"
#include "Timer/LerpTimer.h"

namespace 
{
	static const Vector3 PIPE_TOP_POS = Vector3(0.0f, 80.0f, 0.0f); // 土管の一番上
	static const Vector3 PIPE_BOTTOM_POS = Vector3(0.0f, 0.0f, 0.0f); // 土管の一番上
}


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


/*************** 土管転移ステート用クラス ***************/

PipeWarpState::PipeWarpState(StateMashine* owner)
	: IState(owner)
{
	
}

void PipeWarpState::Enter()
{
	startPos_ = owner_->GetPipeWarpStart() + PIPE_TOP_POS;
	endPos_ = owner_->GetPipeWarpStart() + PIPE_BOTTOM_POS;

	nextPos_ = owner_->GetPipeWarpEnd();
	timer_ = owner_->GetPipeInOutTime();
	lerpTimer_.Init(timer_);

	owner_->GetPlayer()->SetBind(false);
	owner_->GetPlayer()->GetModelRender().PlayAnimation(Player::enPlayerAnimaitonState::Idle);
}

void PipeWarpState::Update()
{
	if (currentWarpState == enWarp_wait)
	{
		if (FadeManager::Get().IsFadeWaitState())
		{
			owner_->GetPlayer()->GetTransform()->m_localPosition = startPos_;
			owner_->GetPlayer()->GetTransform()->UpdateTransform();
			owner_->GetPlayer()->GetModelRender().SetPosition(owner_->GetPlayer()->GetTransform()->m_position);
			owner_->GetPlayer()->SetDraw(true);

			// 土管から出る際の処理ステートに変更
			currentWarpState = enWarp_after;
			// 描画されるようにする
			owner_->GetPlayer()->SetDraw(true);

			lerpTimer_.Init(timer_);
		}
		return;
	}

	// フェードが再生中なら移動処理とをしない
	if (FadeManager::Get().IsFadePlay()) { return; }

	float hoge = lerpTimer_.CalcfloatUpdate();
	Vector3 pos = Math::Lerp(hoge, startPos_, endPos_);
	float scal = 0.0f;

	if (currentWarpState == enWarp_before) { scal = 1.0f - hoge; }
	else if (currentWarpState == enWarp_after) { scal = hoge; }

	// 座標の設定
	owner_->GetPlayer()->GetTransform()->m_localPosition = pos;
	owner_->GetPlayer()->GetTransform()->UpdateTransform();
	owner_->GetPlayer()->GetModelRender().SetPosition(owner_->GetPlayer()->GetTransform()->m_position);
	owner_->GetPlayer()->GetCharaCon().SetPosition(owner_->GetPlayer()->GetTransform()->m_position);

	// 大きさの設定
	owner_->GetPlayer()->GetTransform()->m_localScale.x = scal;
	owner_->GetPlayer()->GetTransform()->m_localScale.y = scal;
	owner_->GetPlayer()->GetTransform()->m_localScale.z = scal;
	owner_->GetPlayer()->GetTransform()->UpdateTransform();

	// ステート変更
	if (hoge >= 0.99f)
	{
		if (currentWarpState == enWarp_before)
		{
			currentWarpState = enWarp_wait;
			owner_->GetPlayer()->SetDraw(false);

			// 出る時
			startPos_ = nextPos_;
			endPos_ = nextPos_ + PIPE_TOP_POS;

			FadeManager::Get().PlayFade(FadeManager::FadeType::enFadeType_Color, TransitionFade::FadeMode::FadeOut, 1.5f, Vector3(0.0f, 0.0f, 0.0f), 2.0f);
		}
		else if (currentWarpState == enWarp_after)
		{
			currentWarpState = enWarp_finish;
		}
	}


	if (currentWarpState == enWarp_finish)
	{
		owner_->GetPlayer()->SetBind(true);
	}
}

void PipeWarpState::Exit()
{
	// 初期のステートに戻す
	currentWarpState = enWarp_before;
}
