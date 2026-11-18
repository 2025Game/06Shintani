#include"CEnemyShield.h"
#include"CXCharacter.h"

//モデルデータの指定
#define MODEL_PATH "res\\Shield\\Shield.obj","res\\Shield\\Shield.mtl"
//静的メンバ変数の定着
CModel CEnemyShield::msModel;

CEnemyShield::CEnemyShield(CXCharacter* parent)
	:mHP(10)
{
	//親のポインタを保存
	SetParent(parent);

	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_PATH);
	}
	//モデルポインタの設定
	CCharacter3::mpModel = &msModel;
	mScale = CVector(10.00f, 10.00f, 10.00f);
	mPosition = CVector(0.0f, 0.0f, 5.0f);
	Tag(ETag::EENEMY);
	mCollider[0].Tag(ETag::EENEMY);
	mCollider[1].Tag(ETag::EENEMY);
	mCollider[2].Tag(ETag::EENEMY);
	mCollider[3].Tag(ETag::EENEMY);
	mCollider[4].Tag(ETag::EENEMY);
	mCollider[5].Tag(ETag::EENEMY);
	//コライダの設定
	//mColliderCapsule1.Tag(ETag::EENEMY);(
	mCollider[0].Set(this, &mMatrix, CVector(0.8f, 1.5f, 0.4f), CVector(-0.8f, 1.5f, 0.4f), CVector(-0.8f, 0.0f, 0.4f));
	mCollider[1].Set(this, &mMatrix, CVector(-0.8f, 0.0f, 0.4f), CVector(0.8f, 0.0f, 0.4f), CVector(0.8f, 1.5f, 0.4f));
	mCollider[2].Set(this, &mMatrix, CVector(1.3f, 1.5f, -0.8f), CVector(0.8f, 1.5f, 0.4f), CVector(0.8f, 0.0f, 0.4f));
	mCollider[3].Set(this, &mMatrix, CVector(1.3f, 1.5f, -0.8f), CVector(0.8f, 0.0f, 0.4f), CVector(1.3f, 0.0f, -0.8f));
	mCollider[4].Set(this, &mMatrix, CVector(-0.8f, 1.5f, 0.4f), CVector(-1.3f, 1.5f, -0.8f), CVector(-1.3f, 0.0f, -0.8f));
	mCollider[5].Set(this, &mMatrix, CVector(-0.8f, 1.5f, 0.4f), CVector(-1.3f, 0.0f, -0.8f), CVector(-0.8f, 0.0f, 0.4f));
}

CEnemyShield::~CEnemyShield()
{
	CTransform* parent = Parent();
	//シールドがなくなるときに、親がいたら親子関係を削除する
	if (parent != nullptr)
	{
		parent->RemoveChild(this);
	}
}



void CEnemyShield::Update()
{
	//親クラスの更新
	CTransform::Update();
	if (mHP <= 0)
	{
		//割れる演出入れる
		mEnabled = false;
	}
	//CTransform::Update();
	
}

void CEnemyShield::Render()
{
	CCharacter3::Render();
}

void CEnemyShield::Collision(CCollider* m, CCollider* o)
{
	//相手のタグがエネミーの時
	if (o->Tag() == ETag::EENEMY || o->Tag() == ETag::EENEMYBULLET || o->Tag() == ETag::EATTACKRANGE)
	{
		//衝突しない
		return;
	}
	CVector adjust;//調整用ベクトル

	
	//相手のコライダがカプセルコライダの時
	if (o->Type() == CCollider::EType::ECAPSULE)
	{
		CVector adjust;//調整用ベクトル

		/*
		
		//カプセルとカプセルの衝突判定
		if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
		{
			if (o->Tag() == ETag::EPLAYERRANGE)
			{
				return;
			}
			
				if (o->Tag() == ETag::EPLAYER)
				{
					printf("敵1に弾が当たった");
					//衝突している場合、プレイヤーの位置を調整する
					mPosition = CVector() * mMatrix + adjust;
					//親子関係がある場合
					if (m->Parent() && m->Parent()->Parent())
					{
						//親のローカル座標へ変換
						mPosition = mPosition * m->Parent()->Parent()->CombinedMatrix().Inverse();
					}

					//行列の更新
					CTransform::Update();
				}
		}*/
		//カプセルと三角コライダの衝突判定
		if (CCollider::CollisionTriangleCapsule(m, o, &adjust))
		{
			if (o->Tag() == ETag::EBULLET)
			{
				printf("敵1に弾が当たった");
				mHP--;

			}
		}
	}
	
}

void CEnemyShield::Collision()
{
	//コライダの優先度変更
	mCollider[0].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[0], COLLISIONRANGE);

	//コライダの優先度変更
	mCollider[1].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[1], COLLISIONRANGE);

	//コライダの優先度変更
	mCollider[2].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[2], COLLISIONRANGE);

	//コライダの優先度変更
	mCollider[3].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[3], COLLISIONRANGE);

	//コライダの優先度変更
	mCollider[4].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[4], COLLISIONRANGE);

	//コライダの優先度変更
	mCollider[5].ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider[5], COLLISIONRANGE);
	
}