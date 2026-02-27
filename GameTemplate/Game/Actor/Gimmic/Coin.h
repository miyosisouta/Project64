#pragma once

#include "Actor/Gimmic/GimmicBase.h"
class Coin : public GimmicBase
{
public:
	Coin() {};
	virtual~Coin() {};

	virtual bool Start()override { return true; };
	virtual void Update()override {};
	virtual void Render(RenderContext& rc)override {};
	virtual enHitReactionType AddEffect() override { return enHitReactionType_None; }
};


class YellowCoin : public Coin
{
public:
	YellowCoin();
	~YellowCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	enHitReactionType AddEffect() override;
};

class RedCoin : public Coin
{
public:
	RedCoin();
	~RedCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	enHitReactionType AddEffect() override;
};

class BlueCoin : public Coin
{
public:
	BlueCoin();
	~BlueCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	enHitReactionType AddEffect() override;
};

