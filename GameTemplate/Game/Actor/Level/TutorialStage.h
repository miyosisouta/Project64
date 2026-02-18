#pragma once
#include "StageBase.h"

class TutorialStage : public StageBase
{
public:
	TutorialStage();
	~TutorialStage();

	void LoadStageData() override;
	void UnloadStageData()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

