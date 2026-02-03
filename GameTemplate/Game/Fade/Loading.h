#pragma once
/*
 * Loading.h
 * ローディング画面のフェードクラス
 */
#include "TransitionFade.h"


class Loading : public TransitionFade
{
public:
	Loading();
	~Loading();
	/*  更新処理 */
	void OnUpdateFade(float ratio) override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
	/* フェードを開始と開始のための設定 */
	void PlayFade(FadeMode mode, float fadeTime, Vector3 color) override; //!< フェードを始める前の設定
};

