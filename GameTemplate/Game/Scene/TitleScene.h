#pragma once
/*
 * ColorFade.h
 * アルファ値のフェードクラス
 */
#include "IScene.h"


class TitleScene : public IScene
{
private:
	SpriteRender titleSprite;


public:
	TitleScene();
	~TitleScene();
	/* スタート処理 */
	void Enter() override;
	/* 更新処理 */
	void Update() override;
	/* 終わりの処理 */
	void Exit() override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
};

