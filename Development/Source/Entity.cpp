#include <WE3D/Entity.hpp>
#include <WE3D/Logger.hpp>

Entity::~Entity()
{
	for (auto & buffer : p_oglBuffers)
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
		p_ID = ID;
	}
}

void Entity::addOglBuffer(OpenGLBuffer * buffer)
{
	p_oglBuffers.push_back(buffer);
}

void Entity::setEnabled(bool val)
{
	p_enabled = val;
}

const vector<OpenGLBuffer*> & Entity::getOglBuffers() const
{
	return p_oglBuffers;
}

const OpenGLBuffer * Entity::getOglBuffer(int index) const
{
	return p_oglBuffers[index];
}

const OpenGLBuffer * Entity::getOglBuffer() const
{
	return p_oglBuffers[0];
}

const string & Entity::getID() const
{
	return p_ID;
}

const bool Entity::isEnabled() const
{
	return p_enabled;
}