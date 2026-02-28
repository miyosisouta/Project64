#include "stdafx.h"
#include "StageLoader.h"
#include "NormalStage.h"

NormalStage::NormalStage()
{
	stageLoader_ = new StageLoader();
	LoadStageData();
}

NormalStage::~NormalStage()
{
	if (stageLoader_) {
		delete stageLoader_;
		stageLoader_ = nullptr;
	}
}

void NormalStage::LoadStageData()
{
	stageLoader_->LoadStage("Assets/modelData/Stage/tkl/StageNormal.tkl");
}

void NormalStage::UnloadStageData()
{
}

void NormalStage::Update()
{
	stageLoader_->Update();
}

void NormalStage::Render(RenderContext& rc)
{
	stageLoader_->Render(rc);
}
