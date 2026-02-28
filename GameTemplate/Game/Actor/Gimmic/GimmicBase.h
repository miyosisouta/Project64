#pragma once
/*
 * StageBase.h
 * すべてのギミッククラスの基底クラス
 */

#include "Actor/Actor.h"
#include "Collision/CollisionManager.h"

class GimmicBase : public Actor
{
public:
	enum enHitReactionType
	{
		enHitReactionType_None,		// 反応なし
		enHitReactionType_PipeWarp,	// 土管に入る
		enHitReactionType_Coin,		// コインを入手
		enHitReactionType_Star		// スター入手
	};

protected:
	CollisionObject* triggerCollision_; //!< アクション用コリジョン
	uint8_t id_ = 0;	//!< 土管のID、同じIDを持っている土管同士がワープの入り口と出口になる


public:
	void SetId(uint8_t id) { id_ = id; }	//!< 土管のIDの設定
	uint8_t GetId() const { return id_; }	//!< 土管のIDの取得

	void SetPosition(Vector3 position) { transform_.m_position = position; }	//!< 土管の座標の設定
	Vector3 GetPosition() const { return transform_.m_position; }				//!< 土管の座標の取得


public:
	GimmicBase();
	virtual ~GimmicBase() {};

	virtual bool Start()override { return true; };
	virtual void Update()override {};
	virtual void Render(RenderContext& rc)override {};
	virtual enHitReactionType DoEffect() { return enHitReactionType::enHitReactionType_None; }	//ギミックにエフェクトを追加するための関数


	CollisionObject* GetTriggerCollision() const { return triggerCollision_; }	//!< アクション用コリジョンの取得
};

