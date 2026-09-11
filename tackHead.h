#pragma once
#include "Engine/GameObject.h"
class tackHead :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	tackHead(GameObject* parent);
	~tackHead() {}
	void Initialize() override;//初期化
	void Update() override;//更新
	void Draw() override;//描画
	void Release() override;//開放

private:
	int hModel_;//ハンドル
};