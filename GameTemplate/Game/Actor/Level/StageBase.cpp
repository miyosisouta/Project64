#include "stdafx.h"
#include "StageBase.h"
#include "StageLoader.h"


StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

void StageBase::Update()
{
	stageLoader_->Update();
}

void StageBase::Render(RenderContext& rc)
{
	stageLoader_->Render(rc);
}
