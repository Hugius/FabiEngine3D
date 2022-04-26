#pragma once

#include <string>

using std::string;

class Animation2d final
{
public:
	Animation2d(const string & id);

	void setRowCount(int value);
	void setColumnCount(int value);
	void setInterval(int value);

	const string & getId() const;

	const int getRowCount() const;
	const int getColumnCount() const;
	const int getInterval() const;

private:
	const string _id;

	int _rowCount = 1;
	int _columnCount = 1;
	int _interval = 0;
};