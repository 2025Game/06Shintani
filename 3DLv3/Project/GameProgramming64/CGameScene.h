#pragma once
#ifndef CGAMESCENE_H
#define CGAMESCENE_H

#include"CSceneBase.h"
#include"CModel.h"
#include"CColliderMesh.h"
#include"CCollisionManager.h"
#include"CUi.h"


//ゲームシーン
class CGameScene :public CSceneBase
{
public:
	CGameScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
	static CUi* Ui();	//UIクラスのインスタンスを取得

private:
	CModel mBackGround;//背景モデル
	CModelX mPlayer;
	CColliderMesh mColliderMesh;//メッシュコライダ
	static CUi* spUi;	//UIクラスのポインタ

	
};
#endif // !CGAMESCENE_H
