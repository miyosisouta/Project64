#pragma once
#include "Actor/Actor.h"

class Pipe : public Actor
{
private:
	int id_ = 0;

public:
	void SetId(int id) { id_ = id; }


public:
	Pipe();
	~Pipe();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

