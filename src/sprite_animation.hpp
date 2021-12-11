#pragma once

#include <string>

using std::string;

class SpriteAnimation final
{
public:
	SpriteAnimation(const string& ID);

	// VOIDS
	void start(int loops);
	void pause();
	void resume();
	void stop();
	void setRowIndex(unsigned int value);
	void setColumnIndex(unsigned int value);
	void setRowCount(unsigned int value);
	void setColumnCount(unsigned int value);
	void setFramestep(unsigned int value);
	void setPassedFrames(unsigned int value);
	void setLoops(unsigned int value);

	// STRING
	const string& getID() const;

	// INT
	const int getMaxLoops() const;

	// UNSIGNED INT
	const unsigned int getPassedFrames() const;
	const unsigned int getFramestep() const;
	const unsigned int getRowCount() const;
	const unsigned int getColumnCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;
	const unsigned int getLoops() const;

	// BOOL
	const bool isStarted() const;
	const bool isPaused() const;

private:
	// STRING
	const string _ID;

	// INT
	int _maxLoops = 0;

	// UNSIGNED INT
	unsigned int _framestep = 0;
	unsigned int _passedFrames = 0;
	unsigned int _rowCount = 0;
	unsigned int _columnCount = 0;
	unsigned int _rowIndex = 0;
	unsigned int _columnIndex = 0;
	unsigned int _passedLoops = 0;

	// BOOL
	bool _isStarted = false;
	bool _isPaused = false;
};