#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_processEngineFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if (scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractValuesFromListString(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				// Temporary values
				auto functionName = scriptLine.substr(0, parenthesisIndex);
				bool executed = false;

				// Possibly execute FE3D function
				executed = (executed || _executeFe3dInputGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dCameraFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dSkySetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dSkyGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dTerrainGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dWaterSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dWaterGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dModelSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dModelGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dBillboardSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dBillboardGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dAabbSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dAabbGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dLightSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dLightGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dReflectionSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dReflectionGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dImageSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dImageGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dTextSetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dTextGetterFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dSoundFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dRaycastFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dCollisionFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dLightingFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dGraphicsFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dMusicFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dFilesystemFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dSceneFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dServerFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dClientFunction(functionName, arguments, returnValues));
				executed = (executed || _executeFe3dMiscFunction(functionName, arguments, returnValues));

				// Check if function call exists
				if (executed)
				{
					_engineFunctionCallCount++;
				}
				else
				{
					_throwScriptError("fe3d function not found!");
				}
			}
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return returnValues;
}