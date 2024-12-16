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
{}

void CCollisionManager::Init()
{
	CheckLayer(Layer::Character, Layer::Monster);
}

void CCollisionManager::Release()	{	}

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

			CCollider* pLeftCollider  = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			
			bool reserveDelete = pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete();

			IsCollisionTrigger(pLeftCollider, pRightCollider, reserveDelete);
		}
	}
}




bool CCollisionManager::IsCollisionTrigger(CCollider* const pLeftCollider,CCollider* const pRightCollider, const bool reserveDelete)
{
	UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());
	if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
	{
		m_umapPrevCollision.insert(make_pair(id, false));
	}
	bool prevCollision = m_umapPrevCollision[id];
	bool curCollision = IsCollisionCheck(pLeftCollider, pRightCollider);

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
	return false;
}

bool CCollisionManager::IsCollisionCheck(CCollider* const pLeftCollider, CCollider* const pRightCollider)
{
	const RectSize sizeLeft		= pLeftCollider->GetBaseSize();
	const RectSize sizeRight	= pRightCollider->GetBaseSize();

	if ((sizeLeft.left > sizeRight.right && sizeLeft.left > sizeRight.left) ||
		(sizeLeft.right < sizeRight.left && sizeLeft.right < sizeRight.right))
	{
		return false;
	}
	if ((sizeLeft.top > sizeRight.top && sizeLeft.top > sizeRight.bottom) ||
		(sizeLeft.bottom < sizeRight.top && sizeLeft.bottom < sizeRight.bottom))
	{
		return false;
	}

	Vector vecLeftPos	= pLeftCollider->GetPos();
	Vector vecRightPos	= pRightCollider->GetPos();

	for (const pair<SHORT, ColliderMatrix>& leftSize : pLeftCollider->m_mapColliderTransform)
	{
		for (const pair<SHORT, ColliderMatrix>& rightSize : pRightCollider->m_mapColliderTransform)
		{

			ColliderType leftType	= leftSize.second.type;
			ColliderType rightType	= leftSize.second.type;

			Vector leftPos	= vecLeftPos	+ leftSize.second.offset;
			Vector rightPos = vecRightPos	+ rightSize.second.offset;

			if (leftType	== ColliderType::Rect && 
				rightType	== ColliderType::Rect)
			{
				if (RectCollision(leftSize.second, rightSize.second, leftPos, rightPos))
				{
					return true;
				}
			}
			if (leftType	== ColliderType::Circle && 
				rightType	== ColliderType::Circle)
			{
				if (CircleCollision(leftSize.second.scale.x, rightSize.second.scale.x, leftPos, rightPos))
				{
					return true;
				}
			}
			else
			{
				if (leftType == ColliderType::Rect)
				{
					if (RectCircleCollision(leftSize.second, rightSize.second.scale.x, leftPos, rightPos))
					{
						return true;
					}
				}
				else
				{
					if (RectCircleCollision(rightSize.second, leftSize.second.scale.x, rightPos, leftPos))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CCollisionManager::RectCollision(const ColliderMatrix& matLeft, const ColliderMatrix& matRight, const Vector&  vecLeftPos, const Vector&  vecRightPos)
{
	const Vector vecLeftScale	= matRight.scale;
	const Vector vecRightScale	= matLeft.scale;

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

bool CCollisionManager::CircleCollision(float leftRadius, float rightRadius, const Vector&  vecLeftPos, const Vector&  vecRightPos)
{
	float xDistance		= vecLeftPos.x	- vecRightPos.x;
	float yDistance		= vecRightPos.y - vecRightPos.y;
	float scaleDistance = (leftRadius + rightRadius) * 0.5f;

	xDistance		*= xDistance;
	yDistance		*= yDistance;
	scaleDistance	*= scaleDistance;
	
	return scaleDistance >= xDistance + yDistance;
}

bool CCollisionManager::RectCircleCollision(const ColliderMatrix& matRect, float circleRadius, const Vector&  vecRectPos, const Vector&  vecCirclePos)
{
	int totalPoint, xPoint, yPoint = 0;

	Vector rectScale = matRect.scale.x * 0.5f;
	float circleScale = vecCirclePos.x * 0.5f;

	if (circleScale < vecRectPos.x - (rectScale.x))
	{
		xPoint = -1;
	}
	else 
	if (circleScale > vecRectPos.x + (rectScale.x))
	{
		xPoint = 1;
	}
	else
	{
		xPoint = 0;
	}

	if (circleScale < vecRectPos.y - (rectScale.y))
	{
		yPoint = -1;
	}
	else
	if (circleScale > vecRectPos.y + (rectScale.y))
	{
		yPoint = 1;
	}
	else
	{
		yPoint = 0;
	}

	totalPoint = 3 * yPoint + xPoint;
	if (totalPoint < 0)
	{		totalPoint * -1;	}
	
	switch (totalPoint)
	{
	case 0:
		return true;

	case  1:
		return (rectScale.x) + (circleRadius) > abs(vecRectPos.x - vecCirclePos.x);

	case  3:
		return (rectScale.y) + (circleRadius) > abs(vecRectPos.y - vecCirclePos.y);

	case  2:
	case  4:
	{
		float cornerX = (xPoint < 0) ? vecRectPos.x - (rectScale.x) : vecRectPos.x + (rectScale.x);
		float cornerY = (yPoint < 0) ? vecRectPos.y - (rectScale.y) : vecRectPos.y + (rectScale.y);
		if (pow(cornerX - circleRadius, 2) + pow(cornerY - circleRadius, 2) < pow(circleRadius, 2))
		{
			return true;
		}
	}
		break;

	default:
		break;
	}
	return false;
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
