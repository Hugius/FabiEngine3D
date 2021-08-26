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

const string& BaseEntity::getID()
{
	return _ID;
}