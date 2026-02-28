/**
 * SceneManager.h
 * シーン管理クラス
 * 生成、指示、更新、破棄を行う
 */
#pragma once

class StopWatch;
class IScene;
class SceneManager
{
public:
	enum class SceneMode
	{
		None = -1,
		TitleScene,
		StageSelectScene,
		InGameScene,
		SceneMode_Max
	};

public:
	/* コンストラクタ */
	SceneManager();
	/* デストラクタ */
	~SceneManager();

	/* スタート処理 */
	void Enter();
	/* 更新処理 */
	void Update();
	/* 描画処理 */
	void Render(RenderContext& rc);
	/* シーンの切り替え */
	void ChangeSceneRequest(SceneMode sceneMode);


public:
	IScene* GetCurrentScene() { return currentScene_; }


private:
	/* 次のシーンの生成・初期化処理、現在のシーンの削除 */
	void ExecuteSceneChange();


private:
	IScene* currentScene_; //!< 現在のシーン
	SceneMode nextSceneMode_ = SceneMode::None; //!< 次のシーンモード

	

	/******************************************** シングルトン *****************************************************/


public:
	/* インスタンスを作る */
	static void CreateInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new SceneManager();
		}
	}


	/* インスタンスを取得 */
	static SceneManager& Get()
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

	/* 利用可能状態か確認する関数 */
	static bool IsAvailable()
	{
		return instance_ != nullptr;
	}

private:
	static SceneManager* instance_; //!< シングルトンインスタンス
};


//////////////////////////////////////////////////////////////////////
/******************** フェードオブジェクトクラス ********************/
//////////////////////////////////////////////////////////////////////


class SceneManagerObject : public IGameObject
{
public:
	/* コンストラクタ */
	SceneManagerObject();
	/* デストラクタ */
	~SceneManagerObject();
	/* スタート処理 */
	bool Start();
	/* 更新処理 */
	void Update();
	/* 描画処理 */
	void Render(RenderContext& rc);
};