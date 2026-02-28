#include "stdafx.h"
#include "StageLoader.h"
#include "Actor/Gimmic/Coin.h"
#include "Actor/Gimmic/Pipe.h"
#include "Actor/Gimmic/Star.h"
#include "Actor/Map/StaticObject.h"

namespace 
{
	constexpr uint8_t PIPE_ID_ONE = 1;
	constexpr uint8_t PIPE_ID_TWO = 2;

	constexpr uint8_t COIN_NUM_ONE = 1;
	constexpr uint8_t COIN_NUM_TWO = 2;
	constexpr uint8_t COIN_NUM_THREE = 3;

	/* ここから静的オブジェクトのアセットパスを設定 */
	constexpr const char* STATIC_OBJECT_FLATGROUND = "Assets/modelData/Stage/ObjectData/Ground.tkm";
	constexpr const char* STATIC_OBJECT_HOUSE = "Assets/modelData/Stage/ObjectData/House.tkm";
	constexpr const char* STATIC_OBJECT_LONGTREE = "Assets/modelData/Stage/ObjectData/LongTree.tkm";
	constexpr const char* STATIC_OBJECT_FLOWER = "Assets/modelData/Stage/ObjectData/Flower.tkm";
	constexpr const char* STATIC_OBJECT_WOOD = "Assets/modelData/Stage/ObjectData/Wood.tkm";
}


void StageLoader::LoadStage(const char* path)
{
	levelRender_.Init(path, [&](LevelObjectData& data) 
		{
			// 前方一致で判定
			/* 静的オブジェクトの生成 */
			if (data.ForwardMatchName(L"Ground"))
			{
				staticObject_ = NewGO<StaticObject>(0, "Ground");
				staticObject_->GetModelRender().Init(STATIC_OBJECT_FLATGROUND);
				staticObject_->GetTransform()->m_localPosition = data.position;
				staticObject_->GetTransform()->m_localRotation = data.rotation;
				staticObject_->GetTransform()->m_localScale = data.scale;
				staticObject_->GetTransform()->UpdateTransform();
				staticObjectList_.push_back(staticObject_);
				return false;
			}
			if (data.ForwardMatchName(L"House"))
			{
				staticObject_ = NewGO<StaticObject>(0, "house");
				staticObject_->GetModelRender().Init(STATIC_OBJECT_HOUSE);
				staticObject_->GetTransform()->m_localPosition = data.position;
				staticObject_->GetTransform()->m_localRotation = data.rotation;
				staticObject_->GetTransform()->m_localScale = data.scale;
				staticObject_->GetTransform()->UpdateTransform();
				staticObjectList_.push_back(staticObject_);
				return false;
			}
			if (data.ForwardMatchName(L"LongTree"))
			{
				staticObject_ = NewGO<StaticObject>(0, "LongTree");
				staticObject_->GetModelRender().Init(STATIC_OBJECT_LONGTREE);
				staticObject_->GetTransform()->m_localPosition = data.position;
				staticObject_->GetTransform()->m_localRotation = data.rotation;
				staticObject_->GetTransform()->m_localScale = data.scale;
				staticObject_->GetTransform()->UpdateTransform();
				staticObjectList_.push_back(staticObject_);
				return false;
			}
			if (data.ForwardMatchName(L"flower"))
			{
				staticObject_ = NewGO<StaticObject>(0, "flower");
				staticObject_->GetModelRender().Init(STATIC_OBJECT_FLOWER);
				staticObject_->GetTransform()->m_localPosition = data.position;
				staticObject_->GetTransform()->m_localRotation = data.rotation;
				staticObject_->GetTransform()->m_localScale = data.scale;
				staticObject_->GetTransform()->UpdateTransform();
				staticObjectList_.push_back(staticObject_);
				return false;
			}
			if (data.ForwardMatchName(L"Wood"))
			{
				staticObject_ = NewGO<StaticObject>(0, "Wood");
				staticObject_->GetModelRender().Init(STATIC_OBJECT_WOOD);
				staticObject_->GetTransform()->m_localPosition = data.position;
				staticObject_->GetTransform()->m_localRotation = data.rotation;
				staticObject_->GetTransform()->m_localScale = data.scale;
				staticObject_->GetTransform()->UpdateTransform();
				staticObjectList_.push_back(staticObject_);
				return false;
			}

			/*------------------------*/
			/* 動的オブジェクトの生成 */
			/*------------------------*/

			/* スター */
			else if (data.ForwardMatchName(L"Star"))
			{
				star_ = NewGO<Star>(0, "star");
				star_->GetTransform()->m_localPosition = data.position;
				star_->GetTransform()->m_localRotation = data.rotation;
				star_->GetTransform()->m_localScale = data.scale;
				star_->GetTransform()->UpdateTransform();
				starList_.push_back(star_);
			}

			/* 土管 */
			else if (data.ForwardMatchName(L"Pipe01"))
			{
				pipe_ = NewGO<Pipe>(0,"pipe01");
				pipe_->GetTransform()->m_localPosition = data.position;
				pipe_->GetTransform()->m_localRotation = data.rotation;
				pipe_->GetTransform()->m_localScale = data.scale;
				pipe_->GetTransform()->UpdateTransform();
				pipe_->SetId(1);
				pipeList_.push_back(pipe_);
				return false;
			}
			else if (data.ForwardMatchName(L"Pipe02"))
			{
				pipe_ = NewGO<Pipe>(0, "pipe02");
				pipe_->GetTransform()->m_localPosition = data.position;
				pipe_->GetTransform()->m_localRotation = data.rotation;
				pipe_->GetTransform()->m_localScale = data.scale;
				pipe_->GetTransform()->UpdateTransform();
				pipe_->SetId(2);
				pipeList_.push_back(pipe_);
				return false;
			}

			/* 青コイン */
			else if (data.ForwardMatchName(L"BlueCoin"))
			{
				blueCoin_ = NewGO<BlueCoin>(0, "blueCoin");
				blueCoin_->GetTransform()->m_localPosition = data.position;
				blueCoin_->GetTransform()->m_localRotation = data.rotation;
				blueCoin_->GetTransform()->m_localScale = data.scale;
				blueCoin_->GetTransform()->UpdateTransform();			
				blueCoinList_.push_back(blueCoin_);
				return true;
			}

			/* 赤コイン */
			else if (data.ForwardMatchName(L"RedCoin"))
			{
				redCoin_ = NewGO<RedCoin>(0, "redCoin");
				redCoin_->GetTransform()->m_localPosition = data.position;
				redCoin_->GetTransform()->m_localRotation = data.rotation;
				redCoin_->GetTransform()->m_localScale = data.scale;
				redCoin_->GetTransform()->UpdateTransform();
				redCoinList_.push_back(redCoin_);
				return true;
			}

			/* 黄コイン */
			else if (data.ForwardMatchName(L"YellowCoin"))
			{
				yellowCoin_ = NewGO<YellowCoin>(0, "yellowCoin");
				yellowCoin_->GetTransform()->m_localPosition = data.position;
				yellowCoin_->GetTransform()->m_localRotation = data.rotation;
				yellowCoin_->GetTransform()->m_localScale = data.scale;
				yellowCoin_->GetTransform()->UpdateTransform();
				yellowCoinList_.push_back(yellowCoin_);
				return true;
			}

			/*------------------------*/
			/*-- クリアイベント座標 --*/
			/*------------------------*/

			else if (data.ForwardMatchName(L"ClearEventPos")) 
			{
				SceneManager::Get().InitClearEventPlayer
				(
					data.position,
					data.rotation,
					data.scale
				);
			}
		});
}

void StageLoader::UnloadStage()
{
	/* 静的オブジェクト */
	for (auto& staticObject : staticObjectList_){ DeleteGO(staticObject);}
	staticObjectList_.clear();

	/* 土管 */
	for (auto& pipe : pipeList_){ DeleteGO(pipe);}
	pipeList_.clear();

	/* 青コイン*/
	for (auto& blueCoin : blueCoinList_){ DeleteGO(blueCoin);}
	blueCoinList_.clear();

	/* 赤コイン */
	for (auto& redCoin : redCoinList_){	DeleteGO(redCoin);}
	redCoinList_.clear();

	/* 黄コイン */
	for (auto& yellowCoin : yellowCoinList_){ DeleteGO(yellowCoin);}
	yellowCoinList_.clear();

}

StageLoader::StageLoader()
{
}

StageLoader::~StageLoader()
{
	UnloadStage();
}

void StageLoader::Update()
{
}

void StageLoader::Render(RenderContext& rc)
{
	
}
