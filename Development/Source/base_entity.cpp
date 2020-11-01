#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::~BaseEntity()
{
	clearOglBuffers();
}

void BaseEntity::load(const string& ID)
{
	if (ID == "")
	{
		Logger::throwError("Tried to create an Entity with empty ID!");
	}
	else
	{
		_ID = ID;
	}
}

void BaseEntity::addOglBuffer(OpenGLBuffer * buffer, bool deleteOnDestroy)
{
	_oglBuffers.push_back(buffer);
	_oglBufferMemoryManagement.push_back(deleteOnDestroy);
}

void BaseEntity::clearOglBuffers()
{
	for (unsigned int i = 0; i < _oglBuffers.size(); i++)
	{
		if (_oglBufferMemoryManagement[i])
		{
			if (_oglBuffers[i] != nullptr)
			{
				delete _oglBuffers[i];
			}
		}
	}

	_oglBuffers.clear();
}

void BaseEntity::setVisible(bool val)
{
	_visible = val;
}

const vector<OpenGLBuffer*> & BaseEntity::getOglBuffers() const
{
	return _oglBuffers;
}

const OpenGLBuffer * BaseEntity::getOglBuffer(int index) const
{
	return _oglBuffers[index];
}

const OpenGLBuffer * BaseEntity::getOglBuffer() const
{
	return _oglBuffers[0];
}

const string& BaseEntity::getID() const
{
	return _ID;
}

const bool BaseEntity::isVisible() const
{
	return _visible;
}