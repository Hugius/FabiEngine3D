#pragma once

#include <string>

using std::string;

class StartedAnimation2d final
{
public:
	void setPlayCount(int value);
	void setPaused(bool value);
	void setAutopaused(bool value);
	void setRowIndex(int value);
	void setColumnIndex(int value);
	void setUpdateCount(int value);
	void setIntervalMultiplier(int value);
	void setIntervalDivider(int value);

	const unsigned int getUpdateCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;
	const unsigned int getIntervalMultiplier() const;
	const unsigned int getIntervalDivider() const;

	const int getPlayCount() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

private:
	unsigned int _rowIndex = 0;
	unsigned int _columnIndex = 0;
	unsigned int _updateCount = 0;
	unsigned int _intervalMultiplier = 1;
	unsigned int _intervalDivider = 1;

	int _playCount = 0;

	bool _isPaused = false;
	bool _isAutopaused = false;
};