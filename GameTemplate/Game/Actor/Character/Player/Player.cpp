#include "stdafx.h"
#include "Player.h"


namespace
{
	struct AnimationData
	{
		const char* filename;
		bool loop;
	};

	AnimationData animationDataList[] =
	{
		AnimationData{"Assets/animData/idle.tka", true},
		AnimationData{"Assets/animData/walk.tka", true},
		AnimationData{"Assets/animData/run.tka", true},
		AnimationData{"Assets/animData/jump.tka", false},
	};
	static_assert(ARRAYSIZE(animationDataList) == static_cast<uint8_t>(Player::enPlayerAnimaitonState::Max), "アニメーション数があっていません！");
}


Player::Player()
{
	status_ = CreateStatus<PlayerStatus>(); // ステータスの生成

	stateMashine_ = std::make_unique<StateMashine>(); // ステートマシンの生成
	stateMashine_->Setup(this); // ステートマシンの初期化
}

Player::~Player()
{
}

bool Player::Start()
{
	for (int i = 0; i < enPlayerAnimaitonState::Max; i++)
	{
		animationClipList_[i].Load(animationDataList[i].filename); // アニメーションクリップのロード
		animationClipList_[i].SetLoopFlag(animationDataList[i].loop); // ループフラグの設定
	}


	model_.Init("Assets/modelData/Character/Player/unityChan.tkm", animationClipList_, enPlayerAnimaitonState::Max, enModelUpAxisY); // モデルの初期化
	CreateCharaCon();
	CollisionHitManager::Get().SetPlayer(this); // 当たり判定管理クラスにプレイヤーを登録
	
	isBind_ = true; // 移動できるようにする
	isDraw_ = true; // 描画できるようにする

	// test : 当たり判定を可視化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Player::Update()
{
	// ステートマシンの更新
	stateMashine_->Update();

	// 移動処理
	Vector3 moveVector = stateMashine_->GetMoveVector(); // 移動ベクトルを取得
	if (moveVector.LengthSq() >= 0.01f || !isBind_)
	{
		const Vector3& position = charaCon_.Execute(moveVector, 1.0f); // あえて1.0f
		// 判定処理結果の座標を設定
		transform_.m_localPosition = position;
		transform_.m_localRotation.SetRotationYFromDirectionXZ(moveVector); // プレイヤーが移動している方向
	}

	transform_.UpdateTransform();
	stateMashine_->SetPosition(transform_.m_position); // ステートマシンに座標設定
	model_.SetPosition(transform_.m_position); // モデルに座標設定
	model_.SetRotation(transform_.m_rotation); // モデルに回転設定
	model_.SetScale(transform_.m_scale); // モデルに拡大率設定

	model_.Update();
}

void Player::Render(RenderContext& rc)
{
	if (!isDraw_) { return; }

	model_.Draw(rc);
}

void Player::InitPipeWarp(Vector3 start, Vector3 end, bool inFlag)
{
	stateMashine_->SetPipeWarpStatus(start, end); // 入った地点と出る地点をステートマシンに設定
	isPipeWarp_ = inFlag; // 土管に入れるように設定
	isBind_ = false; //操作不能にする
}
	
