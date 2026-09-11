#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Ground.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1) {}

void Enemy::Initialize()
{
	hModel_ = Model::Load("kusa.fbx");
						//モデルハンドル、開始フレーム、終了フレーム、アニメーション速度
	Model::SetAnimFrame(hModel_, 1, 100, 1.0f);
	assert(hModel_ >= 0);

	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5f);
	AddCollider(collider);
}

void Enemy::Update()
{
	//レイキャストして、浮いてたら、地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に掘られて作られている、じゃないときはもっと上から
	data.dir = { 0,-1,0 };//真下にレイを飛ばす
	Ground* pGround = (Ground*)FindObject("Ground");//Groundオブジェクトを探す
	int hGroundModel = pGround->GetModelHandle();//Groundオブジェクトのモデルのハンドルを得る
	Model::RayCast(hGroundModel, &data);//レイキャストして、地面に当たったかどうか、当たった時の距離や法線を得る

	if (data.hit == true) {
		transform_.position_.y = 0 - data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にぴったりつける
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release(){}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		KillMe();
	}
}