#pragma once

class YellowCoin;
class RedCoin;
class BlueCoin;
class Pipe;
class StaticObject;
class Star;
/*
 * StageLoader.h
 * ステージ読み込みクラス
 */
class StageLoader
{
private:
	/* クラス */
	LevelRender levelRender_;
	YellowCoin* yellowCoin_ = nullptr;
	RedCoin* redCoin_ = nullptr;
	BlueCoin* blueCoin_ = nullptr;
	Pipe* pipe_ = nullptr;
	StaticObject* staticObject_ = nullptr;
	Star* star_ = nullptr;

	/* コンテナ */
	std::vector<YellowCoin*> yellowCoinList_;
	std::vector<RedCoin*> redCoinList_;
	std::vector<BlueCoin*> blueCoinList_;
	std::vector<Pipe*> pipeList_;
	std::vector<StaticObject*> staticObjectList_;
	std::vector<Star*> starList_;


public:
	/*
	 * ステージの読み込み
	 * path : tklファイルのパス
	 */
	void LoadStage(const char* path);

	/* ステージのアンロード */
	void UnloadStage();



public:
	StageLoader();
	~StageLoader();

	/* 更新処理 */
	void Update();
	/* 描画処理 */
	void Render(RenderContext& rc);
};

