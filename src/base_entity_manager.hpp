#pragma once

#include <string>

using std::string;

class BaseEntityManager
{
public:
	virtual void deleteEntity(const string& ID) = 0;
	virtual void deleteEntities() = 0;

	virtual const bool isEntityExisting(const string& ID) const = 0;
};