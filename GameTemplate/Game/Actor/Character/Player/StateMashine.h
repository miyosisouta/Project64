#pragma once
/*
 * StateMashine.h
 * ステート遷移管理クラス
 */

class Player;
class PlayerStatus;
class IState;
class StateMashine
{
	enum enPlayerState
	{
		Idle,	//!< 待機
		Walk,	//!< 歩き
		Run,	//!< 走り
		Jump,	//!< ジャンプ
		Fall,	//!< 落下
		Max,
	};


private:
	IState* currentState_ = nullptr; //!< 現在の状態
	IState* nextState_ = nullptr; //!< 次の状態
	IState* stateList_[enPlayerState::Max]; //!< ステートのリスト
	Player* owner_ = nullptr; //!< プレイヤーへのポインタ、ステートマシンからプレイヤーの情報を得るために必要。
	PlayerStatus* ownerStatus_ = nullptr; //!< プレイヤーステータスへのポインタ、ステートマシンからプレイヤーステータスの情報を得るために必要。

	Vector3 position_; //!< 座標
	Vector3 scale_; //!< 拡大率
	Vector3 direction_; //!< 方向
	Quaternion rotation_; //!< 回転
	Vector3 moveVector_; //!< 移動ベクトル
	float inputAmount_ = 0.0f; //!< 入力量
	bool isInputA_ = false;	//!< Aボタン入力フラグ
	bool isInputB_ = false;	//!< Bボタン入力フラグ
	bool isInputX_ = false;	//!< Xボタン入力フラグ
	bool isInputY_ = false;	//!< Yボタン入力フラグ


public:
	/* Aボタン入力 */
	inline void SetInputA(bool isInput) { isInputA_ = isInput; }	//!< 設定
	inline bool IsInputA() const { return isInputA_; }				//!< 取得
	/* Bボタン入力 */
	inline void SetInputB(bool isInput) { isInputB_ = isInput; }	//!< 設定
	inline bool IsInputB() const { return isInputB_; }				//!< 取得
	/* Xボタン入力 */
	inline void SetInputX(bool isInput) { isInputX_ = isInput; }	//!< 設定
	inline bool IsInputX() const { return isInputX_; }				//!< 取得
	/* Yボタン入力 */
	inline void SetInputY(bool isInput) { isInputY_ = isInput; }	//!< 設定
	inline bool IsInputY() const { return isInputY_; }				//!< 取得


	/* 座標 */
	inline void SetPosition(const Vector3& position) { position_ = position; }	//!< 設定
	inline Vector3 GetPosition() const { return position_; }					//!< 取得
	/* 拡大 */
	inline void SetScale(const Vector3& scale) { scale_ = scale; }		//!< 設定
	inline Vector3 GetScale() const { return scale_; }					//!< 取得
	/* 回転 */
	inline void SetRotation(const Quaternion& rotation) { rotation_ = rotation; }	//!< 設定
	inline Quaternion GetRotation() const { return rotation_; }						//!< 取得


	/* 方向 */
	inline void SetDirection(const Vector3& direction) { direction_ = direction; }	//!< 設定
	inline Vector3 GetDirection() const { return direction_; }						//!< 取得

	/* 入力量 */
	inline void SetInputAmount(float amount) { inputAmount_ = amount; }		//!< 設定
	inline float GetInputAmount() const { return inputAmount_; }			//!< 取得

	/* 移動ベクトル */
	inline void SetMoveVector(const Vector3& moveVector) { moveVector_ = moveVector; }	//!< 設定
	inline Vector3 GetMoveVector() const { return moveVector_; }						//!< 取得

	/* プレイヤー */
	inline void SetPlayer(Player* player) { owner_ = player; }	//!< プレイヤーの設定
	inline Player* GetPlayer() const { return owner_; }		//!< プレイヤーの取得

	/* プレイヤーステータス */
	inline void SetPlayerStatus(PlayerStatus* status) { ownerStatus_ = status; }	//!< プレイヤーステータスの設定
	inline PlayerStatus* GetPlayerStatus() const { return ownerStatus_; }			//!< プレイヤーステータスの取得


public:
	StateMashine();
	~StateMashine();

	/* ステートマシンの更新 */
	void Update();

	/* ステートマシンの初期化 */
	void Setup(Player* player);

	/* ステートを遷移するかどうか */
	void ChangeState();

	/* ステートをチェンジするかどうか条件式を並べたもの */
	void CheckChangeState();

	/* 歩きステートに変更するか*/
	bool ChangeStateWalk();
	/* 走りステートに変更するか*/
	bool ChangeStateRun();
	/* ジャンプステートに変更するか*/
	bool ChangeStateJump();
};

