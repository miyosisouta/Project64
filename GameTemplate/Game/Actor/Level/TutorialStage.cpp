#include "stdafx.h"
#include "StageLoader.h"
#include "TutorialStage.h"

void TutorialStage::LoadStageData()
{
	stageLoader_->LoadStage("Assets/ModelData/Stage/StageSelect.tkl");
}

void TutorialStage::UnloadStageData()
{
}
