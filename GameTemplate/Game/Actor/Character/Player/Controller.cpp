#include "stdafx.h"
#include "Controller.h"
#include "Actor/Character/Player/Player.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}

bool Controller::Start()
{
	return true;
}

void Controller::Update()
{
	if (target_ == nullptr) { return; }
	// 現在のプレイヤーのステートマシンを取得
	auto* playerStateMashine = target_->GetStateMashine();

	// プレイヤーの入力操作
	{
		playerStateMashine->SetInputA(g_pad[0]->IsPress(enButtonA));	// Aボタン入力
		playerStateMashine->SetInputB(g_pad[0]->IsTrigger(enButtonB));	// Bボタン入力
		playerStateMashine->SetInputX(g_pad[0]->IsTrigger(enButtonX));	// Xボタン入力
		playerStateMashine->SetInputY(g_pad[0]->IsTrigger(enButtonY));	// Yボタン入力
	}

	// 左スティックの入力があるか
	if (IsInputStickL()) 
	{ 
		playerStateMashine->SetRotation(ComputeRotation());	// 回転を計算して設定
		playerStateMashine->SetDirection(GetStickL());		// 方向を設定
	}
	
	// 左スティックの入力量を取得して設定
	Vector3 rawStick(g_pad[0]->GetLStickXF(),0.0, g_pad[0]->GetLStickYF());
	playerStateMashine->SetInputAmount(rawStick.Length());
}

Vector3 Controller::GetStickL()
{
	// 左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// カメラの前方向と右方向のベクトルを取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// y方向には移動しない
	forward.y = 0.0f;
	right.y = 0.0f;

	// 左スティックの入力量を加算
	right *= stickL.x;
	forward *= stickL.y;

	Vector3 direction = right + forward;
	// 0～1の範囲に変更
	direction.Normalize();

	return direction;
}


Quaternion Controller::ComputeRotation()
{
	// スティックの方向
	Vector3 direction = GetStickL();
	// スティック入力を使ってY軸回転の情報を得る
	Quaternion q;
	q.SetRotationYFromDirectionXZ(direction);

	return q;
}

bool Controller::IsInputStickL()
{
	if (fabsf(g_pad[0]->GetLStickXF()) >= 0.1f || fabsf(g_pad[0]->GetLStickYF()) >= 0.1f)
	{
		return true;
	}
	return false;
}
