#pragma once

#include "Actor/Actor.h"

class Coin : public Actor
{
public:
	Coin() {};
	virtual~Coin() {};

	virtual bool Start()override { return true; };
	virtual void Update()override {};
	virtual void Render(RenderContext& rc)override {};
};


class YellowCoin : public Coin
{
public:
	YellowCoin();
	~YellowCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

class RedCoin : public Coin
{
public:
	RedCoin();
	~RedCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

class BlueCoin : public Coin
{
public:
	BlueCoin();
	~BlueCoin();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

