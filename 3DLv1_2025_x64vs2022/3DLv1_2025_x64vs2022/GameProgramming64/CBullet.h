#pragma once
#ifndef CBULLET_H
#define CBULLET_H
//キャラクタークラスのインクルード
#include "CCharacter3.h"
//三角形クラスのインクルード
#include "CTriangle.h"
#include"CColliderh.h"
/*
弾クラス
三角形を飛ばす
*/

class CBullet : public CCharacter3
{
	//幅と奥行きの設定
public:
	//Set(幅、奥行)
	void Set(float w, float d);
	//更新
	void Update();
	//描画
	void Render();
	CBullet();

	private:
		//三角形
		CTriangle mT;
		//生存時間
		int mLife;
		CCollider mCollider;
};

#endif