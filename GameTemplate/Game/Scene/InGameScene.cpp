#include "stdafx.h"
#include "InGameScene.h"
#include "Actor/Level/NormalStage.h"

InGameScene::InGameScene()
{
}
InGameScene::~InGameScene()
{
}

void InGameScene::Enter()
{
	player_ = NewGO<Player>(0, "Player"); // プレイヤーの生成
	controller_ = NewGO<Controller>(0, "Controller"); // コントローラーの生成
	controller_->SetTarget(player_); // コントローラーのターゲットをプレイヤーに設定
	camera_ = new GameCamera(); // カメラの生成
	camera_->SetTarget(player_); // カメラのターゲットをプレイヤーに設定
	camera_->SetUp();
	stage_ = new NormalStage();
}

void InGameScene::Update()
{
	// NewGOしていないものはここで更新を呼ぶ
	stage_->Update();
	camera_->Update();

	
	if (!isClear_) { return; } // クリアしていない場合ここで処理を返す。

	// クリア後の処理をここから書く

	// クリア後、フェード待ち状態になった場合、
	if (FadeManager::Get().IsFadeWaitState())
	{

	}

}

void InGameScene::Exit()
{
}

void InGameScene::Render(RenderContext& rc)
{
	stage_->Render(rc);
}
