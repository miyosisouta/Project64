#include "stdafx.h"
#include "ActorStatus.h"
#include "Core/ParameterManager.h"

PlayerStatus::PlayerStatus()
{
	// 外部ファイルを読み込み
	ParameterManager::Get().LoadParameter<MasterPlayerStatusParameter>("Assets/Parameter/PlayerParameter.json", [](const nlohmann::json& j, MasterPlayerStatusParameter& parameter)
		{
			parameter.basicSpeed = j["basicSpeed"].get<float>();
			parameter.walkSpeed = j["walk"].get<float>();
			parameter.dashSpeed = j["run"].get<float>();
			parameter.jumpMaxHeight = j["jumpMaxHeight"].get<float>();
			parameter.fallSpeed = j["fallSpeed"].get<float>();
			parameter.radius = j["radius"].get<float>();
			parameter.height = j["height"].get<float>();
			parameter.playerHealth = j["health"].get<uint8_t>();
		});
}

PlayerStatus::~PlayerStatus()
{
	ParameterManager::Get().UnloadParameter<MasterPlayerStatusParameter>(); // 外部ファイルの解放
}

void PlayerStatus::SetUp()
{
	// 外部ファイルからパラメーターを取得してステータスに設定
	auto parameter = ParameterManager::Get().GetParameter<MasterPlayerStatusParameter>();
	basicSpeed_ = parameter->basicSpeed;	// 基本移動速度
	walkSpeed_ = parameter->walkSpeed;		// 歩く速度の乗算値
	dashSpeed_ = parameter->dashSpeed;		// 走る速度の乗算値
	jumpPower_ = parameter->jumpMaxHeight;	// ジャンプ力
	fallSpeed_ = parameter->fallSpeed;		// 落下スピード
	radius_ = parameter->radius;			// カプセルコライダーの半径
	height_ = parameter->height;			// カプセルコライダーの高さ
	health_ = parameter->playerHealth;		// プレイヤーの体力
}