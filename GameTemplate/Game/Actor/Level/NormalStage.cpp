#include "stdafx.h"
#include "StageLoader.h"
#include "NormalStage.h"

NormalStage::NormalStage()
{
}

NormalStage::~NormalStage()
{
}

void NormalStage::LoadStageData()
{
	stageLoader_->LoadStage("Assets/Level/NormalStage.tkl");
}

void NormalStage::UnloadStageData()
{
}

void NormalStage::Update()
{
}

void NormalStage::Render(RenderContext& rc)
{
}
