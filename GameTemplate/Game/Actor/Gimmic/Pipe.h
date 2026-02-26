#pragma once
#include "Actor/Gimmic/GimmicBase.h"

class Pipe : public GimmicBase
{
public:
	Pipe();
	~Pipe();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

