#pragma once
#include "Actor/Actor.h"
class StaticObject : public Actor
{
public:
	/* コンストラクタ */
	StaticObject();
	/* デストラクタ */
	~StaticObject();

	/* スタート処理 */
	bool Start() override;
	/* 更新処理 */
	void Update() override;
	/* 描画処理 */
	void Render(RenderContext& rc) override;
};