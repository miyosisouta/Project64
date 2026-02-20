#pragma once
/*
 * StageBase.h
 * すべてのステージクラスの基底クラス
 */

class StageLoader;
class StageBase
{
public:
	StageBase();
	virtual ~StageBase();

	virtual void Update();
	virtual void Render(RenderContext& rc);

protected:
	virtual void LoadStageData() = 0;
	virtual void UnloadStageData() = 0;



protected:
	StageLoader* stageLoader_ = nullptr;
	bool isClear_ = false;

};

