#include "stdafx.h"
#include "Coin.h"
#include "Actor/Gimmic/GimmicBase.h"
#include "Collision/CollisionManager.h"


namespace 
{
	constexpr uint8_t ADD_COIN_YELLOW = 1;	// 黄色コインの追加コイン数
	constexpr uint8_t ADD_COIN_RED = 2;		// 黄色コインの追加コイン数
	constexpr uint8_t ADD_COIN_BLUE = 5;	// 黄色コインの追加コイン数

	static const Vector3 COLLISION_SIZE = Vector3(100.0f, 100.0f, 20.0f); // コインの当たり判定のサイズ
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


	// コインの当たり判定を作成
	{
		triggerCollision_ = new CollisionObject();
		triggerCollision_->CreateBox(transform_.m_position, transform_.m_rotation, COLLISION_SIZE);
		triggerCollision_->SetIsEnableAutoDelete(false); // コインは自動で削除されないようにする
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

GimmicBase::enHitReactionType YellowCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_YELLOW); // 合計コイン数を1追加
	DeleteGO(this); // コインを削除
	return enHitReactionType::enHitReactionType_None;
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

	triggerCollision_ = new CollisionObject();
	triggerCollision_->CreateBox(transform_.m_position, transform_.m_rotation, COLLISION_SIZE);
	triggerCollision_->SetIsEnableAutoDelete(false);

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

GimmicBase::enHitReactionType RedCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_RED); // 合計コイン数を2追加
	DeleteGO(this); // コインを削除
	return enHitReactionType::enHitReactionType_None;
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


	// コインの当たり判定を作成
	{
		triggerCollision_ = new CollisionObject();
		triggerCollision_->CreateBox(transform_.m_position, transform_.m_rotation, COLLISION_SIZE);
		triggerCollision_->SetIsEnableAutoDelete(false);
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

GimmicBase::enHitReactionType BlueCoin::AddEffect()
{
	UserData::Get().AddTotalCoin(ADD_COIN_BLUE); // 合計コイン数を5追加
	DeleteGO(this); // コインを削除
	return enHitReactionType::enHitReactionType_None;
}
