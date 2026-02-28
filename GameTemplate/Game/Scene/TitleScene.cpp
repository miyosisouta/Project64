#include "stdafx.h"
#include "IScene.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}


void TitleScene::Enter()
{
	titleSprite.Init("Assets/Sprite/Title/testTitle.DDS", 1920.0f, 1080.0f);
	titleSprite.SetPosition(Vector3(0.0f,0.0f,0.0f));
	titleSprite.SetRotation(Quaternion::Identity);
	titleSprite.SetScale(Vector3::One);
	titleSprite.Update();
}

void TitleScene::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		SceneManager::Get().ChangeSceneRequest(SceneManager::SceneMode::InGameScene); 
	}
}

void TitleScene::Exit()
{
}

void TitleScene::Render(RenderContext& rc)
{
	// ‰¼‚Ìƒ^ƒCƒgƒ‹‰æ‘œ‚Ì•`‰æ
	titleSprite.Draw(rc);
}
