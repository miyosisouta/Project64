#include "stdafx.h"
#include "GameCamera.h"
#include "Actor/Character/Player/Player.h"

namespace
{
	// カメラの位置
	const float CAMERA_POS_Y = 100.0f; //カメラの高さ
	const float CAMERA_POS_Z = -500.0f; //カメラの後ろへの距離

	// クリップ距離
	const float CAMERA_NEAR_CLIP = 1.0f; //近平面
	const float CAMERA_FAR_CLIP = 10000.0f; //遠平面

	// その他
	const float ZERO = 0.0f; //ゼロベクトル
	const float TARGET_HEIGHT = 20.0f; // 注視点の高さ
}
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::SetUp()
{
	// プレイヤーの座標を取得
	transform_.m_localPosition.y = target_->GetTransform()->m_position.y + CAMERA_POS_Y;
	transform_.m_localPosition.z = target_->GetTransform()->m_position.z + CAMERA_POS_Z;
	transform_.UpdateTransform();

	//注視点から視点までのベクトルを設定
	toCameraPos_.Set(ZERO, transform_.m_position.y, transform_.m_position.z);

	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(CAMERA_NEAR_CLIP);
	g_camera3D->SetFar(CAMERA_FAR_CLIP);
}

void GameCamera::Update()
{
	// 注視点を計算
	Vector3 target = target_->GetTransform()->m_position; // 注視点の基準をプレイヤーの座標に設定
	target.y += TARGET_HEIGHT; 	// 少し上にあげる
	toCameraOldPos_ = target_->GetTransform()->m_position; // 前フレームのカメラの座標を保存


	if (IsActiveCamera())
	{
		// パッドの入力を使ってカメラを回す
		float x = g_pad[0]->GetRStickXF() * 0.8f;
		float y = g_pad[0]->GetRStickYF() * 0.8f;

		// Y軸の回転（左右）
		Quaternion qRotY;
		qRotY.SetRotationDeg(Vector3::AxisY, 1.0f * x);
		qRotY.Apply(transform_.m_localPosition);

		// X軸の回転（上下）
		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, transform_.m_localPosition);


		if (axisX.LengthSq() > 0.001f)
		{
			axisX.Normalize();
			Quaternion qRotX;
			qRotX.SetRotationDeg(axisX, 2.0f * y);

			Vector3 nextPos = transform_.m_localPosition;
			qRotX.Apply(nextPos);

			// カメラが真上や真下に行き過ぎないように制限する（これで異常な遠ざかりを防ぐ）
			Vector3 dir = nextPos;
			dir.Normalize();
			if (dir.y < 0.95f && dir.y > -0.95f) // Y方向の角度制限
			{
				transform_.m_localPosition = nextPos;
			}
		}

		// カメラが地面にめり込まないようにする
		if (transform_.m_localPosition.y < -10.0f)
		{
			transform_.m_localPosition = toCameraOldPos_; // 下がりすぎたら1フレーム前に戻す
		}
	}

	// 注視点から視点までのベクトルを正規化
	Vector3 toPosDir = transform_.m_localPosition;
	toPosDir.Normalize();

	// カメラの回転の上限をチェック
	if (toPosDir.y < -0.2f) { transform_.m_localPosition = toCameraOldPos_; } // カメラが上向きすぎ
	else if (toPosDir.y > 0.9f) { transform_.m_localPosition = toCameraOldPos_; } // カメラが下向きすぎ


	// 視点を計算
	Vector3 pos = target + transform_.m_localPosition;

	// クリアイベント中なら進行度を考慮してカメラと注視点を動かす
	if (target_->IsClearEventAction())
	{
		float t = target_->GetClearEventProgress();

		// tに合わせて注視点を左に、カメラ位置を右・手前にずらす
		Vector3 targetOffset = Math::Lerp(t, Vector3::Zero, Vector3(100.0f, 0.0f, 0.0f));
		Vector3 posOffset = Math::Lerp(t, Vector3::Zero, Vector3(-200.0f, 0.0f, -100.0f));

		target += targetOffset;
		pos += posOffset;
	}

	// カメラの注視点・視点の設定
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	// カメラの更新
	g_camera3D->Update();
	transform_.UpdateTransform();
}
