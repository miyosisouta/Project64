#include "stdafx.h"
#include "Actor/Gimmic/GimmicBase.h"
#include "Coin.h"
#include "Pipe.h"

namespace
{
	static const Vector3 PIPE_COLLISION_TRIGGER_POS_UP = Vector3(0.0f,80.0f,0.0f);
	static const Vector3 PIPE_TRIGGER_COLLISION_SIZE = Vector3(20.0f,10.0f,20.0f);
	static const Vector3 PIPE_COLLISION_SOLID_POS_UP = Vector3(0.0f,75.0f,0.0f);
	static const Vector3 PIPE_SOLID_COLLISION_SIZE = Vector3(80.0f,10.0f,80.0f);

}

Pipe::Pipe()
{
	
}

Pipe::~Pipe()
{
	// 転移用コリジョン
	delete triggerCollision_;
	triggerCollision_ = nullptr;
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
	Vector3 collisionTriggerPos = transform_.m_position + PIPE_COLLISION_TRIGGER_POS_UP;
	Vector3 collisionSolidPos = transform_.m_position + PIPE_COLLISION_SOLID_POS_UP;

	// コリジョンの作成
	{
		// 転移用
		{
			triggerCollision_ = new CollisionObject();
			triggerCollision_->CreateBox(collisionTriggerPos, transform_.m_rotation, PIPE_TRIGGER_COLLISION_SIZE);
			triggerCollision_->SetIsEnableAutoDelete(false);
		}
		// 固い床用
		{
			// 床の「形」を箱型として作成する
			solidBoxCollider_.Create(PIPE_SOLID_COLLISION_SIZE);

			//　剛体の初期化設定を作る
			nsK2EngineLow::RigidBodyInitData rbInfo;
			rbInfo.pos = transform_.m_position + PIPE_COLLISION_SOLID_POS_UP;
			rbInfo.rot = transform_.m_rotation;
			rbInfo.collider = &solidBoxCollider_;

			// 質量を0.0fにすると絶対に動かない固い壁になる
			rbInfo.mass = 0.0f;

			// 設定を元に剛体を初期化
			solidRigidBody_.Init(rbInfo);
		}
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

GimmicBase::enHitReactionType Pipe::DoEffect()
{
	return enHitReactionType::enHitReactionType_PipeWarp;
}
