#pragma once
#include "Actor/Gimmic/GimmicBase.h"
class Star : public GimmicBase
{
public:
	Star();
	~Star();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	GimmicBase::enHitReactionType DoEffect()override;
};