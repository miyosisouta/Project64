#include "stdafx.h"
#include "Actor/Actor.h"
#include "StaticObject.h"

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

bool StaticObject::Start()
{	
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);
	return true;
}
void StaticObject::Update()
{
	model_.Update();
}
void StaticObject::Render(RenderContext& rc)
{
	model_.Draw(rc);
}
