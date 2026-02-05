/**
 * SoundManager.cpp
 * サウンド管理
 * 必要なサウンドファイルを読み込んだり再生したりなど管理する
 */
#include "stdafx.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "InGameScene.h"
#include "Timer/StopWatch.h"
#include "Fade/FadeManager.h"
#include "Fade/TransitionFade.h"

SceneManager* SceneManager::instance_ = nullptr; //初期化


SceneManager::SceneManager()
{
	currentScene_ = new TitleScene();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Enter()
{
	currentScene_->Enter();
}

void SceneManager::Update()
{
	// 次のシーンに移行する必要がある場合
	if (nextSceneMode_ != SceneMode::None) 
	{
		// フェード待ち状態か確認
		if (FadeManager::Get().IsFadeWaitState())
		{
			// シーンの切り替えを実行
			ExecuteSceneChange();
		}
	}
	
	// 現在のシーンが存在する場合、現在のシーンの更新
	if (currentScene_) { currentScene_->Update(); }
}

void SceneManager::Render(RenderContext& rc)
{
	currentScene_->Render(rc);
}

void SceneManager::ChangeSceneRequest(SceneMode sceneMode)
{
	nextSceneMode_ = sceneMode;
	FadeManager::Get().PlayFade(FadeManager::FadeType::enFadeType_Color, TransitionFade::FadeMode::FadeOut, 5.0f, Vector3(1.0f, 1.0f, 1.0f),5.0f);
}


void SceneManager::ExecuteSceneChange()
{

	/***************** 現在のシーンの破棄 ******************/
	{
		delete currentScene_;
		currentScene_ = nullptr;
	}

	/***************** シーンの作成 *******************/
	{
		switch (nextSceneMode_)
		{
			case SceneMode::TitleScene:
			{
				currentScene_ = new TitleScene();
				break;
			}
			case SceneMode::StageSelectScene:
			{
				currentScene_ = new StageSelectScene();
				break;
			}
			case SceneMode::InGameScene:
			{
				currentScene_ = new InGameScene();
				break;
			}
			default:
			{
				assert(false && "不正なシーンモードです");
				break;
			}
		}
		// 初期化処理
		currentScene_->Enter();
	}
}


/*************** FadeManagerObjectクラス ***************/


SceneManagerObject::SceneManagerObject()
{
	SceneManager::CreateInstance();
}

SceneManagerObject::~SceneManagerObject()
{
	SceneManager::DestroyInstance();
}

bool SceneManagerObject::Start()
{
	SceneManager::Get().Enter();
	return true;
}

void SceneManagerObject::Update()
{
	SceneManager::Get().Update();
}

void SceneManagerObject::Render(RenderContext& rc)
{
	SceneManager::Get().Render(rc);
}
