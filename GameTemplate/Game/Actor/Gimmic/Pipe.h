#pragma once
#include "Actor/Gimmic/GimmicBase.h"
#include "physics/BoxCollider.h"
#include "physics/RigidBody.h"

class Pipe : public GimmicBase
{
private:
	nsK2EngineLow::BoxCollider solidBoxCollider_; // 床の「形（箱）」
	nsK2EngineLow::RigidBody solidRigidBody_;     // 床の「物理挙動（質量0の剛体）」

public:
	Pipe();
	~Pipe();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	enHitReactionType DoEffect()override;
};

