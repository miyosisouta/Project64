#include "stdafx.h"
#include "CollisionManager.h"
#include "Actor/Character/Player/Player.h"
#include "Actor/Gimmic/GimmicBase.h"

/*********************************** CollisionHitManager ***************************************/


CollisionHitManager* CollisionHitManager::instance_ = nullptr;


CollisionHitManager::CollisionHitManager()
{
}


CollisionHitManager::~CollisionHitManager()
{

}


void CollisionHitManager::Update()
{
	// ギミックリストをループして当たり判定を行う
	for (auto it = gimmicList_.begin(); it != gimmicList_.end();) 
	{
		// ギミックを取得
		GimmicBase* gimmic = *it;

		// 当たり判定があった場合
		if (gimmic->GetCollision()->IsHit(player_->GetCharaCon())) 
		{ 
			gimmic->AddEffect();						// ギミックの効果を発動
			it = gimmicList_.erase(it);	// ギミックリストから削除
		}
		else 
		{
			++it; // 当たらなかった場合は次のギミックへ
		}
	}
}


/*-----------------------------------------------------------------------------*/
/****************************** CollisionHitObject *****************************/
/*-----------------------------------------------------------------------------*/

CollisionHitObject::CollisionHitObject()
{
	CollisionHitManager::CreateInstance();
}

CollisionHitObject::~CollisionHitObject()
{
	CollisionHitManager::DestroyInstance();
}


void CollisionHitObject::Update()
{
	CollisionHitManager::Get().Update();
}
