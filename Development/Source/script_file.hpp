#pragma once

#include "fe3d.hpp"

class ScriptFile final
{
public:
	ScriptFile(FabiEngine3D& fe3d, const string& ID);

	// Voids
	void addNewLine(const string& textContent);
	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void removeLine(unsigned int index);
	void removeLastLine();
	void setCursorLineIndex(unsigned int index);
	void setCursorCharIndex(unsigned int index);
	void changeID(const string& newID);

	// Strings
	const vector<string>& getLines();
	const string& getID();
	const string& getLineText(unsigned int index);

	// Integers
	unsigned int getLineCount();
	unsigned int getCursorLineIndex();
	unsigned int getCursorCharIndex();

private:
	// Strings
	vector<string> _lines;
	string _ID;

	// Integers
	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharIndex = 0;

	// Miscellaneous
	FabiEngine3D& _fe3d;
};