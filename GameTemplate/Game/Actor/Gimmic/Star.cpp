#include "stdafx.h"
#include "Star.h"
#include "Actor/Gimmic/GimmicBase.h"

namespace
{
	static const Vector3 COLLISION_SIZE = Vector3(20.0f,40.0f,20.0f);
}

Star::Star()
{
}

Star::~Star()
{
}

bool Star::Start()
{
	model_.Init("Assets/modelData/Stage/ObjectData/Star.tkm");
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);
	model_.Update();

	triggerCollision_ = new CollisionObject();
	triggerCollision_->CreateBox(transform_.m_position,transform_.m_rotation, COLLISION_SIZE);
	triggerCollision_->SetIsEnableAutoDelete(false); // スターは自動で削除されないようにする

	// 当たり判定管理クラスにスターとエリア番号を登録
	CollisionHitManager::Get().RegistGimmicList(this);
	return true;
}

void Star::Update()
{
	
}

void Star::Render(RenderContext& rc)
{
	model_.Draw(rc);
}

GimmicBase::enHitReactionType Star::DoEffect()
{
	return GimmicBase::enHitReactionType(enHitReactionType_Star);
}
