#pragma once

#include "fabi_engine_3d.hpp"

class ScriptFile
{
public:
	ScriptFile(FabiEngine3D& fe3d, const string& ID);

	void addNewLine(const string& textContent);
	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void removeLine(unsigned int index);
	void removeLastLine();
	void setCursorLineIndex(unsigned int index);
	void setCursorCharIndex(unsigned int index);

	const string& getID();
	const string& getLineText(unsigned int index);
	unsigned int getLineCount();
	unsigned int getCursorLineIndex();
	unsigned int getCursorCharIndex();
	const vector<string>& getLines();

private:
	FabiEngine3D& _fe3d;
	const string _ID;

	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharIndex = 0;

	vector<string> _lines;
};