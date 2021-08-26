#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);

	// Strings
	const string& getID();

private:
	// Voids
	virtual void _dummy() {}

	// Strings
	const string _ID;
};