#pragma once
#include "Actor/Actor.h"
#include "Actor/ActorStatus.h"
#include "Actor/Character/Player/StateMashine.h"


class Player : public Actor
{
public:
	enum enPlayerAnimaitonState : uint8_t
	{
		Idle,	//!< 待機
		Walk,	//!< 歩き
		Run,	//!< 走り
		Jump,	//!< ジャンプ
		Max,
	};

private:
	std::unique_ptr<StateMashine> stateMashine_;	//!< ステートマシン
	AnimationClip animationClipList_[enPlayerAnimaitonState::Max]; //!< アニメーションクリップのリスト
	CharacterController charaCon_; //!< キャラクターコントローラー


public:
	/* ステートマシンの取得 */
	StateMashine* GetStateMashine() { return stateMashine_.get(); }
	/* プレイヤーステータスの取得 */
	PlayerStatus* GetPlayerStatus() { return dynamic_cast<PlayerStatus*>(status_); }
	/* キャラコンの取得 */
	CharacterController& GetCharaCon() { return charaCon_; }

	/* プレイヤーが地面についているか取得 */
	bool IsOnGrounded() const { return charaCon_.IsOnGround(); }


public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
};

