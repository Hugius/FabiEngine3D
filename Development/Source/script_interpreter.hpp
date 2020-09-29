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
	FabiEngine3D& _fe3d;
	Script& _script;

	void _executeScript(const string& ID);

	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;
};