#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::BaseEntity(const string& ID)
	:
	_ID(ID)
{
	if (ID.empty())
	{
		Logger::throwFatalError("BaseEntity::BaseEntity");
	}
}

void BaseEntity::setVisible(bool value)
{
	_visible = value;
}

const string& BaseEntity::getID() const
{
	return _ID;
}

const bool BaseEntity::isVisible() const
{
	return _visible;
}