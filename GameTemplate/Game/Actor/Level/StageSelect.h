#pragma once
#include "StageBase.h"

class StageSelect : public StageBase
{
public:
	StageSelect();
	~StageSelect();

	void LoadStageData() override;
	void UnloadStageData()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

