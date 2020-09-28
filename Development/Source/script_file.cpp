#include "script_file.hpp"

ScriptFile::ScriptFile(FabiEngine3D& fe3d, const string& ID) :
	_fe3d(fe3d),
	_ID(ID)
{

}

void ScriptFile::addNewLine(const string& textContent)
{
	_lines.push_back(textContent);
}

void ScriptFile::setLineText(unsigned int index, const string& textContent)
{
	if (index >= _lines.size())
	{
		_fe3d.logger_throwError("Could not set scriptline text content at file \'" + _ID + "\' with index: " + to_string(index));
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
		_fe3d.logger_throwError("Could not delete scriptline at file \'" + _ID + "\' with index: " + to_string(index));
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

const string& ScriptFile::getID()
{
	return _ID;
}

const string& ScriptFile::getLineText(unsigned int index)
{
	if (index >= _lines.size())
	{
		_fe3d.logger_throwError("Could not retrieve scriptline at file \'" + _ID + "\' with index: " + to_string(index));
	}
	else
	{
		return _lines[index];
	}
}

unsigned int ScriptFile::getLineCount()
{
	return _lines.size();
}