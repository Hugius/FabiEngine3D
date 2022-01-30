#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::BaseEntity(const string& id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void BaseEntity::setVisible(bool value)
{
	_isVisible = value;
}

const string& BaseEntity::getId() const
{
	return _id;
}

const bool BaseEntity::isVisible() const
{
	return _isVisible;
}