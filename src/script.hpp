#pragma once

#include "script_file.hpp"

class Script final
{
public:
	Script(FabiEngine3D& fe3d);

	// VOID
	void createScriptFile(const string& ID);
	void renameScriptFile(const string& ID, const string& newID);
	void removeScriptFile(const string& ID);
	void reset();

	// STRING
	const vector<string> getScriptFileIDs() const;

	// UNSIGNED INT
	const vector<pair<string, unsigned int>> findKeyword(const string& keyword) const;
	const unsigned int getScriptFileCount() const;
	const unsigned int getTotalLineCount() const;

	// BOOL
	const bool isScriptFileExisting(const string& ID) const;

	// MISCELLANEOUS
	shared_ptr<ScriptFile> getScriptFile(const string& ID) const;

private:
	// MISCELLANEOUS
	vector<shared_ptr<ScriptFile>> _scriptFiles;
	FabiEngine3D& _fe3d;
};