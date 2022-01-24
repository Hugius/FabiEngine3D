#pragma once

#include "engine_interface.hpp"

class ScriptFile final
{
public:
	ScriptFile(const string& id);

	void addNewLine(const string& textContent);
	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void deleteLine(unsigned int index);
	void setCursorLineIndex(unsigned int index);
	void setCursorCharIndex(unsigned int index);
	void changeId(const string& newId);

	const vector<string>& getLines() const;

	const string& getId() const;
	const string& getLineText(unsigned int index) const;

	const unsigned int getLineCount() const;
	const unsigned int getCursorLineIndex() const;
	const unsigned int getCursorCharIndex() const;

private:
	vector<string> _lines;

	string _id;

	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharIndex = 0;
};