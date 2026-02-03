/**
 * FadeManager.h
 * フェード管理クラス
 * 生成、指示、更新、破棄を行う
 */
#pragma once

class TransitionFade;
class FadeManager
{
	struct FadeType 
	{
		enum Enum
		{
			enFadeType_Color,					//!< カラーフェードタイプ
			enFadeType_Loading,					//!< ローディングフェードタイプ
			enFadeType_Max,						//!< フェードタイプの最大数
			enFadeType_Invalid = 0xffffffff,	//!< フェードタイプなし
		};
	};

private:
	TransitionFade* currentFade_ = nullptr;	//!< 現在のフェードイン・アウトクラスのポインタ
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
	void PlayFade(FadeType::Enum type, TransitionFade::FadeMode mode, float fadeTime, Vector3 color);

public:
	TransitionFade* GetCurrentFade() { return currentFade_; } //!< 現在のフェードクラスを取得
	
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