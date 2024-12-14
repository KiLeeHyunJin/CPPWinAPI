#include "framework.h"

#include "CCollisionManager.h"
#include "CSceneManager.h"

#include "CScene.h"
#include "CGameObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrLayer[0][0] = { false };
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
}

void CCollisionManager::PhysicsUpdate()
{
	for (int left = 0; left < (int)Layer::Size; left++)
	{
		for (int right = left; right < (int)Layer::Size; right++)
		{
			if (m_arrLayer[left][right])
			{
				CollisionUpdate((Layer)left, (Layer)right);
			}
		}
	}
}

void CCollisionManager::CollisionUpdate(Layer leftLayer, Layer rightLayer)
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& leftListObj = pCurScene->m_listObj[(int)leftLayer];
	const list<CGameObject*>& rightListObj = pCurScene->m_listObj[(int)rightLayer];

	for (CGameObject* pLeftObj : leftListObj)
	{
		if (nullptr == pLeftObj->GetCollider())
		{
			continue;
		}

		for (CGameObject* pRightObj : rightListObj)
		{
			if (nullptr == pRightObj->GetCollider())
			{
				continue;
			}

			if (pLeftObj == pRightObj)
			{
				continue;
			}

			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				pLeftCollider->OnCollision(pRightCollider);
				pRightCollider->OnCollision(pLeftCollider);
			}
		}
	}
}

void CCollisionManager::Release()
{

}

void CCollisionManager::CheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = true;
	m_arrLayer[(int)right][(int)left] = true;
}

void CCollisionManager::UnCheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = false;
	m_arrLayer[(int)right][(int)left] = false;
}

void CCollisionManager::ResetLayer()
{
	memset(m_arrLayer, 0, sizeof(bool) * (int)Layer::Size * (int)Layer::Size);
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	const Vector vecLeftPos = pLeftCollider->GetPos();
	const Vector vecRightPos = pRightCollider->GetPos();

	const Vector vecLeftScale = pLeftCollider->GetScale();
	const Vector vecRightScale = pRightCollider->GetScale();

	float absXPos = abs(vecLeftPos.x - vecRightPos.x);
	float absYPos = abs(vecLeftPos.y - vecRightPos.y);

	float disX = (vecLeftScale.x + vecRightScale.x) * 0.5f;
	float disY = (vecLeftScale.y + vecRightScale.y) * 0.5f;

	if (absXPos < disX &&
		absYPos < disY)
	{
		return true;
	}
	return false;
}
