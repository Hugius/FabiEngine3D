#pragma once

#include "script_file.hpp"

class Script final
{
public:
	void createScriptFile(const string& id);
	void renameScriptFile(const string& id, const string& newId);
	void deleteScriptFile(const string& id);
	void clear();

	const vector<string> getScriptFileIds() const;

	const vector<pair<string, unsigned int>> findKeyword(const string& keyword) const;

	const unsigned int getScriptFileCount() const;
	const unsigned int getTotalLineCount() const;

	const bool isScriptFileExisting(const string& id) const;
	const bool isEmpty();

	shared_ptr<ScriptFile> getScriptFile(const string& id) const;

private:
	vector<shared_ptr<ScriptFile>> _scriptFiles;
};