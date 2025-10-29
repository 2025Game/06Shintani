#pragma once
#ifndef CTRIANGLE_H
#define CTRIANGLE_H
#include"CVector.h"
/*
三角形クラス
*/
class CTriangle
{
public:
	//頂点座標設定
	//Vertex(頂点1,頂点２,頂点３)
	void Vertex(const CVector &v0, const CVector &v1, const CVector &v2);
	//法線設定
	//Normal(法線ベクトル)
	void Normal(const CVector &n);
	//Normal(法線ベクトル１,法線ベクトル2,法線ベクトル3)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//マテリアル番号の取得
	int MaterialIdx();
	//マテリアル番号の設定
	void MaterialIdx(int idx);
	//UV設定
	void UV(const CVector& v0, const CVector& v1, const CVector& v2);
	//描画
	//Render(行列)
	void Render(const CMatrix& m);

	//描画
	void Render();
private:
	CVector mV[3];//頂点座標
	CVector mN[3];//法線
	int mMaterialIdx;//マテリアル番号
	CVector mUv[3];//テクスチャマッピング

};
#endif