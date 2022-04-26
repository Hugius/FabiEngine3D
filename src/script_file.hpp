#pragma once

#include "engine_interface.hpp"

class ScriptFile final
{
public:
	ScriptFile(const string & id);

	void createLine(int index, const string & textContent);
	void editLine(int index, const string & textContent);
	void deleteLine(int index);
	void setLines(const vector<string> & value);
	void setCursorLineIndex(int value);
	void setCursorCharacterIndex(int value);

	const vector<string> & getLines() const;

	const string & getId() const;
	const string & getLine(int index) const;

	const int getLineCount() const;
	const int getCursorLineIndex() const;
	const int getCursorCharacterIndex() const;

private:
	const string _id;

	vector<string> _lines = {};

	int _cursorLineIndex = 0;
	int _cursorCharacterIndex = 0;
};