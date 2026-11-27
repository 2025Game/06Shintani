#pragma once
#include "CFont.h"
#include"CTexture.h"
/*
* CUi
* ユーザーインタフェースクラス
*/
class CUi
{
public:
	void PosY(float f);	//高度の設定
	void PosX(float f);	//ピッチの設定
	void PosZ(float f);	//ヨ―の設定

	//ゲームクリア表示
	void Clear();

	//ゲームオーバー表示
	void Over();

	//スタート画面
	void Start();
	void Update();
	//Enemy(倒すべき敵の残り数)
	void EnemyCount(int enemy);
	//プレイヤーのHPダメージ処理
	void HpDamage(int damage);
	//現在のHPを返す
	int Hp();
	//プレイヤーのシールドダメージ処理
	void ShieldDamage(int damage);
	//現在のシールドを返す
	int Shield();

	CUi();
	//Time(時間)
	void Time(int time);
	//Score
	void Score(int score);
	void Render();
private:
	float mPosX;	//高度　X座標
	float mPosY;	//高度　Y回転値
	float mPosZ;	//高度　Z回転値

	int mEnemy;	//敵の数
	int mHp;//HP実数
	float mViewHp;//UI用のHP
	int mShield;//シールド
	float mViewShield;//UI用のシールド
	int mTime;	//経過時間(フレーム)
	int mMin;//経過時間(分)
	int mSec1;//経過時間(秒1桁目)
	int mSec2;//経過時間(秒2桁目)
	int mScore; //スコア
	CFont mFont;
	CFont mSfFont;//SFフォント
	CTexture mHpUI;
	CTexture mScoreUI;
	CTexture mSkillUI;
	CTexture mTimeUI;
};
