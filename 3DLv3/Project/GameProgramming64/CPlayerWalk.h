#pragma once

#include"CState.h"
#include"CInput.h"

class CPlayerWalk :public CState
{
public:
	void Start(CCharacter3* parent)override;
	void Update()override;
private:
	CInput mInput;
};