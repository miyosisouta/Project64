#pragma once
#include<string>
/**
 * Types.h
 * エフェクトの定数や情報をまとめるクラス
 */

 /** エフェクトの種類 */
enum EffectKinds
{
	enEffectKind_Max,			//!< エフェクトの最大数
};


/** エフェクトの情報を定義 */
struct EffectInformation
{
	const char16_t* assetPath; //!< アセットパス
	EffectInformation(const char16_t* path) : assetPath(path) {} //!< EffectInformation effectInfoにてコンストラクタを呼び、アセットパスを設定 
};


/******************************** エフェクトを追加次第、コメントを外す *****************************************/ 
/** エフェクトの情報を登録 */
//static EffectInformation effectInfo[enEffectKind_Max] =
//{
//	//EffectInformation(u""),
//
//};