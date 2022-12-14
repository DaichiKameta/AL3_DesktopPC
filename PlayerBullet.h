#include "Model.h"
#include "WorldTransform.h"


///(summary)
///自キャラの弾
/// </summary>
class PlayerBullet {
public:
	///(summary)
	///初期化
	/// </summary>
	/// <param name = "model">モデル</param>
	/// <param name = "position">初期座標</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	///(summary)
	///更新
	/// </summary>
	void Update();
	///(summary)
	///描画
	/// </summary>
	/// <param name = "ViewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& ViewProjection);

public:
	bool IsDead() const { return isDead_; }

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_;

	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;

	//デスフラグ
	bool isDead_ = false;

};