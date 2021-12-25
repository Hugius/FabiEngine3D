#include "script_interpreter.hpp"

const vector<ScriptValue> ScriptInterpreter::_processFe3dFunctionCall(const string& scriptLine)
{
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
	}

	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
	}

	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto args = _extractValuesFromListString(argumentString);

	if(!_hasThrownError)
	{
		auto functionName = scriptLine.substr(0, parenthesisIndex);
		bool isExecuted = false;

		isExecuted = (isExecuted || _executeFe3dSkySetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSkyGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation3dSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation3dGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation2dSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dAnimation2dGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound2dSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound2dGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound3dSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dSound3dGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dInputGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemGetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscSetter(functionName, args, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscGetter(functionName, args, returnValues));

		if(!isExecuted)
		{
			_throwScriptError("fe3d function not existing!");

		}

		_engineFunctionCallCount++;
	}

	return returnValues;
}