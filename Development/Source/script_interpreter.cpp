#include "script_interpreter.hpp"

ScriptInterpreter::ScriptInterpreter(Script& script) :
	_script(script)
{

}

void ScriptInterpreter::executeInitialization()
{
	for (auto& ID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(ID);

		// Loop over all scriptlines
		for (unsigned int i = 0; i < scriptFile->getLineCount(); i++)
		{
			auto scriptLine = scriptFile->getLineText(i);
			if (scriptLine.substr(0, 4) == "META")
			{

			}
		}
	}
}

void ScriptInterpreter::executeUpdate()
{

}

void ScriptInterpreter::executeDestruction()
{

}

void ScriptInterpreter::_executeInitialization()
{
}

void ScriptInterpreter::_executeUpdate()
{
}

void ScriptInterpreter::_executeDestruction()
{
}
