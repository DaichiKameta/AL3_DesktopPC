#include "Player.h"
#include "Function.h"
#include <cassert>

/// <summary>
/// 初期化
/// 引数からモデルデータとテクスチャデータを受け取る
/// </summary>
/// <param name="model"></param>
/// <param name="textureHandle"></param>
void Player::Initialize(Model* model, uint32_t textureHandle) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldtransform_.Initialize();
}

void Player::Update()
{

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	Vector3 move = { 0,0,0 };

	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	//キャラクター旋回処理
	//押した方向で移動ベクトルを変更
	const float kCharacterRootSpeed = 0.02f;

	if (input_->PushKey(DIK_U)) {
		worldtransform_.rotation_.y -= kCharacterRootSpeed;
	}
	else if (input_->PushKey(DIK_I)) {
		worldtransform_.rotation_.y += kCharacterRootSpeed;
	}

	//キーボード入力による移動処理
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 18;

	//範囲を超えない処理
	worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	worldtransform_.translation_.x = min(worldtransform_.translation_.x, +kMoveLimitX);
	worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	worldtransform_.translation_.y = min(worldtransform_.translation_.y, +kMoveLimitY);


	worldtransform_.translation_ += move;

	//行列更新
	worldtransform_.matWorld_ = CreateMatIdentity();
	worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
	worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
	worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.translation_);
	worldtransform_.TransferMatrix();

	Attack();

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

}

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldtransform_, viewProjection_, textureHandle_);

	//弾の描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE)) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = bvector(velocity, worldtransform_);
		//弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldtransform_.translation_, velocity);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}