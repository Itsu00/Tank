#pragma once
#include "Engine/GameObject.h"
class Ground :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);
	~Ground();
	void Initialize() override;//初期化
	void Update() override;//更新
	void Draw() override;//描画
	void Release() override;//開放
	int GetModelHandle() { return hModel_; }
private:
	int hModel_;//ハンドル
};