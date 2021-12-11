#include "sprite_animation.hpp"

SpriteAnimation::SpriteAnimation(const string& ID)
	:
	_ID(ID)
{

}

const string& SpriteAnimation::getID() const
{
	return _ID;
}

//void BillboardEntity::startSpriteAnimation(int loops)
//{
//	if(_isSpriteAnimationStarted)
//	{
//		Logger::throwError("BillboardEntity::startSpriteAnimation::1");
//	}
//	if(loops < -1)
//	{
//		Logger::throwError("BillboardEntity::startSpriteAnimation::2");
//	}
//
//	_isSpriteAnimationStarted = true;
//	_passedSpriteAnimationFrames = 0;
//	_spriteAnimationLoops = 0;
//	_maxSpriteAnimationLoops = loops;
//}
//
//void BillboardEntity::pauseSpriteAnimation()
//{
//	if(!_isSpriteAnimationStarted)
//	{
//		Logger::throwError("BillboardEntity::pauseSpriteAnimation::1");
//	}
//	else if(_isSpriteAnimationPaused)
//	{
//		Logger::throwError("BillboardEntity::pauseSpriteAnimation::2");
//	}
//
//	_isSpriteAnimationPaused = true;
//}
//
//void BillboardEntity::resumeSpriteAnimation()
//{
//	if(!_isSpriteAnimationPaused)
//	{
//		Logger::throwError("BillboardEntity::resumeSpriteAnimation");
//	}
//
//	_isSpriteAnimationPaused = false;
//}
//
//void BillboardEntity::stopSpriteAnimation()
//{
//	if(!_isSpriteAnimationStarted)
//	{
//		Logger::throwError("BillboardEntity::stopSpriteAnimation");
//	}
//
//	_isSpriteAnimationStarted = false;
//	_spriteAnimationRowIndex = 0;
//	_spriteAnimationColumnIndex = 0;
//}
//
//void BillboardEntity::setSpriteAnimationRowIndex(unsigned int value)
//{
//	_spriteAnimationRowIndex = value;
//}
//
//void BillboardEntity::setSpriteAnimationColumnIndex(unsigned int value)
//{
//	_spriteAnimationColumnIndex = value;
//}
//
//void BillboardEntity::setTotalSpriteAnimationRowCount(unsigned int value)
//{
//	_totalSpriteAnimationRowCount = value;
//}
//
//void BillboardEntity::setTotalSpriteAnimationColumnCount(unsigned int value)
//{
//	_totalSpriteAnimationColumnCount = value;
//}
//
//void BillboardEntity::setSpriteAnimationFramestep(unsigned int value)
//{
//	_spriteAnimationFramestep = value;
//}
//
//void BillboardEntity::increasePassedSpriteAnimationFrames()
//{
//	_passedSpriteAnimationFrames++;
//}
//
//void BillboardEntity::resetPassedSpriteAnimationFrames()
//{
//	_passedSpriteAnimationFrames = 0;
//}
//
//void BillboardEntity::increaseSpriteAnimationLoops()
//{
//	_spriteAnimationLoops++;
//}

//const int FabiEngine3D::billboard_getRemainingSpriteAnimationLoops(const string& ID) const
//{
//	// Temporary values
//	auto maxLoops = _core->_billboardEntityManager.getEntity(ID)->getMaxSpriteAnimationLoops();
//	auto currentLoops = _core->_billboardEntityManager.getEntity(ID)->getSpriteAnimationLoops();
//
//	if(maxLoops == -1) // Infinite
//	{
//		return -1;
//	}
//	else // Finite
//	{
//		return (maxLoops - currentLoops);
//	}
//}