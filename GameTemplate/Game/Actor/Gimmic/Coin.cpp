#include "stdafx.h"
#include "Coin.h"

/**************************** 黄色コイン ****************************/

YellowCoin::YellowCoin()
{
}

YellowCoin::~YellowCoin()
{
}

bool YellowCoin::Start()
{
	model_.Init("Assets/modelData/Stage/ObjectData/YellowCoin.tkm");
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);
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

/**************************** 青コイン ****************************/

BlueCoin::BlueCoin()
{
}

BlueCoin::~BlueCoin()
{
}

bool BlueCoin::Start()
{
	model_.Init("Assets/modelData/Stage/ObjectData/BlueCoin.tkm");
	model_.SetPosition(transform_.m_position);
	model_.SetRotation(transform_.m_rotation);
	model_.SetScale(transform_.m_scale);
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
