#include"CEnemy1.h"
//#define GRAVITY 0.0625f//重力
#define VELOCITY 0.01f	//速度
#define BULLETTIME 60 //弾のクールタイム
#define _USE_MATH_DEFINES
#include<math.h>
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;

//モデルデータの指定
#define MODEL_PATH "res\\Enemy1\\Enemy1.obj","res\\Enemy1\\Enemy1.mtl"
//静的メンバ変数の定着
CModel CEnemy1::msModel;

CEnemy1::CEnemy1(const CVector& pos, const CVector& rot, const CVector& scale)
	:mColliderCapsule1(this, &mCombinedMatrix, CVector(0.0f, 2.0f, 5.0f), CVector(0.0f, 3.0f, -8.0f), 2.0f)
	,mAttackRenge(this, &mCombinedMatrix, CVector(-2.0f, -1.0f, 20.0f), CVector(-4.5f, -2.0f, 0.0f), 30.0f)
	,mHP(3)
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_PATH);
	}
	//モデルポインタの設定
	CCharacter3::mpModel = &msModel;
	mScale = CVector(3.00f, 3.00f, 3.00f);
	//最初は待機状態
	//get()は、unique_ptrが保持しているポインタを取得する関数
	//mpState = mpIdle.get();
	//mpState->Start(this);
	//mState = mpState->State();
	//タグの設定
	Tag(ETag::EENEMY);
	mColliderCapsule1.Tag(ETag::EENEMY);
	mAttackRenge.Tag(ETag::EATTACKRANGE);
	//目標地点の設定
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;

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
	mAttackRenge.Update();

	
	/*
	else
	{
		//撃ってなかったらクールタイムをなくす
		BulletCoolTime = 0;
	}
	*/
	//弾のクールタイム
	BulletCoolTime--;

	if (mHP <= 0)
	{
		mEnabled = false;
	}

	
}

void CEnemy1::Collision(CCollider* m, CCollider* o)
{
	//状態クラスの衝突処理
	//mpState->Collision(m, o);
	//自身のコライダタイプの判定
	switch (m->Type())
	{


	case CCollider::EType::ECAPSULE://カプセルコライダ


		//相手のタグがエネミーの時
		if (o->Tag() == ETag::EENEMY||o->Tag()==ETag::EENEMYBULLET||o->Tag()==ETag::EATTACKRANGE)
		{
			//衝突しない
			return;
		}
	}
	//相手のコライダがカプセルコライダの時
	if (o->Type() == CCollider::EType::ECAPSULE)
	{

		CVector adjust;//調整用ベクトル
		
		
			//カプセルとカプセルの衝突判定
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{

				if (m->Tag() != ETag::EATTACKRANGE)
				{
					if (o->Tag() == ETag::EBULLET)
					{
						//printf("敵1に弾が当たった");
						mHP--;
						
					}

				}

				
				

				//相手のタグがプレイヤー範囲かつ自分のタグがエネミーの時
				if (o->Tag() == ETag::EPLAYERRANGE && m->Tag() == ETag::EENEMY)
				{
					//プレイヤーに近すぎるので
					//機体を後方へ移動する
					mPosition = mPosition + mMatrixRotate.VectorZ() * -VELOCITY*5;
					//printf("攻撃しない");
					return;
				}
					//相手のタグがプレイヤーかつ自分のタグが索敵範囲の時
					if ((o->Tag() == ETag::EPLAYER && m->Tag() == ETag::EATTACKRANGE))
					{
						//if (o->Tag() == ETag::EBULLET || (o->Tag() == ETag::EPLAYERRANGE)) return;
						
						

						//printf("攻撃する");
							//printf("索敵範囲に入った");

							//プレイヤーのポインタが0以外の時
						CXPlayer* player = CXPlayer::Instance();
						//目標地点までのベクトルを求める
						CVector vp = mPoint - mPosition;

						//左ベクトルとの内積を求める
						float dx = vp.Dot(mMatrixRotate.VectorX());
						//上ベクトルとの内積を求める
						float dy = vp.Dot(mMatrixRotate.VectorY());
						//前ベクトルとの内積を求める
						float dz = vp.Dot(mMatrixRotate.VectorZ());
						const float margin = 0.1f;
						//左方向へ回転
						if (dx > margin)
						{
							//左へ回転
							mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);
						}
						else if (dx < -margin)
						{
							// //右へ回転
							mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);
						}
						//上下方向へ回転
						if (dy > margin)
						{
							//上へ回転
							mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);
						}
						else if (dy < -margin)
						{
							//下へ回転
							mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
						}

						//Z軸のずれが30.0未満の時
						if (0.0f < dz && dz > 30.0f)
						{
							//機体前方へ移動する
							mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
						}
						
						//X軸のずれが2.0未満
						if (-2.0f < dx && dx < 2.0f)
						{
							//Y軸のずれが2.0未満
							if (-2.0f < dy && dy < 2.0f)
							{
								//Z軸のずれが30.0未満
								if (0.0f < dz && dz < 40.0f)
								{
									if (BulletCoolTime <= 0)
									{
										//球を発射します
										CEnemy1Bullet* bullet = new CEnemy1Bullet();
										bullet->Set(0.1f, 1.5f);
										bullet->Position(CVector(0.0f, 0.0f, 2.0f)* mMatrix);
										bullet->Rotation(mRotation);
										bullet->Update();
										BulletCoolTime = BULLETTIME;
										//printf("弾発射");
									}
									
								}

							}

						}
						CTransform::Update();//行列更新
						//およそ3秒毎に目標地点を更新
						int r = rand() % 1;//randは整数の乱数を返す

						if (r == 0)
						{
							if (player != nullptr)
							{
								mPoint = player->Position();
							}
							else
							{
								mPoint = mPoint * CMatrix().RotateY(45);
							}
						}
						//プレイヤーを追いかける
						
					}
				
				

				
			}
			else
			{
				//カプセルとカプセルの衝突判定
				if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
				{
					/*
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
					*/
					
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


void CEnemy1::Collision()
{
	//コライダの優先度変更
	mColliderCapsule1.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mColliderCapsule1, COLLISIONRANGE);
	
	//コライダの優先度変更
	mAttackRenge.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mAttackRenge, COLLISIONRANGE);
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
