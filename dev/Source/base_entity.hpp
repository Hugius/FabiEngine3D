#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);

	// Voids
	void setVisible(bool value);

	// Strings
	const string& getID() const;

	// Booleans
	const bool isVisible() const;

private:
	// Voids
	virtual void _dummy() {}

	// Strings
	const string _ID;

	// Booleans
	bool _isVisible = true;
};