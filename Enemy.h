#include <3d/Model.h>
#include <input.h>
#include <DebugText.h>

///<summary>
///敵
/// </summary>
class Enemy {

public:
	/// <summary>
	///初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle2);

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ViewProjection viewProjection_);

	//行動フェーズ
	enum class Phase {
		Approach, //接近する
		Leave, //離脱する
	};

private:
	//ワールド変換データ
	WorldTransform worldtransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle2_ = 0u;

	Input* input_ = nullptr;

	DebugText* debugText_ = nullptr;

	//フェーズ
	Phase phase_ = Phase::Approach;

	void AccessPhaseUpdate();

	void EliminationPhaseUpdate();
};