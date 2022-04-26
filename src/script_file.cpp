#include "script_file.hpp"

ScriptFile::ScriptFile(const string & id)
	:
	_id(id)
{
	if(_id.empty())
	{
		abort();
	}
}

void ScriptFile::createLine(unsigned int index, const string & textContent)
{
	_lines.insert(_lines.begin() + index, textContent);
}

void ScriptFile::editLine(unsigned int index, const string & textContent)
{
	if(index >= _lines.size())
	{
		abort();
	}
	else
	{
		_lines[index] = textContent;
	}
}

void ScriptFile::deleteLine(unsigned int index)
{
	if(index >= _lines.size())
	{
		abort();
	}
	else
	{
		_lines.erase(_lines.begin() + index);
	}
}

void ScriptFile::setLines(const vector<string> & value)
{
	_lines = value;
}

void ScriptFile::setCursorLineIndex(int value)
{
	_cursorLineIndex = max(0, value);
}

void ScriptFile::setCursorCharacterIndex(int value)
{
	_cursorCharacterIndex = max(0, value);
}

const string & ScriptFile::getId() const
{
	return _id;
}

const string & ScriptFile::getLine(unsigned int index) const
{
	if(index >= _lines.size())
	{
		abort();
	}
	else
	{
		return _lines[index];
	}
}

const int ScriptFile::getLineCount() const
{
	return static_cast<int>(_lines.size());
}

const int ScriptFile::getCursorLineIndex() const
{
	return _cursorLineIndex;
}

const int ScriptFile::getCursorCharacterIndex() const
{
	return _cursorCharacterIndex;
}

const vector<string> & ScriptFile::getLines() const
{
	return _lines;
}