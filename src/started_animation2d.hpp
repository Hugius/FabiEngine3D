#pragma once

#include <string>

using std::string;

class StartedAnimation2d final
{
public:
	StartedAnimation2d(const string& animationId, const string& quadId);

	void setPlayCount(int value);
	void setPaused(bool value);
	void setAutopaused(bool value);
	void setRowIndex(unsigned int value);
	void setColumnIndex(unsigned int value);
	void setUpdateCount(unsigned int value);
	void setIntervalMultiplier(unsigned int value);
	void setIntervalDivider(unsigned int value);

	const string& getAnimationId() const;
	const string& getQuadId() const;

	const int getPlayCount() const;

	const unsigned int getUpdateCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;
	const unsigned int getIntervalMultiplier() const;
	const unsigned int getIntervalDivider() const;

	const bool isPaused() const;
	const bool isAutopaused() const;

private:
	const string _animationId;
	const string _quadId;

	int _playCount = 0;

	unsigned int _rowIndex = 0;
	unsigned int _columnIndex = 0;
	unsigned int _updateCount = 0;
	unsigned int _intervalMultiplier = 1;
	unsigned int _intervalDivider = 1;

	bool _isPaused = false;
	bool _isAutopaused = false;
};