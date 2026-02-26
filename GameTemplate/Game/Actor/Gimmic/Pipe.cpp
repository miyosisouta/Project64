#include "stdafx.h"
#include "Coin.h"
#include "Pipe.h"

namespace
{
	static const float PIPE_COLLISION_SIZE = 0.3f; // コインの当たり判定のサイズ
	static const Vector3 PIPE_COLLISION_POS_UP = Vector3(0.0f,30.0f,0.0f);
}

Pipe::Pipe()
{
	
}

Pipe::~Pipe()
{
}

bool Pipe::Start()
{

	// 土管のモデルを初期化
	{
		model_.Init("Assets/modelData/Stage/ObjectData/Pipe01.tkm");
		model_.SetPosition(transform_.m_position);
		model_.SetRotation(transform_.m_rotation);
		model_.SetScale(transform_.m_scale);
	}

	// 当たり判定の位置を調整
	Vector3 collisionPos = transform_.m_position + PIPE_COLLISION_POS_UP;

	// コインの当たり判定を作成
	{
		collision_ = new CollisionObject();
		collision_->CreateBox(collisionPos, transform_.m_rotation, transform_.m_scale);
		collision_->SetIsEnableAutoDelete(false);
	}

	// 当たり判定管理クラスにコインとエリア番号を登録
	CollisionHitManager::Get().RegistGimmicList(this);
	return true;
}

void Pipe::Update()
{
	model_.Update();
}

void Pipe::Render(RenderContext& rc)
{
	model_.Draw(rc);
}
