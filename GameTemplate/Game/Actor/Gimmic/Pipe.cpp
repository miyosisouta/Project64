#include "stdafx.h"
#include "Coin.h"
#include "Pipe.h"

Pipe::Pipe()
{
}

Pipe::~Pipe()
{
}

bool Pipe::Start()
{
	model_.Init("Assets/modelData/Stage/ObjectData/Pipe01.tkm");
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);
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
