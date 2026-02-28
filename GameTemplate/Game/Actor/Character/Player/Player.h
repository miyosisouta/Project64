#pragma once
#include "Actor/Actor.h"
#include "Actor/ActorStatus.h"
#include "Actor/Character/Player/StateMashine.h"


class Player : public Actor
{
public:
	enum enPlayerAnimaitonState : uint8_t
	{
		Idle,	//!< 待機
		Walk,	//!< 歩き
		Run,	//!< 走り
		Jump,	//!< ジャンプ
		Max,
	};

private:
	std::unique_ptr<StateMashine> stateMashine_;	//!< ステートマシン
	AnimationClip animationClipList_[enPlayerAnimaitonState::Max]; //!< アニメーションクリップのリスト
	CharacterController charaCon_; //!< キャラクターコントローラー

	float clearEventProgress_ = 0.0f; //!< クリアイベント内のジャンプ中の進行度
	bool isPipeWarp_ = false; //!< 土管に入るかどうか
	bool isBind_ = false; //!< 移動しているかどうか
	bool isDraw_ = false; //!< 描画するか
	bool isClearEventAction_ = false; //!< クリアイベントの動作を行うか

public:
	/* ステートマシンの取得 */
	StateMashine* GetStateMashine() { return stateMashine_.get(); }
	/* プレイヤーステータスの取得 */
	PlayerStatus* GetPlayerStatus() { return dynamic_cast<PlayerStatus*>(status_); }
	/* キャラコンの取得 */
	CharacterController& GetCharaCon() { return charaCon_; }
	
	/* キャラコンの作成 */
	void CreateCharaCon() 
	{
		charaCon_.Init(GetPlayerStatus()->GetRadius(), GetPlayerStatus()->GetHeight(), transform_.m_position); // キャラクターコントローラーの初期化
	}
	/* キャラコンの当たり判定削除 */
	void DeleteCharaCon()
	{
		charaCon_.RemoveRigidBoby();
	}

	/* プレイヤーが地面についているか取得 */
	bool IsOnGrounded() const { return charaCon_.IsOnGround(); }

	/* 土管 */
	inline bool IsPipeWarp() const { return isPipeWarp_; } //!< 土管に入るかどうかの取得
	inline void SetPipeWarp(bool isPipeWarp) { isPipeWarp_ = isPipeWarp; } //!< 土管に入るかどうかの設定
	/* 動き */
	inline bool IsBind() const { return isBind_; } //!< 拘束するかどうかの取得
	inline void SetBind(bool isBind) { isBind_ = isBind; } //!< 拘束するかどうかの設定
	/* 描画 */
	inline bool IsDraw() const { return isDraw_; } //!< 描画しているかどうかの取得
	inline void SetDraw(bool isDraw) { isDraw_ = isDraw; } //!< 描画しているかどうかの設定
	/* クリアイベント */
	inline bool IsClearEventAction() const { return isClearEventAction_; } // クリアイベント時のアクションを行うか取得
	inline void SetClearEventAction(bool flg) { isClearEventAction_ = flg; } // クリアイベント時のアクションを行うか設定
	inline float GetClearEventProgress() { return clearEventProgress_; } // クリアイベント時のジャンプの進行度を取得
	inline void SetClearEventProgress(float progress) { clearEventProgress_ = progress; } // クリアイべント時のジャンプ進行度を設定

public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;


public:
	/*
	 * 土管による遷移の初期化。
	 * start: 土管の入り口の座標, end: 土管の出口の座標, inFlag: 土管に入る遷移かどうか
	 */
	void InitPipeWarp(Vector3 start, Vector3 end, bool inFlag = true);
};

