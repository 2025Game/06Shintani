#pragma once
#ifndef CMATERIAL_H
#define CMATERIAL_H
#define MATERIAL_NAME_LEN 64//名前の長さ
#include"CTexture.h"
#include"CVertex.h"

/*
マテリアルクラス
マテリアルのデータを使う
*/
class CMaterial
{
public:
	//デフォルトコンストラクタ
	CMaterial();
	//マテリアルを有効にする
	void Enabled();
	//マテリアルの名前の取得
	char* Name();
	//マテリアルの名前を取得する
	//NAME(マテリアルの名前)
	void Name(char* name);
	//mDiffuse配列の取得
	float* Diffuse();
	//マテリアルを無効化する
	void Disabled();
	//テクスチャの取得
	CTexture* Texture();
	//頂点数の設定
	//VertexNum(頂点数
	void VertexNum(int num);
	//頂点数の取得
	int VertexNum();
	

private:
	//マテリアル名
	char mName[MATERIAL_NAME_LEN + 1];
	//拡散光の色RGBA
	float mDiffuse[4];
	//テクスチャ
	CTexture mTexture;
	//マテリアル毎の頂点数
	int mVertexNum;
};

#endif