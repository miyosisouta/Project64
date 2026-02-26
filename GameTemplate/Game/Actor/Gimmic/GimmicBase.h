#pragma once
/*
 * StageBase.h
 * すべてのギミッククラスの基底クラス
 */

#include "Actor/Actor.h"
#include "Collision/CollisionManager.h"

class GimmicBase : public Actor
{
protected:
	CollisionObject* collision_; //!< コリジョンオブジェクト


public:
	GimmicBase();
	virtual ~GimmicBase() {};

	virtual bool Start()override { return true; };
	virtual void Update()override {};
	virtual void Render(RenderContext& rc)override {};
	virtual void AddEffect() {};	//ギミックにエフェクトを追加するための関数


	CollisionObject* GetCollision() const { return collision_; }
};

