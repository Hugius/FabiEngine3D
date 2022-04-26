#pragma once

#include "engine_interface.hpp"

class ScriptFile final
{
public:
	ScriptFile(const string & id);

	void createLine(unsigned int index, const string & textContent);
	void editLine(unsigned int index, const string & textContent);
	void deleteLine(unsigned int index);
	void setLines(const vector<string> & value);
	void setCursorLineIndex(int value);
	void setCursorCharacterIndex(int value);

	const vector<string> & getLines() const;

	const string & getId() const;
	const string & getLine(unsigned int index) const;

	const unsigned int getLineCount() const;
	const unsigned int getCursorLineIndex() const;
	const unsigned int getCursorCharacterIndex() const;

private:
	const string _id;

	vector<string> _lines = {};

	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorCharacterIndex = 0;
};