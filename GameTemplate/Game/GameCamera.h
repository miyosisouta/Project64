#pragma once
class Player;
class GameCamera
{
private:
	Transform transform_; //!< カメラの座標、回転、拡大率
	Player* target_ = nullptr;	//!< プレイヤーへのポインタ

private:
	Vector3 toCameraPos_; //!< プレイヤーからカメラまでの距離
	Vector3 toCameraOldPos_; //!< 前フレームのカメラの座標
	bool isActiveCamera_ = true; //!< カメラの操作が有効かどうか

public:
	/* ターゲットの設定 */
	void SetTarget(Player* target) { target_ = target; }

	/* カメラの操作 */
	void SetIsActiveCamera(bool isActive) { isActiveCamera_ = isActive; } //!< 操作の有効/無効設定
	bool IsActiveCamera() { return isActiveCamera_; }					  //!< 操作の有効/無効取得


public:
	GameCamera();
	~GameCamera();
	void SetUp();
	void Update();
};

