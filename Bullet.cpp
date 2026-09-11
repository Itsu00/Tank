#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0, 0, 0)){}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
	Collider* collider = new SphereCollider({ 0,0,0 }, 0.25f);//半径0.5の球型の当たり判定を作る
	AddCollider(collider);//当たり判定をBulletに追加する
}

void Bullet::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	move_.y -= GRAVITY;
	XMVECTOR vMove = XMLoadFloat3(&move_);//ロード:読み込み

	vPos = vPos + vMove;
	XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み
	//transform_.position_.x = move_.x;
	//transform_.position_.y = move_.y;
	//transform_.position_.z = move_.z;

	if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f
		|| transform_.position_.x > 50.0f || transform_.position_.x < -50.0f
		|| transform_.position_.y < -3.0f)
	{
		KillMe();
	}

	//弾の弾道を重力つける
	//敵を配置（敵もレイキャストして、XZ座標ランダムで置く）
	//当たり判定（コライダーの設置）
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release(){}