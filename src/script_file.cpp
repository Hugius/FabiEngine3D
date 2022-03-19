#include "script_file.hpp"
#include "logger.hpp"

ScriptFile::ScriptFile(const string& id)
	:
	_id(id)
{

}

void ScriptFile::createLine(unsigned int index, const string& textContent)
{
	_lines.insert(_lines.begin() + index, textContent);
}

void ScriptFile::editLine(unsigned int index, const string& textContent)
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

void ScriptFile::setCursorLineIndex(unsigned int index)
{
	_cursorLineIndex = index;
}

void ScriptFile::setCursorCharacterIndex(unsigned int index)
{
	_cursorCharacterIndex = index;
}

void ScriptFile::changeId(const string& newId)
{
	_id = newId;
}

const string& ScriptFile::getId() const
{
	return _id;
}

const string& ScriptFile::getLine(unsigned int index) const
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

const unsigned int ScriptFile::getLineCount() const
{
	return static_cast<unsigned int>(_lines.size());
}

const unsigned int ScriptFile::getCursorLineIndex() const
{
	return _cursorLineIndex;
}

const unsigned int ScriptFile::getCursorCharacterIndex() const
{
	return _cursorCharacterIndex;
}

const vector<string>& ScriptFile::getLines() const
{
	return _lines;
}