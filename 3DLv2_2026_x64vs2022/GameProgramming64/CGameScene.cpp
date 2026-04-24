#include"CGameScene.h"
#include"CCharacter3.h"
#include"CTaskManager.h"
#include"CXCharacter.h"

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
	CXCharacter* xchar = new CXCharacter();
	xchar->Init(&mPlayer);
	//キャラクタのモデルの設定
	character->Model(&mBackGround);
}

void CGameScene::Update()
{
//カメラの設定
gluLookAt(1.0f, 2.0f, 10.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//全キャラクタの更新
CTaskManager::Instance()->Update();
//全キャラクタの描画
CTaskManager::Instance()->Render();
}