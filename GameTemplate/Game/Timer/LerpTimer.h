#pragma once
/**
 * @brief 線形補間用タイマー
 */
class LerpTimer
{
private:
	float elapsedTime_ = 0.0f; //!< 経過時間
	float targetTime_ = 0.0f;  //!< 目標時間
	bool isPlay_ = false; //!< 再生中かどうか


public:
	/* 時間の設定、初期は3秒 */
	void Init(const float time = 3.0f)
	{
		targetTime_ = time;
		elapsedTime_ = 0.0f;
		isPlay_ = true;
	}

	/**
	 * 目標時間になるまで毎フレーム時間を計算、初期は最大1.0f
	 * 使うときは更新毎に呼ぶ必要がある
	 */
	float CalcUpdate(const float ratio = 1.0f)
	{
		// 再生中でなければ何もしない
		if (!isPlay_) { return 0; }


		// 経過時間の更新
		elapsedTime_ += g_gameTime->GetFrameDeltaTime();
		// 割合を計算
		float lerpValue = min(ratio, (elapsedTime_ / targetTime_));


		// もし目標時間に達したら再生終了
		if (lerpValue >= ratio) {
			isPlay_ = false;
		}

		// 計算した値を返す
		return lerpValue;
	}

public:
	inline void Play() { isPlay_ = true; }
	inline void Stop(){	isPlay_ = false; }
	
};

