#pragma once
#include"CState.h"
#include"CCollider.h"
class CPaladinIdle :public CState
{
public:
	CPaladinIdle(CXCharacter* parent);
	void Start() override;
	void Update() override;
	//Collision(コライダ１，コライダ２)
	void Collision(CCollider* m, CCollider* o)override;
private:
	static int msAnimNo;//アニメーション番号
};