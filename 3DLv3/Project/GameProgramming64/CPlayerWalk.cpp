#include "CPlayerWalk.h"
#include"CXCharacter.h"
#include"CCamera.h"

//移動速度
#define VELOCITY 0.1f
//回転速度
#define ROTATIONSPEED 2.0f

void CPlayerWalk::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK;//状態の種類を歩くにする
}

void CPlayerWalk::Update()
{
	//カメラの右方向ベクトルを取得する
	CVector cx;
	//カメラの右方向ベクトルを取得する
	CVector cy;
	//進行すべき前方向のベクトルを取得する
	CVector cz;

	cx = CCamera::Instance()->ModelViewInverse().VectorX();
	cy = CCamera::Instance()->ModelViewInverse().VectorY();
	cz = CCamera::Instance()->ModelViewInverse().VectorZ() * -1;

	
	//プレイヤーの前方向ベクトルを取得する
	CVector fwd = mpParent->CombinedMatrix().VectorZ();
	//内積を計算して、回転量（１０度以内）を求める
	float dx = cx.Dot(fwd);
	float dy = cy.Dot(fwd);
	float dz = cz.Dot(fwd);
	if (abs(dx) < 0.01f)
	{
		if (dz < 0.0f)
		{
			dx = 1.0f;
		}
	}
	CVector rot(dy * 10.0f,dx*10.0f,0.0f);
	//プレイヤーをカメラ方向へ回転させる
	mpParent->Rotation(mpParent->Rotation() + rot);

	
	//カメラを逆回転させる
	CCamera::Instance()->Rotation(CCamera::Instance()->Rotation() - rot);

	if (mInput.Key('W'))
	{
		CVector p = mpParent->Position();
		if (mInput.Key(MK_RBUTTON))
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY*0.5);
		}
		else
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY);
		}
		
		//Wキーが押されているときは歩く状態にする
		mState = EState::EWALK;
		
	}
	else
	{
		//Wキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
	
	if (mInput.Key('A'))
	{
		CVector p = mpParent->Position();
		if (mInput.Key(MK_RBUTTON))
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorX() * VELOCITY* 0.5);
		}
		else
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorX() * VELOCITY);
		}

		//Aキーが押されているときは歩く状態にする
		mState = EState::EWALK;

	}
	else
	{
		//Aキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
	if (mInput.Key('S'))
	{
		CVector p = mpParent->Position();
		if (mInput.Key(MK_RBUTTON))
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * -1 * VELOCITY* 0.5);
		}
		else
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * -1 * VELOCITY);
		}

		//Sキーが押されているときは歩く状態にする
		mState = EState::EWALK;

		
	}
	else
	{
		//Sキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
	if (mInput.Key('D'))
	{
		CVector p = mpParent->Position();
		if (mInput.Key(MK_RBUTTON))
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorX() * -1 * VELOCITY * 0.5);
		}
		else
		{
			mpParent->Position(p + mpParent->MatrixRotate().VectorX() * -1 * VELOCITY);
		}

		//Dキーが押されているときは歩く状態にする
		mState = EState::EWALK;

		
	}
	else
	{
		//Dキーが押されていないときは待機状態にする
		mState = EState::EIDLE;
	}
}
