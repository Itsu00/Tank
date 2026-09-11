#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include <cstdlib>//rand()

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene"){}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をPlaysceneにして地面を生成
	Instantiate<Tank>(this);
	//Instantiate<Enemy>(this);

	const int kEnemyNum = 10;//敵の数
	const float kRange = 20.0f;//配置する範囲

	for (int i = 0; i < kEnemyNum; i++) {
		Enemy* enemy = Instantiate<Enemy>(this);
		float x = (rand() % (int)(kRange * 2) - kRange);
		float z = (rand() % (int)(kRange * 2) - kRange);
		enemy->SetPosition({ x, 0.0f, z });
	}
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}