#ifndef  WARP_H
#define WARP_H
#include"CCharacter3.h"

class Warp:public CCharacter3
{
public:

	Warp();
	//更新
	void Update();
	
private:
	
	//モデルのインスタンス
	static CModel msModel;
};
#endif // ! WARP_H

