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
	CheckLayer(Layer::Character, Layer::Monster);
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

			list<CCollider*>* pLeftCollider  = pLeftObj->GetCollider();
			list<CCollider*>* pRightCollider = pRightObj->GetCollider();
			
			bool reserveDelete = pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete();

			IsCollisionList(pLeftCollider, pRightCollider, reserveDelete);
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


bool CCollisionManager::IsCollisionList(list<CCollider*>* pListLeftCollider, list<CCollider*>* pListRightCollider, bool reserveDelete)
{
	for (CCollider* pLeftCollider : *pListLeftCollider)
	{
		for (CCollider* pRightCollider : *pListRightCollider)
		{

			UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());
			if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
			{
				m_umapPrevCollision.insert(make_pair(id, false));
			}
			bool prevCollision = m_umapPrevCollision[id];
			bool curCollision = IsCollision(pLeftCollider, pRightCollider);

			if (curCollision)
			{
				if (prevCollision)
				{

					if (reserveDelete)
					{
						pLeftCollider->OnCollisionExit(pRightCollider);
						pRightCollider->OnCollisionExit(pLeftCollider);
						m_umapPrevCollision[id] = false;
					}
					else
					{
						pLeftCollider->OnCollisionStay(pRightCollider);
						pRightCollider->OnCollisionStay(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}	
				}
				else
				{
					if (reserveDelete)
					{
						return false;
					}
					pLeftCollider->OnCollisionEnter(pRightCollider);
					pRightCollider->OnCollisionEnter(pLeftCollider);
					m_umapPrevCollision[id] = true;
				}
				return true;
			}
			else
			{
				if (prevCollision)
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);
					m_umapPrevCollision[id] = false;
				}
			}
		}
	}
	return false;
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	const Vector vecLeftPos		= pLeftCollider->GetPos();
	const Vector vecRightPos	= pRightCollider->GetPos();

	const Vector vecLeftScale	= pLeftCollider->GetScale();
	const Vector vecRightScale	= pRightCollider->GetScale();

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

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;

	if (leftID > rightID)
	{
		result |= ((UINT64)leftID) << 32;
		result |= (UINT64)rightID;
	}
	else
	{
		result |= ((UINT64)rightID) << 32;
		result |= (UINT64)leftID;
	}

	return result;
}
