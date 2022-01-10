#pragma once

#include "script_file.hpp"

class Script final
{
public:
	void createScriptFile(const string& ID);
	void renameScriptFile(const string& ID, const string& newID);
	void deleteScriptFile(const string& ID);
	void reset();

	const vector<string> getScriptFileIDs() const;

	const vector<pair<string, unsigned int>> findKeyword(const string& keyword) const;
	const unsigned int getScriptFileCount() const;
	const unsigned int getTotalLineCount() const;

	const bool isScriptFileExisting(const string& ID) const;

	shared_ptr<ScriptFile> getScriptFile(const string& ID) const;

private:
	vector<shared_ptr<ScriptFile>> _scriptFiles;
};