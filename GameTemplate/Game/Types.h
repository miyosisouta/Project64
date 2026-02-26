#pragma once
/*
 * Types.h
 * ここでは様々な型定義を行う、列挙型や構造体などをまとめて管理する
 */


struct CreateClassPriority
{
	/* 生成したクラスの処理優先度をここに記入 */
	enum Enum
	{
		SceneManager = 0,		//!< シーンマネージャー
		CollisionManager = 1,	//!< 当たり判定管理
		SoundManager = 5,		//!< サウンドマネージャー
		GameEffectManager = 10,		//!< エフェクトマネージャー
		FadeManager = 100,		//!< フェードマネージャー
	};
};
