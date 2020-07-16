#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::~BaseEntity()
{
	for (auto & buffer : _oglBuffers)
	{
		if (buffer != nullptr)
		{
			delete buffer;
		}
	}
}

void BaseEntity::load(const string & ID)
{
	if (ID == "")
	{
		Logger::getInst().throwError("Tried to create an Entity with empty ID!");
	}
	else
	{
		_ID = ID;
	}
}

void BaseEntity::addOglBuffer(OpenGLBuffer * buffer)
{
	_oglBuffers.push_back(buffer);
}

void BaseEntity::setEnabled(bool val)
{
	_enabled = val;
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

const string & BaseEntity::getID() const
{
	return _ID;
}

const bool BaseEntity::isEnabled() const
{
	return _enabled;
}