#pragma once
#include "StageBase.h"

class NormalStage : public StageBase
{
public:
	NormalStage();
	~NormalStage();
	void LoadStageData() override;
	void UnloadStageData()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

