#include "stdafx.h"
#include "TransitionFade.h"
#include "ColorFade.h"

namespace 
{
	constexpr float MAX_ALPHA = 1.0f;	// 完全不透明
}



ColorFade::ColorFade()
{
}

ColorFade::~ColorFade()
{
}

void ColorFade::OnUpdateFade(float ratio)
{
	fadeSprite_.SetMulColor(Vector4(fadeData_.color.x, fadeData_.color.y, fadeData_.color.z, ratio)); // スプライトの色を設定
	fadeSprite_.Update(); // スプライトの更新
}



void ColorFade::Render(RenderContext& rc)
{
	if(isDraw_)
	{
		// スプライトの描画
		fadeSprite_.Draw(rc);
	}
}

void ColorFade::PlayFade(FadeMode mode, float fadeTime, Vector3 color)
{
	// 親クラスの処理を実行
	TransitionFade::PlayFade(mode, fadeTime, color);

	// ここから下に派生クラス独自の処理を追加
}

void ColorFade::InitFadeSprite()
{
	fadeSprite_.Init("Assets/Sprite/Fade/Fade.DDS",1920,1080);
	fadeSprite_.SetMulColor(Vector4(fadeData_.color.x, fadeData_.color.y, fadeData_.color.z, MAX_ALPHA));
}
