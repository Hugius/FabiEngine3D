#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::BaseEntity(const string& ID) :
	_ID(ID)
{
	if (ID.empty())
	{
		Logger::throwError("Tried to create a BaseEntity with an empty ID!");
	}
}

BaseEntity::~BaseEntity()
{
	clearRenderBuffers();
}

void BaseEntity::addRenderBuffer(RenderBuffer * buffer, bool deleteOnDestroy)
{
	_renderBuffers.push_back(buffer);
	_renderBufferMemoryManagement.push_back(deleteOnDestroy);
}

void BaseEntity::clearRenderBuffers()
{
	for (size_t i = 0; i < _renderBuffers.size(); i++)
	{
		if (_renderBufferMemoryManagement[i])
		{
			if (_renderBuffers[i] != nullptr)
			{
				delete _renderBuffers[i];
			}
		}
	}

	_renderBuffers.clear();
}

void BaseEntity::setVisible(bool value)
{
	_visible = value;
}

const vector<RenderBuffer*>& BaseEntity::getRenderBuffers() const
{
	return _renderBuffers;
}

const RenderBuffer * BaseEntity::getRenderBuffer(unsigned int index) const
{
	return _renderBuffers[index];
}

const RenderBuffer * BaseEntity::getRenderBuffer() const
{
	return _renderBuffers[0];
}

const string& BaseEntity::getID() const
{
	return _ID;
}

const bool BaseEntity::isVisible() const
{
	return _visible;
}