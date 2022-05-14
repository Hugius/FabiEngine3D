#include "script_interpreter.hpp"

const vector<shared_ptr<ScriptValue>> ScriptInterpreter::_processFe3dFunctionCall(const string & scriptLine)
{
	const auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	const auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) || (closingParanthesisFound == scriptLine.end()))
	{
		_throwRuntimeError("invalid syntax");

		return {};
	}

	if(scriptLine.back() != ')')
	{
		_throwRuntimeError("invalid syntax");

		return {};
	}

	const auto parenthesisIndex = static_cast<int>(distance(scriptLine.begin(), openingParanthesisFound));
	const auto functionName = scriptLine.substr(0, parenthesisIndex);
	const auto argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1), (scriptLine.size() - static_cast<size_t>(parenthesisIndex + 1) - 1));
	const auto args = _extractValuesFromListString(argumentString);

	vector<shared_ptr<ScriptValue>> returnValues = {};

	bool isExecuted = false;

	if(_hasThrownError)
	{
		return {};
	}

	isExecuted = (isExecuted || _executeFe3dSkySetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSkyGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dTerrainSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dTerrainGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dWaterSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dWaterGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dModelSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dModelGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dQuad3dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dQuad3dGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dText3dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dText3dGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dAabbSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dAabbGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dQuad2dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dQuad2dGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dText2dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dText2dGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dPointlightSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dPointlightGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSpotlightSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSpotlightGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dCaptorSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dCaptorGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSound3dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSound3dGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSound2dSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dSound2dGetter(functionName, args, returnValues));
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
	isExecuted = (isExecuted || _executeFe3dClockSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dClockGetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dUncategorizedSetter(functionName, args, returnValues));
	isExecuted = (isExecuted || _executeFe3dUncategorizedGetter(functionName, args, returnValues));

	if(!isExecuted)
	{
		_throwRuntimeError("fe3d function does not exist");

		return {};
	}

	_engineFunctionCallCount++;

	return returnValues;
}