#include"Warp.h"

#define MODEL_WARP "res\\Gate\\Gate.obj","res\\Gate\\Gate.mtl"


//静的メンバ変数の定着
CModel Warp::msModel;

Warp::Warp()
{
	//モデルデータがなければ読み込み
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_WARP);
	}
	//モデルポインタの設定
	mpModel = &msModel;
}

void Warp::Update()
{
	CTransform::Update();
	mRotation = mRotation + (CVector(0.0f, 0.0f, 1.0f));
}