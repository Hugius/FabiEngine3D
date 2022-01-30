#include "script_file.hpp"
#include "logger.hpp"

ScriptFile::ScriptFile(const string& id)
	:
	_id(id)
{

}

void ScriptFile::addNewLine(const string& textContent)
{
	_lines.push_back(textContent);
}

void ScriptFile::insertNewLine(unsigned int index, const string& textContent)
{
	_lines.insert(_lines.begin() + index, textContent);
}

void ScriptFile::setLineText(unsigned int index, const string& textContent)
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

void ScriptFile::setCursorCharIndex(unsigned int index)
{
	_cursorCharIndex = index;
}

void ScriptFile::changeId(const string& newId)
{
	_id = newId;
}

const string& ScriptFile::getId() const
{
	return _id;
}

const string& ScriptFile::getLineText(unsigned int index) const
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

const unsigned int ScriptFile::getCursorCharIndex() const
{
	return _cursorCharIndex;
}

const vector<string>& ScriptFile::getLines() const
{
	return _lines;
}