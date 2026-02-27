/**
 * CollisionManager.h
 * 当たり判定管理
 */
#pragma once
class Player;
class GimmicBase;
class Coin;
class Pipe;
class CollisionHitManager
{
private:
	std::vector<GimmicBase*> gimmicList_; //!< ギミックのリスト
	Player* player_ = nullptr; //!< プレイヤーのポインタ


private:
	CollisionHitManager();
	~CollisionHitManager();

public:
	void Update();
	void RegistGimmicList(GimmicBase* gimmic) { gimmicList_.push_back(gimmic); }


public:
	void SetPlayer(Player* player) { player_ = player; }


/************************* ここからシングルトン **************************/

private:
	// インスタンス
	static CollisionHitManager* instance_;


public:
	/* インスタンスの作成 */
	static void CreateInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new CollisionHitManager();
		}
	}

	/* インスタンスの取得 */
	static CollisionHitManager& Get()
	{
		return *instance_;
	}

	/* インスタンスがあるかどうか */
	static bool IsAvailable()
	{
		return instance_ != nullptr;
	}

	/* インスタンスの削除 */
	static void DestroyInstance()
	{
		if (instance_)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}
};


/************************* 当たり判定オブジェクト **************************/
class CollisionHitObject : public IGameObject
{
public:
	CollisionHitObject();
	~CollisionHitObject();

	void Update();
};