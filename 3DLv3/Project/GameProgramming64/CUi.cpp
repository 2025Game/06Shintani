#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"

void CUi::Enemy(int enemy)
{
	mEnemy = enemy;
}

void CUi::Hp(int hp)
{
	mHp = hp;
}

CUi::CUi()
	: mTime(0)
	, mHp(0)
	, mPosX(0.0f)
	, mPosY(0.0f)
	, mPosZ(0.0f)

{	//フォントファイルのロード
	mFont.Load("FontWhite.png", 1, 64);
}

void CUi::Time(int time)
{
	mTime = time;
}

void CUi::Render()
{
	CCamera::Start(0, 800, 0, 600);	//2D描画開始
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "X:%7.2f", mPosX);
	//文字列の描画
	mFont.Draw(650, 80, 8, 16, buf);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "Y:%7.2f", mPosY);
	//文字列の描画
	mFont.Draw(650, 50, 8, 16, buf);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "Z:%7.2f", mPosZ);
	//文字列の描画
	mFont.Draw(650, 20, 8, 16, buf);
	CCamera::End();	//2D描画終了
}

void CUi::Start()
{
	mFont.Draw(36, 300, 18, 36, "START PUSH ENTER KEY!");
}

void CUi::Clear()
{
	mFont.Draw(36, 300, 18, 36, "GAME CLEAR!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");
}

void CUi::Over()
{
	mFont.Draw(36, 300, 18, 36, "GAME OVER!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");
}

void CUi::PosX(float f)
{
	mPosX = f;
}

void CUi::PosY(float f)
{
	mPosY = f;
}

void CUi::PosZ(float f)
{
	mPosZ = f;
}
