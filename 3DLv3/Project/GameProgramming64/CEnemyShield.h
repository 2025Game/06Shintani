#ifndef CENENYSHIELD_H
#define CENENYSHIELD_H
#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCollisionManager.h"
#include"CColliderTriangle.h"
#include"CEnemy2.h"
class CEnemyShield :public CXCharacter
{

public:
	CEnemyShield(CXCharacter* parent);
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
	int mHP;//HP

};


#endif // !CENENYSHIELD_H
