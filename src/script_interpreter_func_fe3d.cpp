#include "script_interpreter.hpp"

const vector<ScriptValue> ScriptInterpreter::_processEngineFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has no opening & closing parentheses
	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
	}

	// Check if function call does not end with a paranthesis
	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
	}

	// Extract arguments from argument string
	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto arguments = _extractValuesFromListString(argumentString);

	// Check if argument extraction went well
	if(!_hasThrownError)
	{
		// Temporary values
		auto functionName = scriptLine.substr(0, parenthesisIndex);
		bool isExecuted = false;

		// Possibly execute FE3D function
		isExecuted = (isExecuted || _executeFe3dSkySetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSkyGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation3dSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation3dGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound2dSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound2dGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound3dSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound3dGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dInputGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldGetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscSetter(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscGetter(functionName, arguments, returnValues));

		// Check if function call not existing
		if(!isExecuted)
		{
			_throwScriptError("fe3d function not existing!");

		}

		// Increase function calls
		_engineFunctionCallCount++;
	}

	return returnValues;
}