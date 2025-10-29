#pragma once
#ifndef CMATRIX_H
#define CMATRIX_X
/*
マトリクスクラス
４行４列の行列データを扱う
*/

class CMatrix
{
public:
	//表示確認用
	//４×4の行列を画面出力
	void Print();
	//デフォルトコンストラクタ
	CMatrix();
	//単位行列の作成
	CMatrix Identity();
	//拡大縮小行列の作成
	//Scale(倍率X,倍率Y,倍率Z）
	CMatrix Scale(float sx, float sy, float sz);
	//行列値の取得
	//M(行,列)
	// mM[行][列]を取得
	float M(int r, int c)const;
	

private:
	//４×4の行列データを設定
	float mM[4][4];

};
#endif
