#pragma once
#include "Engine/GameObject.h"
class Tank :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Tank(GameObject* parent);
	~Tank();
	void Initialize() override;//初期化
	void Update() override;//更新
	void Draw() override;//描画
	void Release() override;//開放

private:
	int hModel_;//ハンドル
	int camType_;
	void SetFixedCam();//固定カメラの処理
};