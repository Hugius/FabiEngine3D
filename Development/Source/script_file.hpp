#pragma once

#include "fabi_engine_3d.hpp"

class ScriptFile
{
public:
	ScriptFile(FabiEngine3D& fe3d, const string& ID);

	void insertNewLine(unsigned int index, const string& textContent);
	void setLineText(unsigned int index, const string& textContent);
	void removeLine(unsigned int index);
	void removeLastLine();

	const string& getID();
	const string& getLineText(unsigned int index);
	unsigned int getLineCount();

private:
	FabiEngine3D& _fe3d;
	const string _ID;

	vector<string> _lines;
};