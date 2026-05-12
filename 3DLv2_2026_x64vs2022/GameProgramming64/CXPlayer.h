#pragma once
#ifndef CXPLAYER_E
#define CXPLAYER_E

#include "CXCharacter.h"
#include"CColliderLine.h"
#include"CCollisionManager.h"

class CXPlayer :public CXCharacter
{
public:
	CXPlayer();
	void Update() override;
	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();
private:
	CColliderLine mColliderLine;
};
#endif // !CXPLAYER_E
