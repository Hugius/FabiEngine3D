#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::BaseEntity(const string& ID)
	:
	_ID(ID)
{
	if (ID.empty())
	{
		Logger::throwError("BaseEntity::BaseEntity");
	}
}

void BaseEntity::setVisible(bool value)
{
	_isVisible = value;
}

const string& BaseEntity::getID()
{
	return _ID;
}

const bool BaseEntity::isVisible()
{
	return _isVisible;
}