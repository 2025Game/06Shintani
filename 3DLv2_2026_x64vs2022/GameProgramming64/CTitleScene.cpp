#include"CTitleScene.h"
#include"CCamera.h"
#include"glut.h"

CTitleScene::CTitleScene()
	:CSceneBase(EScene::eTitle)
{
#ifdef DEBUG
	printf("CTitleScene()\n");
#endif // DEBUG

}

CTitleScene::~CTitleScene()
{
#ifdef DEBUG
	printf("~CTitleScene()\n");
#endif // DEBUG
}

void CTitleScene::Load()
{
	mFont.Load("FontWhite.png", 1, 64);
}

void CTitleScene::Update()
{
	CCamera::Start(0, 800, 0, 600);//2D描画開始
	//描画色の設定（赤色）
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	//文字列の描画
	mFont.Draw(400, 300, 18, 26, "CLICK");
	CCamera::End();//2D描画終了
}