#include "stdafx.h"
#include "IScene.h"
#include "StageSelectScene.h"
#include "Actor/Level/StageSelect.h"


StageSelectScene::StageSelectScene()
{
}
StageSelectScene::~StageSelectScene()
{
	delete stage_;
	stage_ = nullptr;

	DeleteGO(player_);
	delete camera_;
	camera_ = nullptr;
}

void StageSelectScene::Enter()
{
	player_ = NewGO<Player>(0, "Player"); // プレイヤーの生成
	controller_ = NewGO<Controller>(0, "Controller"); // コントローラーの生成
	controller_->SetTarget(player_); // コントローラーのターゲットをプレイヤーに設定
	camera_ = new GameCamera(); // カメラの生成
	camera_->SetTarget(player_); // カメラのターゲットをプレイヤーに設定
	camera_->SetUp();
	stage_ = new StageSelect();
}

void StageSelectScene::Update()
{
	stage_->Update();
	camera_->Update();
}

void StageSelectScene::Exit()
{
	
}

void StageSelectScene::Render(RenderContext& rc)
{
	stage_->Render(rc);
}
