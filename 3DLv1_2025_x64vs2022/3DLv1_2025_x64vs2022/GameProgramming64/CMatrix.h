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


private:
	//４×4の行列データを設定
	float mM[4][4];

};
#endif
