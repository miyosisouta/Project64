#pragma once
class StopWatch
{
private:
	float elapsedTime_ = 0.0f; //!< 経過時間
	bool isPlay_ = false;   //!< 計測中かどうか


public:
	/* 時間の更新 */
	void UpdateTimer() 
	{
		if (!isPlay_) { return; }
		elapsedTime_ += g_gameTime->GetFrameDeltaTime();
	}

public:
	/* 時間の初期化 */
	inline void Init() { elapsedTime_ = 0.0f; }

	/* 計測開始 */
	inline void Start() { isPlay_ = true; }

	/* 計測停止 */
	inline void Stop() { isPlay_ = false; }

	/* 経過時間の取得 */
	inline float GetElapsedTime() { return elapsedTime_; }
};

