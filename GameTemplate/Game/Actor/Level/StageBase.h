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


protected:
	virtual void LoadStageData() = 0;
	virtual void UnloadStageData() = 0;
	virtual void Update();
	virtual void Render(RenderContext& rc);


protected:
	StageLoader* stageLoader_ = nullptr;
	bool isClear_ = false;

};

