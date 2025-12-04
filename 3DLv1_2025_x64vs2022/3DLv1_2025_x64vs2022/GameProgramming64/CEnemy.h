#pragma once
#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include"CColliderh.h"
/*
エネミークラス
キャラクタクラスを継承
*/


class CEnemy : public CCharacter3
{
public:
	//コンストラクタ
	//ECEnemy(モデル、位置、回転、拡縮)
	CEnemy(CModel* model, const CVector& position, const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
	//確認用メソッド 削除予定
	
private:
	//コライダ
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};

#endif