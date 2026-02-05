#pragma once
/*
 * ColorFade.h
 * アルファ値のフェードクラス
 */
#include "TransitionFade.h"


class ColorFade : public TransitionFade
{
private:
	SpriteRender fadeSprite_; //!< フェード用スプライト

public:
	ColorFade();
	~ColorFade();
	/* 更新処理 */
	void OnUpdateFade(float ratio) override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
	/* フェードを開始と開始のための設定 */
	void PlayFade(FadeMode mode, float fadeTime, Vector3 color, float waitTime = 0.0f) override; //!< フェードを始める前の設定
};

