#pragma once

#include <string>

using std::string;

class Animation2d final
{
public:
	Animation2d(const string& ID);

	void setPlayCount(int value);
	void setPaused(bool value);
	void setRowIndex(unsigned int value);
	void setColumnIndex(unsigned int value);
	void setRowCount(unsigned int value);
	void setColumnCount(unsigned int value);
	void setFramestep(unsigned int value);
	void setPassedFrames(unsigned int value);
	void setPreviewTexturePath(const string& value);

	const string& getID() const;
	const string& getPreviewTexturePath() const;

	const int getPlayCount() const;

	const unsigned int getPassedFrames() const;
	const unsigned int getFramestep() const;
	const unsigned int getRowCount() const;
	const unsigned int getColumnCount() const;
	const unsigned int getRowIndex() const;
	const unsigned int getColumnIndex() const;

	const bool isPaused() const;

private:
	const string _ID;
	string _previewTexturePath = "";

	int _playCount = 0;

	unsigned int _rowCount = 0;
	unsigned int _rowIndex = 0;
	unsigned int _columnCount = 0;
	unsigned int _columnIndex = 0;
	unsigned int _framestep = 0;
	unsigned int _passedFrames = 0;

	bool _isPaused = false;
};