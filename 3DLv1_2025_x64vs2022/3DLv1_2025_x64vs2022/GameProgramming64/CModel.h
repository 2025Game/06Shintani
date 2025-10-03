#pragma once
#ifndef CMODEL_H
#define CMODEL_H
/*
モデルクラス
モデルのデータや表示
*/
class CModel
{
public:
	//モデルファイルの入力
	//Load（モデルファイル名,マテリアルファイル名）
	void Load(const char* obj, const char* mtl);
};

#endif 
