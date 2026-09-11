#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Ground.h"
#include "tackHead.h"

namespace 
{
	XMVECTOR vFront = { 0,0,1,0 };//タンクの前方向のベクトル
	const float moveSpead = 0.1f;//タンクの移動速度
	const float CAM_HEIGHT_BIAS = 0.2f;//カメラの高さのバイアス
	const float CAM_HEIGHT = 2.0f;
	const float CAM_POSITION = 7.0f;
	enum CAM_TYPE {
		FIXED_CAM,	//固定カメラ
		TPS_CAM,	//三人称視点カメラ
		TPS_CAMROT, //三人称支店カメラ（回転）
		FPS_CAM,	//一人称視点カメラ
		CAM_TYPE_MAX
	};
}

Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1), camType_(FIXED_CAM){}

Tank::~Tank(){}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
	Instantiate<tackHead>(this);//親をタンクにして砲塔を生成thisは自分自身
}

void Tank::Update()
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

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る
	//XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトルにかけると、回転したベクトルが得られる
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);

	if (Input::IsKeyDown(DIK_C)) {
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
		//0,1,2...CAM_TYPE_MAX-1の順でcamType_を切り替える
	}
	switch (camType_) {
	case FIXED_CAM://固定カメラ
		SetFixedCam();
		break;
	case TPS_CAM://三人称視点カメラ
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT;//高さを少し高く
		camPos.z = camPos.z - CAM_POSITION;//位置を少し後ろに
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
		break;
	}
	case TPS_CAMROT://三人称視点カメラ(回転)
	{
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0.0f, CAM_HEIGHT, -CAM_POSITION, 0.0f };
		vCAM = XMVector3TransformCoord(vCAM, matRot);//タンクの回転をカメラの位置に反映させる
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
		break;
	}
	case FPS_CAM://一人称視点カメラの処理
		XMFLOAT3 camPos = transform_.position_;//カメラの位置をタンクの位置にする
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);//カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);//カメラの注視点をタンクの前方にする
		Camera::SetTarget(camTarget);
		break;
	}

	if (Input::IsKey(DIK_A)) {//左に回転
		transform_.rotate_.y -= 5.0f;
	}
	if (Input::IsKey(DIK_D)) {//右に回転
		transform_.rotate_.y += 5.0f;
	}
	Debug::Log("CAMTYPE = ");
	Debug::Log(camType_, true);//後のtrueは改行するかどうか
	if (Input::IsKey(DIK_W)) {//前に進む
		vPos = vPos + moveSpead * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み
	}
	if (Input::IsKey(DIK_S)) {//前に進む
		vPos = vPos - moveSpead * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}