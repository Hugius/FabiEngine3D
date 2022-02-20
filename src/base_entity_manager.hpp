#pragma once

#include <string>

using std::string;

class BaseEntityManager
{
public:
	virtual void deleteEntity(const string& id) = 0;
	virtual void deleteEntities() = 0;

	virtual const bool isEntityExisting(const string& id) const = 0;
	virtual const bool isEntitiesExisting() const = 0;
};