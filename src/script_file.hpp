#pragma once

#include "fe3d.hpp"

class ScriptFile final
{
public:
	ScriptFile(FabiEngine3D& fe3d, const string& ID);

	// VOID
	void addNewLine(const string& textContent);
	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void removeLine(unsigned int index);
	void removeLastLine();
	void setCursorLineIndex(unsigned int index);
	void setCursorCharIndex(unsigned int index);
	void changeID(const string& newID);

	// STRING
	const vector<string>& getLines() const;
	const string& getID() const;
	const string& getLineText(unsigned int index) const;

	// UNSIGNED INT
	const unsigned int getLineCount() const;
	const unsigned int getCursorLineIndex() const;
	const unsigned int getCursorCharIndex() const;

private:
	// STRING
	vector<string> _lines;
	string _ID;

	// UNSIGNED INT
	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharIndex = 0;

	// Miscellaneous
	FabiEngine3D& _fe3d;
};