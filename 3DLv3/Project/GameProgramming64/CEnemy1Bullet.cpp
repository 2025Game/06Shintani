#include "CEnemy1Bullet.h"
#include "CCollisionManager.h"

#define MODEL_BULLET "res\\Enemy1\\Enemy1Bullet.obj","res\\Enemy1\\Enemy1Bullet.mtl"
#define BULLETHP 300 //弾の生存時間
#define VELOCITY 0.2f
//静的メンバ変数の定着
CModel CEnemy1Bullet::msModel;

void CEnemy1Bullet::Collision(CCollider* m, CCollider* o)
{
	//コライダのmとoが衝突しているか判定
	//if (CCollider::Collision(m, o))
	//{
	if (o->Tag() == ETag::EBULLET || o->Tag() == ETag::EENEMYBULLET ||o->Tag() == ETag::EATTACKRANGE|| o->Tag() == ETag::EPLAYERRANGE )
	{
		//相手のタグがEBULLETの時は衝突処理を行わない
		return;
	}

	CVector adjust;//調整用ベクトル
	if (o->Tag() == ETag::EPLAYER)
	{
		//カプセルとカプセルの衝突判定
		if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
		{
			//プレイヤーと衝突している時は無効にする
			//printf("プレイヤーに弾が当たった");
			mEnabled = false;
		}
	}


	//}
}

CEnemy1Bullet::CEnemy1Bullet()
	: mLife(BULLETHP)
	, mColliderCapsule1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.01f), 0.5f)
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_BULLET);
	}
	//モデルポインタの設定
	mpModel = &msModel;
	Tag(ETag::EENEMYBULLET);
	mColliderCapsule1.Tag(ETag::EENEMYBULLET);
}


//幅と奥行きの設定
//Set(幅, 奥行)
void CEnemy1Bullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(0.5f, 0.5f, 0.5f);
	//三角形の頂点設定→ヒント 3
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CEnemy1Bullet::Update() {
	//	CTransform::Update();
		//位置更新　進行方向へ１進む→ヒント 17
		//mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
		//生存時間の判定
	if (mLife-- > 0) {
		CTransform::Update();
		//位置更新
		mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		mColliderCapsule1.Update();
	}
	else 
	{
		//無効にする
		mEnabled = false;
	}
}

//描画
/*
void CBullet::Render()
{

	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画→ヒント 12
	mT.Render(mMatrix);
	//mCollider.Render();
}
*/
void CEnemy1Bullet::Collision()
{
	//コライダの優先度変更
	mColliderCapsule1.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mColliderCapsule1, COLLISIONRANGE);
}