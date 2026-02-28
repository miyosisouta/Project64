#include "stdafx.h"
#include "StageLoader.h"
#include "StageSelect.h"

StageSelect::StageSelect()
{
	stageLoader_ = new StageLoader();
	LoadStageData();
	normalCollision_ = new CollisionHitObject();
	
}

StageSelect::~StageSelect()
{
	if (stageLoader_) {
		delete stageLoader_;
		stageLoader_ = nullptr;
	}
}

void StageSelect::LoadStageData()
{
	stageLoader_->LoadStage("Assets/modelData/Stage/tkl/stageSelect.tkl");
}

void StageSelect::UnloadStageData()
{
}

void StageSelect::Update()
{
	stageLoader_->Update();


}

void StageSelect::Render(RenderContext& rc)
{
	stageLoader_->Render(rc);
}
