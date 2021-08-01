#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);

	void setVisible(bool value);

	const string& getID() const;

	const bool isVisible() const;

	virtual void dummy() {}

private:
	const string _ID;

	bool _visible = true;
};