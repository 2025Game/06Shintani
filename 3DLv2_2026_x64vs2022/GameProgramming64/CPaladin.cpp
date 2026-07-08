#include"CPaladin.h"

#define PALADIN_MODEL "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"

CModelX CPaladin::msModel;

CPaladin::CPaladin(const CVector& pos, const CVector& rot, const CVector& scale)
	:mCollider(this,&mCombinedMatrix,CVector(0.0f,4.0f,0.0f),CVector(0.0f,0.0f,0.0f),0.5f)
{
	//static•Ï”‚Í‰Šú’l‚Ìó‘Ô‚Åˆê‚Â‚¾‚¯ì¬‚³‚êíœ‚³‚ê‚È‚¢
	//ˆê‚Âì¬‚³‚ê‚½‚ç‚»‚ÌŒã‰Šú’l‚Ì‘ã“ü‚Í‚³‚ê‚È‚¢
	static bool first = true;
	if (first)
	{
		msModel.Load(PALADIN_MODEL);
		first = false;
	}
	Init(&msModel);
	mPosition = pos;
	mRotation = rot;
	mScale = scale;

}

void CPaladin::Update()
{
	CXCharacter::Update();
	mCollider.Update();
}
