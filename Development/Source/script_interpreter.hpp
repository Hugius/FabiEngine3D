#pragma once

#include "script.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script);

	void load();
	void executeInitialization();
	void executeUpdate();
	void executeDestruction();
	void unload();

private:
	enum class ScriptType
	{
		INIT,
		UPDATE,
		DESTROY
	};

	FabiEngine3D& _fe3d;
	Script& _script;

	void _executeScript(const string& ID, ScriptType type);

	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;

	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";
};