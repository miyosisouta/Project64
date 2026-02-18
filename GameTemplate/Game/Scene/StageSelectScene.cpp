#include "stdafx.h"
#include "IScene.h"
#include "StageSelectScene.h"
#include "Actor/Level/StageSelect.h"


StageSelectScene::StageSelectScene()
{
}
StageSelectScene::~StageSelectScene()
{
	delete stageSelect_;
	stageSelect_ = nullptr;
}

void StageSelectScene::Enter()
{
	stageSelect_ = new StageSelect();
	g_camera3D->SetPosition(1000.0f, 1000.0f, -2000.0f);
	g_camera3D->SetTarget(0.0f, 0.0f, 0.0f);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);
}

void StageSelectScene::Update()
{
	stageSelect_->Update();
}

void StageSelectScene::Exit()
{
}

void StageSelectScene::Render(RenderContext& rc)
{
	stageSelect_->Render(rc);
}
