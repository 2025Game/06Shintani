#include"CGameScene.h"
#include"CCharacter3.h"
#include"CTaskManager.h"
#include"CXCharacter.h"
#include"CXPlayer.h"
#include"CCube.h"
#include"CCamera.h"
#include"CPaladin.h"

//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"

CGameScene::CGameScene()
	:CSceneBase(EScene::eGame)
{

}


void CGameScene::Load()
{
	//背景データの読み込み
	mBackGround.Load(MODEL_BACKGROUND);
	//Xファイルの読み込み
	mPlayer.Load(MODEL_FILE);
	//キャラのインスタンス作成
	CCharacter3* character = new CCharacter3();
	//mPlayerのインスタンス作成
	CXCharacter* xchar = new CXPlayer();
	xchar->Init(&mPlayer);
	//キャラクタのモデルの設定
	character->Model(&mBackGround);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	//パラディンのインスタンスを生成
	CXCharacter* paladin = new CPaladin(CVector(0.0f,5.0f,-9.0f));
	//立方体インスタンスの生成
	CCharacter3* cube = new CCube;
	cube->Position(CVector(0.0f, 0.0f, -9.0f));
	cube->Scale(CVector(10.0f, 0.5f, 10.0f));
	//カメラ位置の設定
	CCamera::Instance()->Scale(CVector(0.0f, 1.0f, -7.0f));
}

void CGameScene::Update()
{
//カメラの設定
//gluLookAt(1.0f, 2.0f, 10.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//全キャラクタの更新
CTaskManager::Instance()->Update();
//衝突処理の呼び出し
CTaskManager::Instance()->Collision();
//カメラの更新
CCamera::Instance()->Update();
//全キャラクタの描画
CTaskManager::Instance()->Render();
//コライダの描画
CCollisionManager::Instance()->Render();
}