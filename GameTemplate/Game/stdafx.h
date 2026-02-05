#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "k2EnginePreCompile.h"
using namespace nsK2EngineLow;
using namespace nsK2Engine;

/* ここにインクルードしたクラスはstdtx.hをインクルードしたすべてのクラスで使えるようになる */
/* 汎用クラスの追加 */
#include "Effect/GameEffectManager.h"
#include "Fade/FadeManager.h"
#include "Sound/SoundManager.h"
#include "Scene/SceneManager.h"
#include "Types.h"