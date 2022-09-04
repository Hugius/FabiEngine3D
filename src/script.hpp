#pragma once

#include "script_file.hpp"

class Script final
{
public:
	void createScriptFile(const string & scriptId);
	void renameScriptFile(const string & scriptId, const string & newScriptId);
	void deleteScriptFile(const string & scriptId);
	void replaceKeyword(const string & oldKeyword, const string & newKeyword);
	void clear();

	const map<string, vector<int>> searchKeyword(const string & keyword) const;

	const vector<string> getScriptFileIds() const;

	const shared_ptr<ScriptFile> getScriptFile(const string & scriptId) const;

	const int getScriptFileCount() const;
	const int getTotalLineCount() const;

	const bool isScriptFileExisting(const string & scriptId) const;
	const bool isEmpty();

private:
	map<string, shared_ptr<ScriptFile>> _scriptFiles = {};
};