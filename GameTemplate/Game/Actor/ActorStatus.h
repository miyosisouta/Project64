#pragma once

/**
 * ステータス生成関数
 * ※必ずこの関数を呼んでステータスの生成をすること！
 * 　Factoryパターンで指定したステータスを生成してセットアップまでする
 */
template <typename TStatus>
static TStatus* CreateStatus()
{
	auto* status = new TStatus();
	status->SetUp();
	return status;
}

/*
 * アクターのステータスクラス
 */
class ActorStatus
{
public:
	ActorStatus() {}
	~ActorStatus() {}

public:
	// ステータスの設定
	virtual void SetUp() = 0;

protected:
	ActorStatus* state_ = nullptr; //!< ステータスポインタ、ステートマシンからプレイヤーの情報を得るために必要。

};



/*
 * キャラクターのステータスクラス
 */
class CharacterStatus : public ActorStatus
{
protected:
	float basicSpeed_ = 0.0f;       //!< ベースの速度
	float walkSpeed_ = 0.0f;	    //!< ベースの速度に乗算する歩き速度
	float dashSpeed_ = 0.0f;        //!< ベースの速度に乗算する走り速度
	float jumpPower_ = 0.0f;        //!< ジャンプの力
	float fallSpeed_ = 0.0f;        //!< 落下速度
	float radius_ = 0.0f;           //!< キャラクターの半径
	float height_ = 0.0f;           //!< キャラクターの高さ

public:
	// キャラクターのステータスを取得するための関数
	inline float GetBasicSpeed() const { return basicSpeed_; }	//!< ベースの速度の取得
	inline float GetWalkSpeed() const { return walkSpeed_; }	//!< 歩き速度の取得
	inline float GetRunSpeed() const { return dashSpeed_; }		//!< 走り速度の取得
	inline float GetJumpPower() const { return jumpPower_; }	//!< ジャンプ力の取得
	inline float GetFallSpeed() const { return fallSpeed_; }	//!< 落下速度の取得
	inline float GetRadius() const { return radius_; }			//!< 半径の取得
	inline float GetHeight() const { return height_; }			//!< 高さの取得

public:
	CharacterStatus() {}
	~CharacterStatus() {}

	// ステータスの設定
	virtual void SetUp() override = 0;
};



/*
 * プレイヤーのステータスクラス
 */
class PlayerStatus : public CharacterStatus
{
private:
	uint8_t health_ = 0;			//!<体力

public:
	inline uint8_t GetHealth() const { return health_; }	//!< 体力の取得


public:
	PlayerStatus();
	~PlayerStatus();

	void SetUp() override;
};