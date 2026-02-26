#pragma once
/*
 * UserData.h
 * ユーザーデータ管理クラス
 */
namespace DataSetting {
	enum
	{
		COIN_MAX = 100,
		COIN_MIN = 0,
		LIFE_MAX = 8,
	};
}

class UserData
{
private:
	uint8_t remaningLifes_ = 0;					//!< 所持残機数
	uint8_t lifes_ = 8;							//!< 所持HP
	uint8_t totalCoins_ = DataSetting::COIN_MIN;		//!< 合計所持コイン数
	uint8_t stageCoins_ = DataSetting::COIN_MIN;		//!< ステージ所持コイン数
	uint8_t totalStars_ = DataSetting::COIN_MIN;		//!< 合計所持スター数
	uint8_t stageStars_ = DataSetting::COIN_MIN;		//!< ステージ所持スター数


private:
	/* コンストラクタ */
	UserData(){}


public:
	/* デストラクタ */
	~UserData() {}


	/* ゲッター */
	inline const uint8_t GetUserDataLife()const { return remaningLifes_;} //!< ライフ
	inline const uint8_t GetUserDataTotalCoin()const { return totalCoins_;} //!< コイン
	inline const uint8_t GetUserDataTotalStar()const { return totalStars_;} //!< スター

	/* セッター */
	inline void SetUserDataLife(const uint8_t life) { remaningLifes_ = life; } //!< ライフ
	inline void SetUserDataStageCoin(const uint8_t coin) { stageCoins_ = coin; } //!< コイン
	inline void SetUserDataStageStar(const uint8_t star) { stageStars_ = star; } //!< スター

	/* 加える */
	/* 合計コイン数を追加 */
	void AddTotalCoin(const uint8_t value) {
		totalCoins_ += value;
		totalCoins_ = min(totalCoins_, DataSetting::COIN_MAX);
		totalCoins_ = max(totalCoins_, DataSetting::COIN_MIN);
	}
	/* ステージ内コインを追加 */
	void AddStageCoin(const uint8_t value) {
		stageCoins_ += value;
		stageCoins_ = min(stageCoins_, DataSetting::COIN_MAX);
		stageCoins_ = max(stageCoins_, DataSetting::COIN_MIN);
	}


	/******************************************** シングルトン *****************************************************/


public:
	/* インスタンスを作る */
	static void CreateInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new UserData();
		}
	}


	/* インスタンスを取得 */
	static UserData& Get()
	{
		return *instance_;
	}


	/* インスタンスを破棄 */
	static void DestroyInstance()
	{
		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

private:
	static UserData* instance_; //!< シングルトンインスタンス

};

