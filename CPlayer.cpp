#include "framework.h"
#include "CPlayer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"

#include "Logger.h"
#include "CCollider.h"
#include "CAnimator.h"

CPlayer::CPlayer()
{
	m_layer = Layer::Character;

	m_pImg = nullptr;
	m_pIdleImg = nullptr;
	m_pMoveImg = nullptr;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	//pImg->Load(GETPATH + );

	//m_pImg = RESOURCE->LoadImg(L"Player", L"Image\\Player.bmp");
	//m_pIdleImg = RESOURCE->LoadImg(L"Player", L"Image\\PlayerAnimation.png");

	m_pMoveImg = RESOURCE->LoadImg(L"Player", L"Image\\PlayerMove.bmp");
	m_fSpeed = 100;
	SetScale(Vector(20, 20));
	SetPosition(m_vecPos);

	AddCollider(ColliderType::Rect,		0, Vector(20, 20), Vector(0, 0));
	AddCollider(ColliderType::Circle,	1, Vector(20, 20), Vector(20, 0));

	m_pAnim = new CAnimator();

	m_pAnim->CreateAnimation(L"IdleUp",			m_pMoveImg, Vector(8, 0),	Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleRightUp",	m_pMoveImg, Vector(8, 70),	Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleRight",		m_pMoveImg, Vector(8, 140), Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleRightDown",	m_pMoveImg, Vector(8, 210), Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleDown",		m_pMoveImg, Vector(8, 280), Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleLeftDown",	m_pMoveImg, Vector(8, 350), Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleLeft",		m_pMoveImg, Vector(8, 420), Vector(80, 70), Vector(83, 0), 0.1f, 7);
	m_pAnim->CreateAnimation(L"IdleLeftUp",		m_pMoveImg, Vector(8, 490), Vector(80, 70), Vector(83, 0), 0.1f, 7);

	m_pAnim->CreateAnimation(L"MoveUp",			m_pMoveImg, Vector(0, 0),	Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveRightUp",	m_pMoveImg, Vector(0, 79),	Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveRight",		m_pMoveImg, Vector(0, 158), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveRightDown",	m_pMoveImg, Vector(0, 237), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveDown",		m_pMoveImg, Vector(0, 316), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveLeftDown",		m_pMoveImg, Vector(0, 395), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveLeft",		m_pMoveImg, Vector(0, 474), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	m_pAnim->CreateAnimation(L"MoveLeftUp",	m_pMoveImg, Vector(0, 553), Vector(80, 70), Vector(83, 0), 0.1f, 16);
	
	AddComponent(m_pAnim);

	m_pAnim->Play(L"IdleDown");
	m_vecLookDir.y = 1;
}

void CPlayer::Release()
{
}

void CPlayer::Update()
{
	memset(&m_vecMoveDir, 0, sizeof(Vector));
	m_bIsMove = false;
	if (BUTTONSTAY(VK_RIGHT))
	{
		m_vecMoveDir.x = 1;
		m_bIsMove = true;
	}
	if (BUTTONSTAY(VK_LEFT))
	{
		m_vecMoveDir.x = -1;
		m_bIsMove = true;
	}
	if (BUTTONSTAY(VK_UP))
	{
		m_vecMoveDir.y = -1;
		m_bIsMove = true;
	}
	if (BUTTONSTAY(VK_DOWN))
	{
		m_vecMoveDir.y = 1;
		m_bIsMove = true;
	}

	if (m_vecMoveDir.x != 0 || m_vecMoveDir.y != 0)
	{
		m_vecPos = m_vecPos + m_vecMoveDir.Normalized() * m_fSpeed * DeltaTime;
	}
}

void CPlayer::Render()
{
	//RENDER->SetPen(PenType::Solid, RGB(0, 255, 0), 1);
	//RENDER->Rect(
	//	m_vecPos.x - m_vecScale.x, 
	//	m_vecPos.y - m_vecScale.y,
	//	m_vecPos.x + m_vecScale.x,
	//	m_vecPos.y + m_vecScale.y);

	//RENDER->Image(m_pImg,
	//	m_vecPos - (m_vecScale * 0.5f),
	//	m_vecPos + (m_vecScale * 0.5f));

	//RENDER->FillEllipse(m_vecPos, 100, Color(100, 0, 100, 0.5f));
	AnimationUpdate();

}

void CPlayer::AnimationUpdate()
{
	if (m_vecMoveDir.SqrMagnitude() > 0)
	{
		m_vecLookDir = m_vecMoveDir.Normalized();
	}
	wstring str = L"";

	if (m_bIsMove)					str += L"Move";
	else							str += L"Idle";

	if (m_vecLookDir.x > 0)			str += L"Right";
	else if(m_vecLookDir.x < 0)		str += L"Left";

	if (m_vecLookDir.y < 0)			str += L"Up";
	else if (m_vecLookDir.y > 0)	str += L"Down";

	Logger::Debug(str);

	m_pAnim->Play(str, false);
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	Logger::Debug(L"충돌 감지");
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollision)
{
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollision)
{
}


