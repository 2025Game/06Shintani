#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"
#define HP_UI "UI\\HPUI.png"
#define SCORE_UI "UI\\ScoreUI.png"
#define SKILL_UI "UI\\SkillUI.png"
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
	, mScore(0)
	, mPosX(0.0f)
	, mPosY(0.0f)
	, mPosZ(0.0f)

{	//フォントファイルのロード
	mFont.Load("FontWhite.png", 1, 64);
	mSfFont.Load("FontWhite.png", 1, 64);//TODO SFフォントを探して入れる
	//UIのロード
	mHpUI.Load(HP_UI);//HPのUI
	mScoreUI.Load(SCORE_UI);//ScoreのUI
	mSkillUI.Load(SKILL_UI);//SkillのUI

}

void CUi::Time(int time)
{
	mTime = time;
}

void CUi::Score(int score)
{
	mScore += score;
}

void CUi::Render()
{
	CCamera::Start(0, 800, 0, 600);	//2D描画開始
	//文字列編集エリアの作成
	char buf[64];
	//UIの表示
	mHpUI.DrawImage(0.0f, 400.0f, 0.0f, 50.0f, 60, 2130, 520, 230);
	mScoreUI.DrawImage(0.0f, 300.0f, 550.0f, 600.0f, 115, 2100, 520, 190);
	mSkillUI.DrawImage(500.0f, 800.0f, 0.0f, 50.0f, 210, 1840, 580, 275);
	//Scoreの表示
	//文字列の設定
	sprintf(buf, "SCORE:%d", mScore);
	//文字列の描画
	mFont.Draw(30, 580, 8, 16, buf);
	
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "X:%7.2f", mPosX);
	//文字列の描画
	mFont.Draw(650, 130, 8, 16, buf);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "Y:%7.2f", mPosY);
	//文字列の描画
	mFont.Draw(650, 100, 8, 16, buf);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "Z:%7.2f", mPosZ);
	//文字列の描画
	mFont.Draw(650, 70, 8, 16, buf);

	
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
