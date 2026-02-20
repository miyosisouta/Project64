#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "k2EnginePreCompile.h"
using namespace nsK2EngineLow;
using namespace nsK2Engine;

/* ここにインクルードしたクラスはstdtx.hをインクルードしたすべてのクラスで使えるようになる */
/* 汎用クラスの追加 */
#include "Core/ParameterManager.h"
#include "Effect/GameEffectManager.h"
#include "Fade/FadeManager.h"
#include "json/json.hpp"
#include "Sound/SoundManager.h"
#include "Scene/SceneManager.h"
#include "Util/Transform.h"
#include "Types.h"