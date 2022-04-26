#pragma once

#include "script_file.hpp"

class Script final
{
public:
	void createScriptFile(const string & id);
	void renameScriptFile(const string & id, const string & newId);
	void deleteScriptFile(const string & id);
	void clear();

	const unordered_map<string, unsigned int> findKeyword(const string & keyword) const;

	const vector<string> getScriptFileIds() const;

	const shared_ptr<ScriptFile> getScriptFile(const string & id) const;

	const int getScriptFileCount() const;
	const int getTotalLineCount() const;

	const bool isScriptFileExisting(const string & id) const;
	const bool isEmpty();

private:
	map<string, shared_ptr<ScriptFile>> _scriptFiles = {};
};