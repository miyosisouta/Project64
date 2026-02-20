#pragma once
/*
 * Loading.h
 * ローディング画面のフェードクラス
 */
#include "IScene.h"

class GameCamera;
class Player;
class StageBase;
class StageSelectScene : public IScene
{
private:
	StageBase* stage_ = nullptr;


public:
	StageSelectScene();
	~StageSelectScene();
	/* スタート処理 */
	void Enter() override;
	/*  更新処理 */
	void Update() override;
	/* 終わりの処理 */
	void Exit() override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
};

