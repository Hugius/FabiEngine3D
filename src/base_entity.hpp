#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);

	// VOID
	void setVisible(bool value);

	// STRING
	const string& getID() const;

	// BOOL
	const bool isVisible() const;

private:
	// VOID
	virtual void _dummy() {}

	// STRING
	const string _ID;

	// BOOL
	bool _isVisible = true;
};