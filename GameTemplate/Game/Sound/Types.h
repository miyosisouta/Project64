/**
 * Types.h
 * サウンド用の定数など必要な情報を定義するファイル
 */
#pragma once
#include <string>


 /** サウンドの種類 */
enum enSoundKind
{
	enSoundKind_SE = 0,
	
	/* SE */
	enSoundKind_decision = enSoundKind_SE,		//!< ここからSEの開始位置
	enSoundKind_SE_Max,							//!< SEの最大数
	
	/* BGM */
	enSoundKind_BGM = enSoundKind_SE_Max,		//!< BGMの開始位置
	enSoundKind_Title = enSoundKind_BGM,			//!< タイトルBGM
	enSoundKind_Max,							//!< サウンドの最大数
	enSoundKind_None = enSoundKind_Max,			//!< 総サウンド数
};


/** サウンドの情報の構造体 */
struct SoundInformation
{
	std::string assetPath;
	//
	SoundInformation(const std::string& path) : assetPath(path) {}
};


/**
 *	情報を保持
 *	流すsoundファイルをSoundInformationに格納
 */
static SoundInformation soundInformation[enSoundKind_Max] =
{
	// SE
	SoundInformation("Assets/Audio/SE/decision.wav"),	


	//BGM
	SoundInformation("Assets/Audio/BGM/title.wav"),
};

