#pragma once
/*
 * TransitionFade.h
 * フェードの基底クラス
 */

class LerpTimer;
class TransitionFade
{
public:
	/* 現在のフェード状態 */
	enum class FadeMode
	{
		FadeOut,        //!< 表示される
		FadeIn,         //!< 表示されない
		FadeWait,       //!< フェードを待つ
		FadeMode_Max,   //!< モード数
		None            //!< 何もない
	};

	/* フェードに関するデータ構造体 */
	struct FadeData
	{
		FadeMode mode = FadeMode::FadeOut;      //!< フェードモード
		float fadeTime = 0.0f;					//!< フェード時間
		Vector3 color = Vector3::One;			//!< フェードの色
		float waitTime = 0.0f;					//!< 待機時間
	};


protected:
	LerpTimer* fadeTimer; //!< フェード用タイマー
	FadeData fadeData_;      //!< フェードに関するデータ
	FadeMode nextMode_ = FadeMode::None; //!< 次のフェードモード

	bool isPlay_ = false;       //!< フェードを再生するか
	bool isDraw_ = false;		//!< フェード画像を描画するかどうか


public:
	TransitionFade();
	virtual ~TransitionFade();

	/* 更新処理 */
	void Update();
	/* 子クラスのアップデート処理 */
	virtual void OnUpdateFade(float ratio) = 0; //!< フェードの更新処理
	/* 描画処理 */
	virtual void Render(RenderContext& rc) = 0;

	/* フェードを開始と開始のための設定 */
	virtual void PlayFade(FadeMode mode, float fadeTime, Vector3 color,float waitTime = 0.0f);


public:
	/* フェード再生 */
	inline void Play() { isPlay_ = true; }           
	/* フェード停止 */
	inline void Stop() { isPlay_ = false; }
	/* フェードしているか */
	inline bool IsPlay() { return isPlay_; }
	/* 描画中か */
	inline bool IsDraw() { return isDraw_; }
	/* 描画するかどうか */
	inline void SetIsDraw(const bool flag) { isDraw_ = flag; }
	/* モードの取得 */
	inline const FadeMode GetFadeMode() { return fadeData_.mode; }
};

