#include "stdafx.h"
#include "TransitionFade.h"
#include "Timer/LerpTimer.h"

namespace
{
	constexpr float MAX_ALPHA = 1.0f;	// 完全不透明
	constexpr float MIN_ALPHA = 0.0f;	// 完全透明
	constexpr float TIME_ZERO = 0.0f;	// 完全透明
}

TransitionFade::TransitionFade()
	: fadeTimer(new LerpTimer()) // ★重要：タイマーの実体化
{
}

TransitionFade::~TransitionFade()
{
    if (fadeTimer) {
        delete fadeTimer;
        fadeTimer = nullptr;
    }
}

void TransitionFade::Update()
{
	if (!isPlay_) { return; } // フェード再生中でなければ何もしない


	// 現在の割合を取得
	float progress = fadeTimer->CalcUpdate();   
	// モードチェンジが必要かどうかフラグ
    bool isModeChange = (progress >= MAX_ALPHA);

	// 送信するアルファ値
	float sendToAlpha = TIME_ZERO;


	// フェードのアルファ値を決定
    switch (fadeData_.mode)
    {
    case FadeMode::FadeOut:
        sendToAlpha = progress; // 0.0 -> 1.0 (だんだん暗く)
        break;

    case FadeMode::FadeIn:
        sendToAlpha = MAX_ALPHA - progress; // 1.0 -> 0.0 (だんだん明るく)
        break;

    case FadeMode::FadeWait:
        sendToAlpha = MAX_ALPHA; // 待機中は常に真っ暗(1.0)で固定！
        break;

    default:
        break;
    }
	// フェードの更新処理
	OnUpdateFade(sendToAlpha);

	// モードチェンジが必要な場合
    if (isModeChange) 
    {
        switch (fadeData_.mode)
        {
        case FadeMode::FadeOut:
            // フェードアウト完了時
            if (fadeData_.waitTime > TIME_ZERO)
            {
                // 待ち時間があるなら Wait モードへ
                fadeData_.mode = FadeMode::FadeWait;
                fadeTimer->Init(fadeData_.waitTime);
            }
            else
            {
                // 待ち時間がないなら即座に FadeIn へ
                fadeData_.mode = FadeMode::FadeIn;
                fadeTimer->Init(fadeData_.fadeTime);
            }
            break;

        case FadeMode::FadeWait:
            // 待ち時間完了時 -> FadeIn へ
            fadeData_.mode = FadeMode::FadeIn;
            fadeTimer->Init(fadeData_.fadeTime);
            break;

        case FadeMode::FadeIn:
            // フェードイン完了時 -> 終了処理
            isPlay_ = false;
            isDraw_ = false; // 必要に応じて描画も止める
            break;

        default:
            break;
        }
    }
}

void TransitionFade::PlayFade(FadeMode mode, float fadeTime, Vector3 color, float waitTime)
{
    // データをセット
    fadeData_.mode = mode;
    fadeData_.fadeTime = fadeTime;
    fadeData_.color = color;
	fadeData_.waitTime = waitTime;

    // フラグをオン
    isPlay_ = true;
    isDraw_ = true;

    // タイマーを開始
    if (fadeTimer) {
        fadeTimer->Init(fadeTime);
    }
}
