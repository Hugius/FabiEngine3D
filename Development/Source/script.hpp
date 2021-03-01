#pragma once

#include "script_file.hpp"

class Script final
{
public:
	Script(FabiEngine3D& fe3d);

	void addScriptFile(const string& ID);
	void renameScriptFile(const string& ID, const string& newID);
	void removeScriptFile(const string& ID);
	void reset();

	unsigned int getScriptFileCount();
	unsigned int getTotalLineCount();

	bool isScriptFileExisting(const string& ID);

	shared_ptr<ScriptFile> getScriptFile(const string& ID);

	const vector<string> getAllScriptFileIDs();
	const vector<pair<string, unsigned int>> findKeyword(const string& keyword);

private:
	FabiEngine3D& _fe3d;

	vector<shared_ptr<ScriptFile>> _scriptFiles;
};