/**
 * SoundManager.cpp
 * サウンド管理
 * 必要なサウンドファイルを読み込んだり再生したりなど管理する
 */
#include "stdafx.h"
#include "FadeManager.h"
#include "TransitionFade.h"
#include "ColorFade.h"
#include "Loading.h"


FadeManager* FadeManager::instance_ = nullptr; //初期化


FadeManager::FadeManager()
{

}

FadeManager::~FadeManager()
{
	if (currentFade_) {
		delete currentFade_;
		currentFade_ = nullptr;
	}
}

void FadeManager::Update()
{
	// 現在のフェードクラスが存在する場合
	if (currentFade_) {	currentFade_->Update(); } // 現在のフェードクラスの更新
}
void FadeManager::Render(RenderContext& rc)
{
	// 現在のフェードクラスが存在する場合
	if (currentFade_) {	currentFade_->Render(rc); }// 現在のフェードクラスの描画
}


void FadeManager::CreateFade(FadeType::Enum type)
{
	switch (type)
	{
	case FadeType::enFadeType_Color:		//!< カラーフェードタイプ
		currentFade_ = new ColorFade();
		break;
	case FadeType::enFadeType_Loading:		//!< ローディングフェードタイプ
		currentFade_ = new Loading();
		break;
	default:
		// 不正なタイプ
		assert(false && "不正なフェードタイプです");
		break;
	}
}


void FadeManager::PlayFade(FadeType::Enum type, TransitionFade::FadeMode mode, float fadeTime, Vector3 color)
{
	// タイプが変わった、または現在のフェードクラスが存在しない場合
	{
		if (currentFadeType_ != type || currentFade_ == nullptr)
		{
			// 古いものを削除
			if (currentFade_) {
				delete currentFade_;
				currentFade_ = nullptr;
			}

			// 新しいものを生成（CreateFadeの中身をここに持ってきてもOK）
			CreateFade(type);
			currentFadeType_ = type;
		}
	}
	// フェードの設定
	{
		if (currentFade_) {
			currentFade_->PlayFade(mode, fadeTime, color);
		}
	}
}


/*************** FadeManagerObjectクラス ***************/


FadeManagerObject::FadeManagerObject()
{
	FadeManager::CreateInstance();
}

FadeManagerObject::~FadeManagerObject()
{
	FadeManager::DestroyInstance();
}

void FadeManagerObject::Update()
{
	FadeManager::Get().Update();
}

void FadeManagerObject::Render(RenderContext& rc)
{
	FadeManager::Get().Render(rc);
}
