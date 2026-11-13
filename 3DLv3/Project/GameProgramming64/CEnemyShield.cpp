#include"CEnemyShield.h"

//モデルデータの指定
#define MODEL_PATH "res\\Shield\\Shield.obj","res\\Shield\\Shield.mtl"
//静的メンバ変数の定着
CModel CEnemyShield::msModel;

CEnemyShield::CEnemyShield()
	:mHP(10)
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_PATH);
	}
	//モデルポインタの設定
	CCharacter3::mpModel = &msModel;
	mScale = CVector(10.00f, 10.00f, 10.00f);
	Tag(ETag::EENEMY);

	//コライダの設定
	mCollider[0].Set(this, &mMatrix, CVector(-1.0f, 0.0f, -1.0f), CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, -1.0f));
	mCollider[1].Set(this, &mMatrix, CVector(-1.0f, 0.0f, -1.0f), CVector(-1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, 1.0f));
}

void CEnemyShield::Update()
{
	//親クラスの更新
	CXCharacter::Update();

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

	//相手のコライダがカプセルコライダの時
	if (o->Type() == CCollider::EType::ECAPSULE)
	{
		CVector adjust;//調整用ベクトル


		//カプセルとカプセルの衝突判定
		if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
		{
			if (o->Tag() == ETag::EPLAYERRANGE)
			{
				return;
			}
				if (o->Tag() == ETag::EBULLET)
				{
					//printf("敵1に弾が当たった");
					mHP--;

				}
				if (o->Tag() == ETag::EPLAYER)
				{
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
		}
	}
}

void CEnemyShield::Collision()
{
	//コライダの優先度変更
	//mColliderCapsule1.ChangePriority();
	//衝突処理を実行
	//CCollisionManager::Instance()->Collision(&mColliderCapsule1, COLLISIONRANGE);
}