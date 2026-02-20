#pragma once

class StateMashine;
class IState
{
protected:
	StateMashine* owner_; //!< ステートマシンへのポインタ、ステートからステートマシンの情報を得るために必要。


public:
	/* コンストラクタ */
	IState(StateMashine* owner) : owner_(owner) {}
	/* デストラクタ */
	virtual ~IState() {}

	virtual void Enter() = 0;		//!< ステートに入るときの処理
	virtual void Update() = 0;		//!< ステートの更新処理
	virtual void Exit() = 0;		//!< ステートから出るときの処理

};

class IdleState : public IState
{
public:
	IdleState(StateMashine* owner);
	~IdleState() {}
	void Enter() override;
	void Update() override;
	void Exit() override;
};


class WalkState : public IState
{
public:
	WalkState(StateMashine* owner);
	~WalkState() {}

	void Enter() override;
	void Update() override;
	void Exit() override;
};

class RunState : public IState
{
public:
	RunState(StateMashine* owner);
	~RunState() {}
	void Enter() override;
	void Update() override;
	void Exit() override;
};

class JumpState : public IState
{
private:
	float currentPosY = 0.0f; //!< ジャンプの力

public:
	JumpState(StateMashine* owner);
	~JumpState() {}
	void Enter() override;
	void Update() override;
	void Exit() override;
};

class FallState : public IState
{
private:
		float currentPosY = 0.0f; //!< 落ちるスピード
public:
	FallState(StateMashine* owner);
	~FallState() {}
	void Enter() override;
	void Update() override;
	void Exit() override;
};



