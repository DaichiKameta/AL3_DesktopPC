#include "PlayerBullet.h"
#include "Function.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
    //NULLポインタチェック
    assert(model);

    model_ = model;
    //テクスチャ読み込み
    textureHandle_ = TextureManager::Load("mario.jpg");

    //ワールド変換の初期化
    worldtransform_.Initialize();

    //引数で受け取った初期座標をセット
    worldtransform_.translation_ = position;

    //引数で受け取った速度をメンバ変数に代入
    velocity_ = velocity;

}

void PlayerBullet::Update() {

    //座標を移動させる(1フレーム分の移動量を足しこむ)
    worldtransform_.translation_ += velocity_;

    //行列更新
    worldtransform_.matWorld_ = CreateMatIdentity();
    worldtransform_.matWorld_ *= CreateMatScale(worldtransform_.scale_);
    worldtransform_.matWorld_ *= CreateMatRotationX(worldtransform_.rotation_);
    worldtransform_.matWorld_ *= CreateMatRotationY(worldtransform_.rotation_);
    worldtransform_.matWorld_ *= CreateMatRotationZ(worldtransform_.rotation_);
    worldtransform_.matWorld_ *= CreateMatTranslation(worldtransform_.translation_);
    worldtransform_.TransferMatrix();

    //時間経過でデス
    if (--deathTimer_ <= 0) {
        isDead_ = true;
    }
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

    model_->Draw(worldtransform_, viewProjection, textureHandle_);

}