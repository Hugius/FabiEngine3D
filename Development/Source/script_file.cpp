#include "script_file.hpp"
#include "logger.hpp"

ScriptFile::ScriptFile(FabiEngine3D& fe3d, const string& ID) :
	_fe3d(fe3d),
	_ID(ID)
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
	if (index >= _lines.size())
	{
		Logger::throwError("Cannot set scriptline text content at file \"" + _ID + "\" with index: " + to_string(index));
	}
	else
	{
		_lines[index] = textContent;
	}
}

void ScriptFile::removeLine(unsigned int index)
{
	if (index >= _lines.size())
	{
		Logger::throwError("Cannot delete scriptline at file \"" + _ID + "\" with index: " + to_string(index));
	}
	else
	{
		_lines.erase(_lines.begin() + index);
	}
}

void ScriptFile::removeLastLine()
{
	_lines.pop_back();
}

void ScriptFile::setCursorLineIndex(unsigned int index)
{
	_cursorLineIndex = index;
}

void ScriptFile::setCursorCharIndex(unsigned int index)
{
	_cursorCharIndex = index;
}

void ScriptFile::changeID(const string& newID)
{
	_ID = newID;
}

const string& ScriptFile::getID()
{
	return _ID;
}

const string& ScriptFile::getLineText(unsigned int index)
{
	if (index >= _lines.size())
	{
		Logger::throwError("Cannot retrieve scriptline at file \"" + _ID + "\" with index: " + to_string(index));
	}
	else
	{
		return _lines[index];
	}
}

unsigned int ScriptFile::getLineCount()
{
	return static_cast<unsigned int>(_lines.size());
}

unsigned int ScriptFile::getCursorLineIndex()
{
	return _cursorLineIndex;
}

unsigned int ScriptFile::getCursorCharIndex()
{
	return _cursorCharIndex;
}

const vector<string>& ScriptFile::getLines()
{
	return _lines;
}