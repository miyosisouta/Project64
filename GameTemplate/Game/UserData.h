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
	};
}

class UserData
{
private:


	uint8_t remaningLifes_ = 0;					//!< 所持残機数
	uint8_t lifes_ = 8;							//!< 所持HP
	uint8_t coins_ = DataSetting::COIN_MIN;		//!< 所持コイン数
	uint8_t stars_ = DataSetting::COIN_MIN;		//!< 所持スター数


private:
	/* コンストラクタ */
	UserData(){}


public:
	/* デストラクタ */
	~UserData() {}


	/* ゲッター */
	inline const uint8_t GetUserDataLife()const { return remaningLifes_;} //!< ライフ
	inline const uint8_t GetUserDataCoin()const { return coins_;} //!< コイン
	inline const uint8_t GetUserDataStar()const { return stars_;} //!< スター

	/* セッター */
	inline void SetUserDataLife(const uint8_t life) { remaningLifes_ = life; } //!< ライフ
	inline void SetUserDataCoin(const uint8_t coin) { coins_ = coin; } //!< コイン
	inline void SetUserDataStar(const uint8_t star) { stars_ = star; } //!< スター

	/* 加える */
	void AddCoin(const uint8_t value) {	//!< ライフ
		coins_ += value;
		coins_ = min(coins_, DataSetting::COIN_MAX);
		coins_ = max(coins_, DataSetting::COIN_MIN);
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

