#include "Enemy.h"
#include <cassert>
#include "Function.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle2)
{
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle2_ = textureHandle2;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldtransform_.Initialize();
}

void Enemy::Update()
{



	/*worldtransform_.translation_ += move;*/


	//行列更新
	worldtransform_.matWorld_ = CreateMatIdentity();
	worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
	worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.translation_);
	worldtransform_.TransferMatrix();

	switch (phase_) {
	case Enemy::Phase::Approach:
	default:
		// 接近フェーズの更新
		AccessPhaseUpdate();
		break;
	case Enemy::Phase::Leave:
		// 離脱フェーズの更新
		EliminationPhaseUpdate();
		break;
	}
}
// 接近フェーズの更新
void Enemy::AccessPhaseUpdate() {

	Vector3 move = { 0,0,0 };
	//敵の移動の速さ
	const float kEnemySpeed = 0.02f;

	move = { 0.0f,0.0f,kEnemySpeed };


	// 移動 (ベクトルを加算)
	worldtransform_.translation_ -= move;
	// 既定の位置に到達したら離脱
	if (worldtransform_.translation_.z < -10.0f) {
		phase_ = Enemy::Phase::Leave;
	}
}

// 離脱フェーズの更新
void Enemy::EliminationPhaseUpdate() {
	Vector3 move2 = { 0,0,0 };
	//敵の移動の速さ
	const float kEnemySpeed = 0.02f;
	move2 = { kEnemySpeed ,kEnemySpeed ,0.0f };
	// 移動（ベクトルを加算）
	worldtransform_.translation_ -= move2;
}


void Enemy::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldtransform_, viewProjection_, textureHandle2_);
}