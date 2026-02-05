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

void ColorFade::PlayFade(FadeMode mode, float fadeTime, Vector3 color, float waitTime)
{
	// 親クラスの処理を実行
	// フェードの設定を行う(モード,時間,色の設定)
	TransitionFade::PlayFade(mode, fadeTime, color,waitTime);

	// ここから下に派生クラス独自の処理を追加
	// スプライトの初期化
	{
		fadeSprite_.Init("Assets/Sprite/Fade/Fade.DDS", 1920, 1080);											// 画像の読み込み
		fadeSprite_.SetMulColor(Vector4(fadeData_.color.x, fadeData_.color.y, fadeData_.color.z, MAX_ALPHA));	// スプライトの色を設定
	}
}
