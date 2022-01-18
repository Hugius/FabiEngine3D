#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);

	virtual void setVisible(bool value);

	const string& getID() const;

	const bool isVisible() const;

protected:
	const string _ID;

	bool _isVisible = true;

private:
	virtual void _dummy()
	{

	}
};