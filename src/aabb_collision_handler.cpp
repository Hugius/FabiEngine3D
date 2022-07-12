#include "aabb_collision_handler.hpp"

void AabbCollisionHandler::calculateCollisionWithAabbs(const string & aabbId)
{

}

void AabbCollisionHandler::clearCollisionWithAabbs()
{
	_aabbCollisions.clear();
}

//const bool AabbCollisionHandler::hasAabbsCollided(shared_ptr<Aabb> firstAabb, shared_ptr<Aabb> secondAabb) const
//{
//	const auto aabbPosition1 = firstAabb->getBasePosition();
//	const auto aabbPosition2 = secondAabb->getBasePosition();
//	const auto aabbSize1 = firstAabb->getBaseSize();
//	const auto aabbSize2 = secondAabb->getBaseSize();
//	const auto halfAabbSize1 = (aabbSize1 * 0.5f);
//	const auto halfAabbSize2 = (aabbSize2 * 0.5f);
//
//	bool xInsideBox = false;
//	bool yInsideBox = false;
//	bool zInsideBox = false;
//	bool xTooSmall = false;
//	bool yTooSmall = false;
//	bool zTooSmall = false;
//
//	if((((aabbPosition1.x + halfAabbSize1.x) > (aabbPosition2.x - halfAabbSize2.x)) && ((aabbPosition1.x + halfAabbSize1.x) < (aabbPosition2.x + halfAabbSize2.x))) ||
//	   (((aabbPosition1.x - halfAabbSize1.x) < (aabbPosition2.x + halfAabbSize2.x)) && ((aabbPosition1.x - halfAabbSize1.x) > (aabbPosition2.x - halfAabbSize2.x))))
//	{
//		xInsideBox = true;
//	}
//
//	if(firstAabb->isCentered())
//	{
//		if(secondAabb->isCentered())
//		{
//			if((((aabbPosition1.y + halfAabbSize1.y) > (aabbPosition2.y - halfAabbSize2.y)) && ((aabbPosition1.y + halfAabbSize1.y) < (aabbPosition2.y + halfAabbSize2.y))) ||
//			   (((aabbPosition1.y - halfAabbSize1.y) < (aabbPosition2.y + halfAabbSize2.y)) && ((aabbPosition1.y - halfAabbSize1.y) > (aabbPosition2.y - halfAabbSize2.y))))
//			{
//				yInsideBox = true;
//			}
//		}
//		else
//		{
//			if((((aabbPosition1.y + halfAabbSize1.y) > aabbPosition2.y) && ((aabbPosition1.y + halfAabbSize1.y) < (aabbPosition2.y + aabbSize2.y))) ||
//			   (((aabbPosition1.y - halfAabbSize1.y) < (aabbPosition2.y + aabbSize2.y)) && ((aabbPosition1.y - halfAabbSize1.y) > aabbPosition2.y)))
//			{
//				yInsideBox = true;
//			}
//		}
//	}
//	else
//	{
//		if(secondAabb->isCentered())
//		{
//			if((((aabbPosition1.y + aabbSize1.y) > (aabbPosition2.y - halfAabbSize2.y)) && ((aabbPosition1.y + aabbSize1.y) < (aabbPosition2.y + halfAabbSize2.y))) ||
//			   ((aabbPosition1.y < (aabbPosition2.y + halfAabbSize2.y)) && (aabbPosition1.y > (aabbPosition2.y - halfAabbSize2.y))))
//			{
//				yInsideBox = true;
//			}
//		}
//		else
//		{
//			if((((aabbPosition1.y + halfAabbSize1.y) > (aabbPosition2.y - halfAabbSize2.y)) && ((aabbPosition1.y + halfAabbSize1.y) < (aabbPosition2.y + halfAabbSize2.y))) ||
//			   (((aabbPosition1.y - halfAabbSize1.y) < (aabbPosition2.y + halfAabbSize2.y)) && ((aabbPosition1.y - halfAabbSize1.y) > (aabbPosition2.y - halfAabbSize2.y))))
//			{
//				yInsideBox = true;
//			}
//		}
//	}
//
//	if(((aabbPosition1.z + halfAabbSize1.z) > (aabbPosition2.z - halfAabbSize2.z) && (aabbPosition1.z + halfAabbSize1.z) < (aabbPosition2.z + halfAabbSize2.z)) ||
//	   ((aabbPosition1.z - halfAabbSize1.z) < (aabbPosition2.z + halfAabbSize2.z) && (aabbPosition1.z - halfAabbSize1.z) > (aabbPosition2.z - halfAabbSize2.z)))
//	{
//		zInsideBox = true;
//	}
//
//	xTooSmall =
//		(((aabbPosition1.x + halfAabbSize1.x) >= (aabbPosition2.x + halfAabbSize2.x)) &&
//		 ((aabbPosition1.x - halfAabbSize1.x) <= (aabbPosition2.x - halfAabbSize2.x)));
//
//	if(firstAabb->isCentered())
//	{
//		if(secondAabb->isCentered())
//		{
//			yTooSmall =
//				(((aabbPosition1.y + halfAabbSize1.y) >= (aabbPosition2.y + halfAabbSize2.y)) &&
//				 ((aabbPosition1.y - halfAabbSize1.y) <= (aabbPosition2.y - halfAabbSize2.y)));
//		}
//		else
//		{
//			yTooSmall =
//				(((aabbPosition1.y + halfAabbSize1.y) >= (aabbPosition2.y + aabbSize2.y)) &&
//				 ((aabbPosition1.y - halfAabbSize1.y) <= aabbPosition2.y));
//		}
//	}
//	else
//	{
//		if(secondAabb->isCentered())
//		{
//			yTooSmall =
//				(((aabbPosition1.y + aabbSize1.y) >= (aabbPosition2.y + halfAabbSize2.y)) &&
//				 (aabbPosition1.y <= (aabbPosition2.y - halfAabbSize2.y)));
//		}
//		else
//		{
//			yTooSmall =
//				(((aabbPosition1.y + aabbSize1.y) >= (aabbPosition2.y + aabbSize2.y)) &&
//				 (aabbPosition1.y <= aabbPosition2.y));
//		}
//	}
//
//	zTooSmall =
//		(((aabbPosition1.z + halfAabbSize1.z) >= (aabbPosition2.z + halfAabbSize2.z)) &&
//		 ((aabbPosition1.z - halfAabbSize1.z) <= (aabbPosition2.z - halfAabbSize2.z)));
//
//	if((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void AabbCollisionHandler::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

const vector<string> AabbCollisionHandler::getAabbCollisions(const string & aabbId) const
{
	return _aabbCollisions.at(aabbId);
}