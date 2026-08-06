#include"CPlayerIdle.h"
#include"CXCharacter.h"

//回転速度
#define ROTATIONSPEED 2.0f

void CPlayerIdle::Start(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(0, true, 60);
	mState = EState::EIDLE;//状態の種類を待機にする
}

void CPlayerIdle::Update()
{
	//Aキーで左回転、Dキーで右回転
	if (mInput.Key('D'))
	{
		CVector r = mpParent->Rotation() + CVector(0.0f, -ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
	if (mInput.Key('A'))
	{
		CVector r = mpParent->Rotation() + CVector(0.0f, ROTATIONSPEED, 0.0f);
		mpParent->Rotation(r);
	}
	if (mInput.Key('W'))
	{
		//Wキーが押されているときは歩く状態にする
		mState = EState::EWALK;
	}
	if (mInput.Key('I'))
	{
		//Iキーが押されているときは攻撃状態にする
		mState = EState::EATTACK;
	}
	if (mInput.Key(' '))
	{
		//SPACEキーが押されているときはジャンプ状態にする
		mState = EState::EJUMP;
	}
	//左マウスのカーソルが押されたら
	if (mInput.Key(VK_LBUTTON))
	{
		//double x, y;
		//mInput.MouseGetPosition(&x, &y);
		//printf("Mouse Position:x=%f,y=%f\n", x, y);
		mState = EState::EATTACK;
	}
	//Nキーが押されたら
	if (mInput.Key('N'))
	{
		//マウスカーソルを非表示にする
		mInput.MouseShowCursor(false);
	}
	//Mキーが押されたら
	if (mInput.Key('M'))
	{
		//マウスカーソルを表示する
		mInput.MouseShowCursor(true);
	}

	
}
