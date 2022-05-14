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

	const int getUpdateCount() const;
	const int getRowIndex() const;
	const int getColumnIndex() const;
	const int getIntervalMultiplier() const;
	const int getIntervalDivider() const;

	const int getPlayCount() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

private:
	int _rowIndex = 0;
	int _columnIndex = 0;
	int _updateCount = 0;
	int _intervalMultiplier = 1;
	int _intervalDivider = 1;
	int _playCount = 0;

	bool _isPaused = false;
	bool _isAutopaused = false;
};