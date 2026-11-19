#ifndef CENENYSHIELD_H
#define CENENYSHIELD_H
#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCollisionManager.h"
#include"CColliderTriangle.h"

class CXCaracter;

class CEnemyShield :public CCharacter3
{

public:
	CEnemyShield(CCharacter3* parent);
	~CEnemyShield();
	void Update();
	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void Collision();

	void Render() override;
private:

	//モデルのインスタンス
	static CModel msModel;
	//CColliderCapsule mColliderCapsule1;//カプセルコライダ
	CColliderTriangle mCollider[6];
	int mHp;//HP

};


#endif // !CENENYSHIELD_H
