#pragma once

#include "script_file.hpp"

class Script final
{
public:
	Script(FabiEngine3D& fe3d);

	void addScriptFile(const string& ID);
	void removeScriptFile(const string& ID);
	void reset();

	int getScriptFileCount();

	bool isScriptFileExisting(const string& ID);

	shared_ptr<ScriptFile> getScriptFile(const string& ID);

	vector<string> getAllScriptFileIDs();

private:
	FabiEngine3D& _fe3d;

	vector<shared_ptr<ScriptFile>> _scriptFiles;
};