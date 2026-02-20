#pragma once
#include "Actor/Actor.h"

class Player;
class Controller : public Actor
{
private:
	Player* target_ = nullptr;	//!< プレイヤーへのポインタ、ステートマシンからプレイヤーの情報を得るために必要。

private:
	/** 左スティックの入力量を取得 */
	Vector3 GetStickL();
	/** 左スティックによる方向を使って回転を計算 */
	Quaternion ComputeRotation();
	/* プレイヤーが移動しているか */
	bool IsInputStickL();
public:
	void SetTarget(Player* target) { target_ = target; }

public:
	Controller();
	~Controller();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override {};
};

