#pragma once
#include "Engine/GameObject.h"
class Bullet :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet() {}
	void Initialize() override;//初期化
	void Update() override;//更新
	void Draw() override;//描画
	void Release() override;//開放
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }//弾の進行方向をセットする関数
private:
	int hModel_;//ハンドル
	XMFLOAT3 move_;//弾の進行方向
	const float GRAVITY = 0.007f;//重力の強さ
};