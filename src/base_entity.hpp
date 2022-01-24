#pragma once

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& id);

	virtual void setVisible(bool value);

	const string& getId() const;

	const bool isVisible() const;

protected:
	const string _ID;

	bool _isVisible = true;

private:
	virtual void _dummy()
	{

	}
};