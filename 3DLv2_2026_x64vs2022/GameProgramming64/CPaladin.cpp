#include"CPaladin.h"

#define PALADIN_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
#define GRAVITY 0.0625f//重力
#define _USE_MATH_DEFINES
#include<math.h>
//ラジアンを度数に変換するための定数
const float RAD_TO_DEG = 180.0f / (float)M_PI;
CModelX CPaladin::msModel;


CPaladin::CPaladin(const CVector& pos, const CVector& rot, const CVector& scale)
	:mCollider(this,&mCombinedMatrix,CVector(0.0f,4.0f,0.0f),CVector(0.0f,0.0f,0.0f),0.5f)
{
	//static変数は初期値の状態で一つだけ作成され削除されない
	//一つ作成されたらその後初期値の代入はされない
	static bool first = true;
	if (first)
	{
		msModel.Load(PALADIN_MODEL);
		first = false;
	}
	Init(&msModel);
	mPosition = pos;
	mRotation = rot;
	mScale = scale;

	//待機状態の作成
	mpIdle = std::make_unique<CPaladinIdle>(this);
	//ダメージ状態の作成
	mpDamage = std::make_unique<CPaladinDamage>(this);

	mpState = mpIdle.get();
	mpState->Start();
	mState = mpState->State();

}

void CPaladin::Update()
{
	
	//状態の更新
	mpState->Update();

	//状態の切り替え
	if (mState != mpState->State())
	{
		mState = mpState->State();
		switch (mState)
		{
		case EState::EIDLE:
			mpState = mpIdle.get();
			break;
		case EState::EDAMAGE:
			mpState = mpDamage.get();
			break;
		default:
			break;

		}
		mpState->Start();
	}
	CXCharacter::Update();
	mCollider.Update();

	//GRAVITYの大きさだけ、下方向へ移動させる
	mPosition = mPosition - CVector(0.0f, GRAVITY, 0.0f);
}

void CPaladin::Collision(CCollider* m, CCollider* o)
{
	//状態クラスの衝突処理
	mpState->Collision(m, o);
	//自身のコライダタイプの判定
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE://カプセルコライダ
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
		
		//相手のコライダがカプセルコライダの時
		/*if (o->Type() == CCollider::EType::ECAPSULE)
		{
			if (o->Parent()->Tag() == ETag::EPLAYER && o->Parent()->State() == EState::EATTACK && o->Tag() == ETag::ESWORD)
			{
				//相手の親のタグがプレイヤーかつ、相手の親の状態が攻撃かつ、相手のタグが剣だったらダメージ状態に切り替える
				mState = EState::EDAMAGE;//状態の種類をダメージにする
				
			}
		}*/
	}
}

void CPaladin::Collision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突所折を実行
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);

}