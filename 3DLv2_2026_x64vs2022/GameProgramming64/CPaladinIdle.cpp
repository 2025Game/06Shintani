#include "CPaladinIdle.h"
#include"CXCharacter.h"

#define ANIMATION_FILE "res\\paladin\\sword and shield idle.fbx.x"

int CPaladinIdle::msAnimNo = 0;

CPaladinIdle::CPaladinIdle(CXCharacter* parent)
{
	//親のポインタを保存
	mpParent = parent;
	//モデルの読み込み
	static bool first = true;
	if (first)
	{
		//アニメーションの読み込み
		parent->Model()->AddAnimationSet(ANIMATION_FILE);
		msAnimNo = parent->Model()->AnimationSet().size() - 1;
		first = false;
	}
	
}

void CPaladinIdle::Start()
{
	int animation_size =
		mpParent->Model()->AnimationSet()[msAnimNo]->MaxTime();
	//アニメーションの変更
	mpParent->ChangeAnimation(msAnimNo, true, animation_size);
	mState = EState::EIDLE;//状態の種類を待機にする
	printf("待機状態");
}

void CPaladinIdle::Update()
{
}

void CPaladinIdle::Collision(CCollider* m, CCollider* o)
{
	//自身のコライダタイプの判定
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE://カプセルコライダ

		
		//相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::EType::ECAPSULE)
		{
			CVector adjust;//調整用ベクトル
			//カプセルとカプセルの衝突判定
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				if (o->Parent()->Tag() == ETag::EPLAYER && o->Parent()->State() == EState::EATTACK && o->Tag() == ETag::ESWORD)
				{
					//相手の親のタグがプレイヤーかつ、相手の親の状態が攻撃かつ、相手のタグが剣だったらダメージ状態に切り替える
					mState = EState::EDAMAGE;//状態の種類をダメージにする
				}
			}
			
		}
		break;
	}
}
