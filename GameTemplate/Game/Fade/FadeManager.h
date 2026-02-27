/**
 * FadeManager.h
 * フェード管理クラス
 * 生成、指示、更新、破棄を行う
 */
#pragma once
#include "TransitionFade.h"

class FadeManager
{
public:
	struct FadeType 
	{
		enum Enum
		{
			enFadeType_Invalid = -1,		//!< フェードタイプなし
			enFadeType_Color,				//!< カラーフェードタイプ
			enFadeType_Loading,				//!< ローディングフェードタイプ
			enFadeType_Max,					//!< フェードタイプの最大数
		};
	};

private:
	TransitionFade* currentFade_;	//!< 現在のフェードイン・アウトクラスのポインタ
	FadeType::Enum currentFadeType_ = FadeType::enFadeType_Invalid; //!< 現在のフェードタイプ

public:
	/* コンストラクタ */
	FadeManager();
	/* デストラクタ */
	~FadeManager();

	/* 更新処理 */
	void Update();
	/* 描画処理 */
	void Render(RenderContext& rc);

public:
	/* 
	 * フェードクラスの生成 
	 */
	void CreateFade(FadeType::Enum type);
	/* 
	 * フェードの再生 
	 * フェードを使いたいときはこれを呼ぶ
	 */
	void PlayFade(FadeType::Enum type, TransitionFade::FadeMode mode, float fadeTime, Vector3 color,float waitTime = 0.0f);

public:
	TransitionFade* GetCurrentFade() { return currentFade_; } //!< 現在のフェードクラスを取得
	TransitionFade::FadeMode GetCurrentFadeMode() { return currentFade_->GetFadeMode(); } //!< 現在のフェードタイプを取得
	

public:
	/* フェード待ち状態か */
	bool IsFadeWaitState() const;

	bool IsFadePlay() const { return currentFade_->IsPlay(); }

	/******************************************** シングルトン *****************************************************/


public:
	/* インスタンスを作る */
	static void CreateInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new FadeManager();
		}
	}


	/* インスタンスを取得 */
	static FadeManager& Get()
	{
		return *instance_;
	}


	/* インスタンスを破棄 */
	static void DestroyInstance()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

private:
	static FadeManager* instance_; //!< シングルトンインスタンス
};


/********** フェードオブジェクトクラス **********/

class FadeManagerObject : public IGameObject
{
public:
	/* コンストラクタ */
	FadeManagerObject();
	/* デストラクタ */
	~FadeManagerObject();
	/* スタート処理 */
	bool Start() { return true; }
	/* 更新処理 */
	void Update();
	/* 描画処理 */
	void Render(RenderContext& rc);
};