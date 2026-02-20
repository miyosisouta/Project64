#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene()
{
}
InGameScene::~InGameScene()
{
}

void InGameScene::Enter()
{
	player_ = NewGO<Player>(0, "Player"); // プレイヤーの生成
	camera_ = new GameCamera(); // カメラの生成
}

void InGameScene::Update()
{
}

void InGameScene::Exit()
{
}

void InGameScene::Render(RenderContext& rc)
{
}
