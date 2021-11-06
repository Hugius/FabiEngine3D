#pragma once

#include "script_file.hpp"

class Script final
{
public:
	Script(FabiEngine3D& fe3d);

	// Voids
	void createScriptFile(const string& ID);
	void renameScriptFile(const string& ID, const string& newID);
	void removeScriptFile(const string& ID);
	void reset();

	// Strings
	const vector<string> getAllScriptFileIDs();

	// Integers
	const vector<pair<string, unsigned int>> findKeyword(const string& keyword);
	unsigned int getScriptFileCount();
	unsigned int getTotalLineCount();

	// Booleans
	bool isScriptFileExisting(const string& ID);

	// Miscellaneous
	shared_ptr<ScriptFile> getScriptFile(const string& ID);

private:
	// Miscellaneous
	vector<shared_ptr<ScriptFile>> _scriptFiles;
	FabiEngine3D& _fe3d;
};