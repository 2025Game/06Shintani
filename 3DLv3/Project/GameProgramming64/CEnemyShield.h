#ifndef CENENYSHIELD_H
#define CENENYSHIELD_H
#include"CXCharacter.h"
#include"CColliderTriangle.h"

class CEnemyShield :public CXCharacter
{

public:
	CEnemyShield();

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
	//コライダは上面だけつける
	CColliderTriangle mCollider[2];
	int mHP;//HP
};


#endif // !CENENYSHIELD_H
