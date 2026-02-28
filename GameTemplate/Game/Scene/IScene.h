#pragma once
/*
 * TransitionFade.h
 * フェードの基底クラス
 */
#include "GameCamera.h"
#include "Actor/Character/Player/Player.h"
#include "Actor/Character/Player/Controller.h"

class StageBase;
class LerpTimer;
class IScene
{
protected:
	LerpTimer* fadeTimer; //!< フェード用タイマー
	Player* player_ = nullptr;
	Controller* controller_ = nullptr;
	GameCamera* camera_ = nullptr;
	StageBase* stage_ = nullptr;
	bool isClear_ = false;

public:
	inline void SetClearFlag(bool flg) { isClear_ = flg; }
	inline bool GetClearFlag() { return isClear_; }

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

