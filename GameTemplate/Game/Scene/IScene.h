#pragma once
/*
 * TransitionFade.h
 * フェードの基底クラス
 */

class LerpTimer;
class IScene
{
protected:
	LerpTimer* fadeTimer; //!< フェード用タイマー


public:
	IScene();
	virtual ~IScene();

	/* 初期化処理 */
	virtual void Enter() = 0;
	/* 更新処理 */
	virtual void Update() = 0;
	/*
	 * 終わりの処理 
	 * 何かしらの削除処理をここで行う
	 */
	virtual void Exit() = 0;

	/* 描画処理 */
	virtual void Render(RenderContext& rc) = 0;
};

