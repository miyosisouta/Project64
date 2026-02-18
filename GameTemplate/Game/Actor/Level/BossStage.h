#pragma once

#include "StageBase.h"


class BossStage : public StageBase
{
public:
	BossStage();
	~BossStage();

	void LoadStageData() override;
	void UnloadStageData()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

