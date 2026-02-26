#include "stdafx.h"
#include "Coin.h"
#include "Collision/CollisionManager.h"

namespace 
{
	constexpr float PIPE_COLLISION_SIZE = 0.3f; // コインの当たり判定のサイズ
	constexpr uint8_t ADD_COIN_YELLOW = 1;	// 黄色コインの追加コイン数
	constexpr uint8_t ADD_COIN_RED = 2;		// 黄色コインの追加コイン数
	constexpr uint8_t ADD_COIN_BLUE = 5;	// 黄色コインの追加コイン数
}

/**************************** 黄色コイン ****************************/

YellowCoin::YellowCoin()
{
}

YellowCoin::~YellowCoin()
{
}

bool YellowCoin::Start()
{
	// コインのモデルを初期化
	{
		model_.Init("Assets/modelData/Stage/ObjectData/YellowCoin.tkm");
		model_.SetPosition(transform_.m_position);
		model_.SetRotation(transform_.m_rotation);
		model_.SetScale(transform_.m_scale);
	}

	// コインの当たり判定のサイズをモデルの大きさより少し大きくする
	Vector3 collisionSize = Vector3(
		transform_.m_scale.x + PIPE_COLLISION_SIZE,
		transform_.m_scale.y + PIPE_COLLISION_SIZE,
		transform_.m_scale.z + PIPE_COLLISION_SIZE
	); 

	// コインの当たり判定を作成
	{
		collision_ = new CollisionObject();
		collision_->CreateBox(transform_.m_position, transform_.m_rotation, collisionSize);
		collision_->SetIsEnableAutoDelete(false); // コインは自動で削除されないようにする
	}

	// 当たり判定管理クラスにコインとエリア番号を登録
	CollisionHitManager::Get().RegistGimmicList(this);
	return true;
}

void YellowCoin::Update()
{
	model_.Update();
}

void YellowCoin::Render(RenderContext& rc)
{
	model_.Draw(rc);
}

void YellowCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_YELLOW); // 合計コイン数を1追加
	DeleteGO(this); // コインを削除

}

/**************************** 赤コイン ****************************/

RedCoin::RedCoin()
{
}

RedCoin::~RedCoin()
{
}

bool RedCoin::Start()
{
	model_.Init("Assets/modelData/Stage/ObjectData/RedCoin.tkm");
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);

	// コインの当たり判定のサイズをモデルの大きさより少し大きくする
	Vector3 collisionSize = Vector3(
		transform_.m_scale.x + PIPE_COLLISION_SIZE,
		transform_.m_scale.y + PIPE_COLLISION_SIZE,
		transform_.m_scale.z + PIPE_COLLISION_SIZE
	);

	collision_ = new CollisionObject();
	collision_->CreateSphere(transform_.m_position, transform_.m_rotation, 0.5f);
	collision_->SetIsEnableAutoDelete(false);

	// 当たり判定管理クラスにコインとエリア番号を登録
	CollisionHitManager::Get().RegistGimmicList(this);
	return true;
}

void RedCoin::Update()
{
	model_.Update();
}

void RedCoin::Render(RenderContext& rc)
{
	model_.Draw(rc);
}

void RedCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_RED); // 合計コイン数を2追加
	DeleteGO(this); // コインを削除
}

/**************************** 青コイン ****************************/

BlueCoin::BlueCoin()
{
}

BlueCoin::~BlueCoin()
{
}

bool BlueCoin::Start()
{
	// コインのモデルを初期化
	{
		model_.Init("Assets/modelData/Stage/ObjectData/BlueCoin.tkm");
		model_.SetPosition(transform_.m_position);
		model_.SetRotation(transform_.m_rotation);
		model_.SetScale(transform_.m_scale);
	}

	// コインの当たり判定のサイズをモデルの大きさより少し大きくする
	Vector3 collisionSize = Vector3(
		transform_.m_scale.x + PIPE_COLLISION_SIZE,
		transform_.m_scale.y + PIPE_COLLISION_SIZE,
		transform_.m_scale.z + PIPE_COLLISION_SIZE
	);

	// コインの当たり判定を作成
	{
		collision_ = new CollisionObject();
		collision_->CreateSphere(transform_.m_position, transform_.m_rotation, 0.5f);
		collision_->SetIsEnableAutoDelete(false);
	}
	// 当たり判定管理クラスにコインとエリア番号を登録
	CollisionHitManager::Get().RegistGimmicList(this);
	return true;
}

void BlueCoin::Update()
{
	model_.Update();
}

void BlueCoin::Render(RenderContext& rc)
{
	model_.Draw(rc);
}

void BlueCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_BLUE); // 合計コイン数を5追加
	DeleteGO(this); // コインを削除
}
