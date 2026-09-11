#include "tackHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Bullet.h"

tackHead::tackHead(GameObject* parent)//メンバの初期化をする所
	:GameObject(parent, "tackHead"), hModel_(-1){}

void tackHead::Initialize()//モデルの読み込み、データの用意
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void tackHead::Update(){
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y -= 5.0f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y += 5.0f;
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		const float BULLET_SPEED = 0.2f;
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");

		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);
		XMVECTOR vMove = vTop - vRoot;
		//XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);//引き算
		vMove = BULLET_SPEED * vMove;

		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		//弾を生成
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());//親をタンクにして弾
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);//弾の位置を砲塔にする
	}
}

void tackHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void tackHead::Release(){}