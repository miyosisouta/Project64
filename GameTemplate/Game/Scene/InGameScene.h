#pragma once
/*
 * InGameScene.h
 * インゲームシーン
 */
#include "Scene/IScene.h"

class InGameScene : public IScene
{
public:
	InGameScene();
	~InGameScene();
	/* スタート処理 */
	void Enter() override;
	/* 更新処理 */
	void Update() override;
	/* 終わりの処理 */
	void Exit() override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
};

