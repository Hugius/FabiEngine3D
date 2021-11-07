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
	const vector<string> getAllScriptFileIDs() const;

	// Integers
	const vector<pair<string, unsigned int>> findKeyword(const string& keyword) const;
	const unsigned int getScriptFileCount() const;
	const unsigned int getTotalLineCount() const;

	// Booleans
	const bool isScriptFileExisting(const string& ID) const;

	// Miscellaneous
	shared_ptr<ScriptFile> getScriptFile(const string& ID) const;

private:
	// Miscellaneous
	vector<shared_ptr<ScriptFile>> _scriptFiles;
	FabiEngine3D& _fe3d;
};