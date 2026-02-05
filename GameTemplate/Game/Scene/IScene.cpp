#include "stdafx.h"
#include "IScene.h"
#include "Timer/LerpTimer.h"


IScene::IScene()
	: fadeTimer(new LerpTimer()) // ★重要：タイマーの実体化
{
}

IScene::~IScene()
{
    if (fadeTimer) {
        delete fadeTimer;
        fadeTimer = nullptr;
    }
}