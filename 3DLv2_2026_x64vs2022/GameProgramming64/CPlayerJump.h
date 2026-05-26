#pragma once
#include"CState.h"
#include"CInput.h"
#include"CCollider.h"
class CPlayerJump :public CState
{
public:
	void Start(CXCharacter* parent)override;
	void Update()override;
	//衝突処理
	//Collision(コライダ１，コライダ２)
	void Collision(CCollider* m, CCollider* o)override;
private:
	CInput mInput;
	CVector mJumpV;//ジャンプの速度
};