#pragma once
#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include"CTriangle.h"

/*
モデルクラス
モデルのデータや表示
*/
class CModel
{
	

private:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	std::vector<CTriangle> mNormal;

public:
	//モデルファイルの入力
	//Load（モデルファイル名,マテリアルファイル名）
	void Load(const char* obj, const char* mtl);

	void Render();
};

#endif 
