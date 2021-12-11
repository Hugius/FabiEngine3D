#pragma once

#include <string>

using std::string;

class SpriteAnimation final
{
public:
	SpriteAnimation(const string& ID);

	// VOIDS
	void setTimesToPlay(int value);
	void setPaused(bool value);
	void setRowIndex(unsigned int value);
	void setColumnIndex(unsigned int value);
	void setRowCount(unsigned int value);
	void setColumnCount(unsigned int value);
	void setFramestep(unsigned int value);
	void setPassedFrames(unsigned int value);
	void setPreviewTexturePath(const string& value);

	// STRING
	const string& getID() const;
	const string& getPreviewTexturePath() const;

	// INT
	const int getTimesToPlay() const;

	// UNSIGNED INT
	const unsigned int getPassedFrames() const;
	const unsigned int getFramestep() const;
	const unsigned int getRowCount() const;
	const unsigned int getColumnCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;

	// BOOL
	const bool isPaused() const;

private:
	// STRING
	const string _ID;
	string _previewTexturePath = "";

	// INT
	int _timesToPlay = 0;

	// UNSIGNED INT
	unsigned int _rowCount = 0;
	unsigned int _rowIndex = 0;
	unsigned int _columnCount = 0;
	unsigned int _columnIndex = 0;
	unsigned int _framestep = 0;
	unsigned int _passedFrames = 0;

	// BOOL
	bool _isPaused = false;
};