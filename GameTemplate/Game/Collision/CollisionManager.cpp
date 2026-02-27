#include "stdafx.h"
#include "CollisionManager.h"
#include "Actor/Gimmic/Coin.h"
#include "Actor/Gimmic/Pipe.h"
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
	if (!player_) { return; }


	player_->SetPipeWarp(false);	// マイフレームfalseにしておく：ステートマシーンにて土管遷移の処理を行うため

	// ギミックリストをループして当たり判定を行う
	for (auto it = gimmicList_.begin(); it != gimmicList_.end();) 
	{
		// ギミックを取得
		GimmicBase* gimmic = *it;

		// 当たり判定があった場合
		if (gimmic->GetTriggerCollision()->IsHit(player_->GetCharaCon())) 
		{ 
			auto effectType = gimmic->AddEffect();		// ギミックの効果を発動

			switch (effectType) 
			{
				// 土管に入る処理
				case GimmicBase::enHitReactionType::enHitReactionType_PipeWarp:	
				{
					// 土管に入る処理を行う前に、X入力がされていてプレイヤーが地面についているかどうかを確認する
					if (!player_->GetStateMashine()->IsInputX() || !player_->GetCharaCon().IsOnGround()) { break; }

					uint8_t myId = gimmic->GetId();				// 土管のIDを取得
					Vector3 startPos = gimmic->GetPosition();	// 土管の座標を取得
					Vector3 endPos = Vector3::Zero;				// 土管の出口の座標を初期化


					for (auto* targetGimmic : gimmicList_)
					{
						// 「同じIDを持っている」 かつ 「自分自身ではない」 ギミックを発見したら！
						if (targetGimmic->GetId() == myId && targetGimmic != gimmic)
						{
							endPos = targetGimmic->GetPosition(); // 出口を設定
							break;
						}
					}

					player_->SetPipeWarp(true);	// プレイヤーの土管に入るフラグを立てる：ステートマシーンにて土管遷移の処理を行うため
					player_->InitPipeWarp(startPos, endPos); // 土管の入り口の座標を渡して土管遷移の初期化
					break;
				}
				default:
					break;
			}

			if (effectType != gimmic->enHitReactionType_PipeWarp)
			{
				it = gimmicList_.erase(it);	// ギミックリストから削除
			}
			else 
			{
				++it;
			}
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
