#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"
#define HP_UI "UI\\HPUI.png"
#define SCORE_UI "UI\\ScoreUI.png"
#define SKILL_UI "UI\\SkillUI.png"
#define TIME_UI "UI\\TimeUI.png"
#define MAX_HP 5 //プレイヤーのHP
#define MAX_SHIELD 5 //プレイヤーのシールド耐久値


CUi::CUi()
	: mTime(0)
	, mHp(MAX_HP)
	, mShield(MAX_SHIELD)
	, mScore(0)
	, mPosX(0.0f)
	, mPosY(0.0f)
	, mPosZ(0.0f)

{	//フォントファイルのロード
	mFont.Load("FontWhite.png", 1, 64);
	mSfFont.Load("FontWhite.png", 1, 64);//TODO SFフォントを探して入れる
	//UIのロード
	mHpUI.Load(HP_UI);//HP&ShieldのUI
	mScoreUI.Load(SCORE_UI);//ScoreのUI
	mSkillUI.Load(SKILL_UI);//SkillのUI
	mTimeUI.Load(TIME_UI);//TimeのUI

}
void CUi::Enemy(int enemy)
{
	mEnemy = enemy;
}

void CUi::HpDamage(int damage)
{
	printf("ダメージを食らった");
	mHp -= damage;
}

int CUi::Hp()
{
	return mHp;
}



void CUi::ShieldDamage(int damage)
{
	printf("シールドが削られた");
	mShield -= damage;
}
int CUi::Shield()
{
	return mShield;
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
	mScoreUI.DrawImage(0.0f, 300.0f, 550.0f, 600.0f, 115, 2100, 520, 190);
	mSkillUI.DrawImage(500.0f, 800.0f, 0.0f, 50.0f, 210, 1840, 580, 275);
	
	mTimeUI.DrawImage(0.0f, 300.0f, 500.0f, 550.0f, 60, 2130, 560 ,110);

	// HP割合
	float hp_rate = (float)mHp / MAX_HP;

	if (hp_rate < 0.0f) hp_rate = 0.0f;
	if (hp_rate > 1.0f) hp_rate = 1.0f;
	
	// シールド割合
	float shield_rate = (float)mShield / MAX_SHIELD;

	if (shield_rate < 0.0f) shield_rate = 0.0f;
	if (shield_rate > 1.0f) shield_rate = 1.0f;
	//ShieldUIの裏を作成
	// 色を灰色にする
	glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
	glBegin(GL_QUADS);
	float shield_x = 30.0f;
	float shield_y = 25.0f;

	float shield_width = 300.0f;
	float shield_height = 15.0f;
	glVertex2f(shield_x, shield_y);
	glVertex2f(shield_x + shield_width, shield_y);
	glVertex2f(shield_x + shield_width, shield_y + shield_height);
	glVertex2f(shield_x, shield_y + shield_height);

	//HPUIの裏を作成
	glBegin(GL_QUADS);
	float hp_x = 30.0f;
	float hp_y = 5.0f;

	float hp_width = 300.0f;
	float hp_height = 15.0f;
	glVertex2f(hp_x, hp_y);
	glVertex2f(hp_x + hp_width, hp_y);
	glVertex2f(hp_x + hp_width, hp_y + hp_height);
	glVertex2f(hp_x, hp_y + hp_height);

	glEnd();
	// シールドバー描画
	// 色を青にする
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	
	glVertex2f(shield_x, shield_y);
	glVertex2f(shield_x + shield_width * shield_rate, shield_y);
	glVertex2f(shield_x + shield_width * shield_rate, shield_y + shield_height);
	glVertex2f(shield_x, shield_y + shield_height);
	
	glEnd();
	// 色を緑にする
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	// HPによって色変更
	if (hp_rate > 0.7f)
	{
		glColor3f(0.0f, 1.0f, 0.0f); // 緑
	}
	else if (hp_rate > 0.3f)
	{
		glColor3f(1.0f, 1.0f, 0.0f); // 黄
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f); // 赤
	}
	// HPバー描画
	glBegin(GL_QUADS);
	
	glVertex2f(hp_x, hp_y);
	glVertex2f(hp_x + hp_width * hp_rate, hp_y);
	glVertex2f(hp_x + hp_width * hp_rate, hp_y + hp_height);
	glVertex2f(hp_x, hp_y + hp_height);

	glEnd();
	
	// 色を白にする
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//HPUIの表示
	mHpUI.DrawImage(0.0f, 350.0f, 0.0f, 50.0f, 60, 2130, 520, 230);
	//Scoreの表示
	//文字列の設定
	sprintf(buf, "SCORE:%d", mScore);
	//文字列の描画
	mFont.Draw(30, 580, 8, 16, buf);
	//Scoreの表示
	//文字列の設定
	sprintf(buf, "%d", mTime);
	//文字列の描画
	mFont.Draw(100, 525, 8, 16, buf);
	
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
