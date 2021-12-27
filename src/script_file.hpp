#pragma once

#include "fe3d.hpp"

class ScriptFile final
{
public:
	ScriptFile(FabiEngine3D& fe3d, const string& ID);

	void addNewLine(const string& textContent);
	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void deleteLine(unsigned int index);
	void setCursorLineIndex(unsigned int index);
	void setCursorCharIndex(unsigned int index);
	void changeID(const string& newID);

	const vector<string>& getLines() const;
	const string& getID() const;
	const string& getLineText(unsigned int index) const;

	const unsigned int getLineCount() const;
	const unsigned int getCursorLineIndex() const;
	const unsigned int getCursorCharIndex() const;

private:
	vector<string> _lines;
	string _ID;

	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharIndex = 0;

	FabiEngine3D& _fe3d;
};