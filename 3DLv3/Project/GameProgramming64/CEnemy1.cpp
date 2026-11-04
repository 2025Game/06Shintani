#include"CEnemy1.h"
//#define GRAVITY 0.0625f//重力
#define _USE_MATH_DEFINES
#include<math.h>
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

//モデルデータの指定
#define MODEL_PATH "res\\Spaceship\\SpaceShip.obj","res\\Spaceship\\SpaceShip.mtl"
//静的メンバ変数の定着
CModel CEnemy1::msModel;

CEnemy1::CEnemy1(const CVector& pos, const CVector& rot, const CVector& scale)
	:mColliderCapsule1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -20.0f), 1.1f)
	, mColliderCapsule2(this, &mMatrix, CVector(2.0f, -1.0f, 20.0f), CVector(4.5f, -2.0f, 0.0f), 0.4f)
	, mColliderCapsule3(this, &mMatrix, CVector(-2.0f, -1.0f, 20.0f), CVector(-4.5f, -2.0f, 0.0f), 0.4f)
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_PATH);
	}
	//モデルポインタの設定
	CCharacter3::mpModel = &msModel;
	mScale = CVector(0.20f, 0.20f, 0.20f);
	//最初は待機状態
	//get()は、unique_ptrが保持しているポインタを取得する関数
	//mpState = mpIdle.get();
	//mpState->Start(this);
	//mState = mpState->State();
	//タグの設定
	Tag(ETag::EENEMY);
	mColliderCapsule1.Tag(ETag::EENEMY);
	mColliderCapsule2.Tag(ETag::EENEMY);
	mColliderCapsule3.Tag(ETag::EENEMY);
}

void CEnemy1::Update()
{
	//状態の更新
	/*mpState->Update();

	//状態の切り替え
	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState)
		{
		case EState::EIDLE:
			mpState = mpIdle.get();
			break;
		case EState::EWALK:
			mpState = mpWalk.get();
			break;
		case EState::EATTACK:
			mpState = mpAttack.get();
			break;
			//case EState::EJUMP:
				//mpState = mpJump.get();
				//break;
		default:
			break;

		}
		mpState->Start(this);
	}
	*/

	//GRAVITYの大きさだけ、下方向へ移動させる
	//mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);
	//親クラスの更新
	CXCharacter::Update();
	//カプセルコライダの更新
	mColliderCapsule1.Update();
	mColliderCapsule2.Update();
	mColliderCapsule3.Update();

	//スペースキー入力で弾発射
	if (mInput.Key(VK_LBUTTON))
	{
		if (BulletCoolTime <= 0)
		{
			if (BulletFlag == false)
			{
				CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->Position(CVector(1.5f, -3.0f, 35.0f) * mMatrix);
				bullet->Rotation(mRotation);
				bullet->Update();
				BulletFlag = true;
				BulletCoolTime = 20;
			}
			else if (BulletFlag == true)
			{
				CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->Position(CVector(-1.5f, -3.0f, 35.0f) * mMatrix);
				bullet->Rotation(mRotation);
				bullet->Update();
				BulletFlag = false;
				BulletCoolTime = 20;
			}

			//CApplication::TaskManager()->Add(bullet);
		}

	}
	/*
	else
	{
		//撃ってなかったらクールタイムをなくす
		BulletCoolTime = 0;
	}
	*/
	//弾のクールタイム
	BulletCoolTime--;

}

void CEnemy1::Collision(CCollider* m, CCollider* o)
{
	//状態クラスの衝突処理
	//mpState->Collision(m, o);
	//自身のコライダタイプの判定
	switch (m->Type())
	{


	case CCollider::EType::ECAPSULE://カプセルコライダ

		if (o == &mColliderCapsule1 || o == &mColliderCapsule2 || o == &mColliderCapsule3)
		{
			//相手のタグがエネミーの時は衝突処理を行わない
			return;
		}
		if (o->Tag() == ETag::EENEMY)
		{
			return;
		}
		//相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::EType::ECAPSULE)
		{
			CVector adjust;//調整用ベクトル
			if (o->Tag() == ETag::EBULLET)
			{
				//カプセルとカプセルの衝突判定
				if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
				{
					printf("当たった");
					//ダメージ処理を入れる
				}
			}
			else
			{
				//カプセルとカプセルの衝突判定
				if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
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

		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::EType::ETRIANGLE)
		{
			CVector adjust;//調整用ベクトル
			//三角形とカプセルの衝突判定
			if (CCollider::CollisionTriangleCapsule(o, m, &adjust))
			{
				//位置の更新
				//現在のワールドでの位置
				mPosition = (CVector() * mMatrix + adjust);
				//前方の位置を求める
				CVector forward = (CVector(0.0f, 0.0f, 1.0f) * mMatrix + adjust);

				if (o->Parent())
				{
					//親のローカル座標へ変換
					mPosition = mPosition * o->Parent()->CombinedMatrix().Inverse();
					//親のローカル座標へ変換
					forward = forward * o->Parent()->CombinedMatrix().Inverse();


				}
				//ローカルの座標の向きを求める
				forward = forward - mPosition;
				//Y軸の回転角度の度数
				//atan2f(forward.X(), forward.Z())* RAD_TO_DEG;
				mRotation = CVector(0.0f, atan2f(forward.X(), forward.Z()) * RAD_TO_DEG, 0.0f);
				//親の設定
				mpParent = o->Parent();
				//行列の更新
				CTransform::Update();
			}
		}
		//break;

	}
}

void CEnemy1::Collision()
{
	//コライダの優先度変更
	mColliderCapsule1.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mColliderCapsule1, COLLISIONRANGE);
	//コライダの優先度変更
	mColliderCapsule2.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mColliderCapsule2, COLLISIONRANGE);
	//コライダの優先度変更
	mColliderCapsule3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mColliderCapsule3, COLLISIONRANGE);
}

void CEnemy1::Init(CModelX* model)
{
	//CXCharacter::Init(model);
}

void CEnemy1::Render()
{
	CCharacter3::Render();
}

const CMatrix& CEnemy1::FrameCombinedMatrix(const char* name)
{
	//フレーム名から行列を取得する
	for (size_t i = 0; i < mpModel->Frames().size(); i++)
	{
		if (strcmp(mpModel->Frames()[i]->name(), name) == 0)
		{
			return mpModel->Frames()[i]->CombinedMatrix();
		}
	}
	static CMatrix dummy;//ダミーの行列
	return dummy;
}
