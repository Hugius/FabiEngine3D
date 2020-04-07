#include "Entity.hpp"
#include "Logger.hpp"

Entity::~Entity()
{
	for (auto & buffer : _oglBuffers)
	{
		if (buffer != nullptr)
		{
			delete buffer;
		}
	}
}

void Entity::load(const string & ID)
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

void Entity::addOglBuffer(OpenGLBuffer * buffer)
{
	_oglBuffers.push_back(buffer);
}

void Entity::setEnabled(bool val)
{
	_enabled = val;
}

const vector<OpenGLBuffer*> & Entity::getOglBuffers() const
{
	return _oglBuffers;
}

const OpenGLBuffer * Entity::getOglBuffer(int index) const
{
	return _oglBuffers[index];
}

const OpenGLBuffer * Entity::getOglBuffer() const
{
	return _oglBuffers[0];
}

const string & Entity::getID() const
{
	return _ID;
}

const bool Entity::isEnabled() const
{
	return _enabled;
}