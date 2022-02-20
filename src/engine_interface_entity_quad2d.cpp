#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad2d_create(const string& id, bool isCentered)
{
	_core->getQuad2dEntityManager()->createEntity(id, isCentered);
}

void EngineInterface::quad2d_delete(const string& id)
{
	for(const auto& [animationId, quadId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimationIds())
	{
		if(id == quadId)
		{
			_core->getAnimation2dPlayer()->stopQuad2dAnimation(animationId, quadId);
		}
	}

	_core->getQuad2dEntityManager()->deleteEntity(id);
}

void EngineInterface::quad2d_setVisible(const string& id, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::quad2d_setDiffuseMap(const string& id, const string& value)
{
	if(value.empty())
	{
		_core->getQuad2dEntityManager()->getEntity(id)->setDiffuseMap(nullptr);
		_core->getQuad2dEntityManager()->getEntity(id)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			auto image = _core->getImageLoader()->loadImage(value);

			if(image != nullptr)
			{
				texture = make_shared<TextureBuffer>(image);

				_core->getTextureBufferCache()->store2dBuffer(value, texture);
			}
		}

		_core->getQuad2dEntityManager()->getEntity(id)->setDiffuseMap(texture);
		_core->getQuad2dEntityManager()->getEntity(id)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad2d_setPosition(const string& id, const fvec2& position)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setPosition(position);
}

void EngineInterface::quad2d_setRotation(const string& id, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setRotation(rotation);
}

void EngineInterface::quad2d_setSize(const string& id, const fvec2& size)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setSize(size);
}

void EngineInterface::quad2d_move(const string& id, const fvec2& position)
{
	_core->getQuad2dEntityManager()->getEntity(id)->move(position);
}

void EngineInterface::quad2d_rotate(const string& id, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(id)->rotate(rotation);
}

void EngineInterface::quad2d_scale(const string& id, const fvec2& size)
{
	_core->getQuad2dEntityManager()->getEntity(id)->scale(size);
}

void EngineInterface::quad2d_moveTo(const string& id, const fvec2& target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::quad2d_rotateTo(const string& id, float target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::quad2d_scaleTo(const string& id, const fvec2& target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(id)->scaleTo(target, speed);
}

void EngineInterface::quad2d_setColor(const string& id, const fvec3& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::quad2d_setOpacity(const string& id, float value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setOpacity(value);
}

void EngineInterface::quad2d_setMinPosition(const string& id, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setMinPosition(value);
}

void EngineInterface::quad2d_setMaxPosition(const string& id, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setMaxPosition(value);
}

void EngineInterface::quad2d_setWireframed(const string& id, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::quad2d_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::quad2d_setUvMultiplier(const string& id, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setUvMultiplier(value);
}

void EngineInterface::quad2d_setUvOffset(const string& id, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setUvOffset(value);
}

void EngineInterface::quad2d_startAnimation(const string& quadId, const string& animationId, int playCount)
{
	_core->getAnimation2dPlayer()->startQuad2dAnimation(animationId, quadId, playCount);
}

void EngineInterface::quad2d_pauseAnimation(const string& quadId, const string& animationId)
{
	_core->getAnimation2dPlayer()->pauseQuad2dAnimation(animationId, quadId);
}

void EngineInterface::quad2d_autopauseAnimation(const string& quadId, const string& animationId)
{
	_core->getAnimation2dPlayer()->autopauseQuad2dAnimation(animationId, quadId);
}

void EngineInterface::quad2d_resumeAnimation(const string& quadId, const string& animationId)
{
	_core->getAnimation2dPlayer()->resumeQuad2dAnimation(animationId, quadId);
}

void EngineInterface::quad2d_stopAnimation(const string& quadId, const string& animationId)
{
	_core->getAnimation2dPlayer()->stopQuad2dAnimation(animationId, quadId);
}

void EngineInterface::quad2d_setAnimationRowIndex(const string& animationId, const string& quadId, unsigned int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimationRowIndex(animationId, quadId, value);
}

void EngineInterface::quad2d_setAnimationColumnIndex(const string& animationId, const string& quadId, unsigned int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimationColumnIndex(animationId, quadId, value);
}

void EngineInterface::quad2d_setAnimationIntervalMultiplier(const string& animationId, const string& quadId, unsigned int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimationIntervalMultiplier(animationId, quadId, value);
}

void EngineInterface::quad2d_setAnimationIntervalDivider(const string& animationId, const string& quadId, unsigned int value)
{
	_core->getAnimation2dPlayer()->setQuad2dAnimationIntervalDivider(animationId, quadId, value);
}

void EngineInterface::quad2d_setHorizontallyFlipped(const string& id, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setHorizontallyFlipped(value);
}

void EngineInterface::quad2d_setVerticallyFlipped(const string& id, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(id)->setVerticallyFlipped(value);
}

const bool EngineInterface::quad2d_isExisting(const string& id) const
{
	return _core->getQuad2dEntityManager()->isEntityExisting(id);
}

const fvec2& EngineInterface::quad2d_getPosition(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getPosition();
}

const float EngineInterface::quad2d_getRotation(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getRotation();
}

const float EngineInterface::quad2d_getOpacity(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getOpacity();
}

const int EngineInterface::quad2d_getAnimationPlayCount(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimationPlayCount(quadId, animationId);
}

const unsigned int EngineInterface::quad2d_getAnimationRowIndex(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimationRowIndex(quadId, animationId);
}

const unsigned int EngineInterface::quad2d_getAnimationColumnIndex(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimationColumnIndex(quadId, animationId);
}

const unsigned int EngineInterface::quad2d_getAnimationIntervalMultiplier(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimationIntervalMultiplier(quadId, animationId);
}

const unsigned int EngineInterface::quad2d_getAnimationIntervalDivider(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->getQuad2dAnimationIntervalDivider(quadId, animationId);
}

const vector<string> EngineInterface::quad2d_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad2dEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const vector<string> EngineInterface::quad2d_getAnimationIds(const string& id) const
{
	vector<string> result;

	for(const auto& [animationId, quadId] : _core->getAnimation2dPlayer()->getStartedQuad2dAnimationIds())
	{
		if(id == quadId)
		{
			result.push_back(animationId);
		}
	}

	return result;
}

const string& EngineInterface::quad2d_getDiffuseMapPath(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getDiffuseMapPath();
}

const fvec3& EngineInterface::quad2d_getWireframeColor(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getWireframeColor();
}

const fvec2& EngineInterface::quad2d_getSize(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getSize();
}

const fvec2& EngineInterface::quad2d_getMinPosition(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getMinPosition();
}

const fvec2& EngineInterface::quad2d_getMaxPosition(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getMaxPosition();
}

const fvec2& EngineInterface::quad2d_getUvMultiplier(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getUvMultiplier();
}

const fvec2& EngineInterface::quad2d_getUvOffset(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getUvOffset();
}

const fvec3& EngineInterface::quad2d_getColor(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->getColor();
}

const bool EngineInterface::quad2d_isVisible(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::quad2d_isCentered(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->isCentered();
}

const bool EngineInterface::quad2d_hasDiffuseMap(const string& id) const
{
	return (_core->getQuad2dEntityManager()->getEntity(id)->getDiffuseMap() != nullptr);
}

const bool EngineInterface::quad2d_isWireframed(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->isWireframed();
}

const bool EngineInterface::quad2d_isAnimationStarted(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimationStarted(animationId, quadId);
}

const bool EngineInterface::quad2d_isAnimationPaused(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimationPaused(animationId, quadId);
}

const bool EngineInterface::quad2d_isAnimationAutopaused(const string& quadId, const string& animationId) const
{
	return _core->getAnimation2dPlayer()->isQuad2dAnimationAutopaused(animationId, quadId);
}

const bool EngineInterface::quad2d_isHorizontallyFlipped(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->isFlippedHorizonally();
}

const bool EngineInterface::quad2d_isVerticallyFlipped(const string& id) const
{
	return _core->getQuad2dEntityManager()->getEntity(id)->isVerticallyFlipped();
}