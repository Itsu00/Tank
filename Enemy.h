#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);
	~Enemy() {}
	void Initialize() override;//初期化
	void Update() override;//更新
	void Draw() override;//描画
	void Release() override;//開放
	void OnCollision(GameObject* pTarget) override;
private:
	int hModel_;//ハンドル
};