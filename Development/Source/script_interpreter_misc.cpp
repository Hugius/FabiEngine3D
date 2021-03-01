#include "script_interpreter.hpp"

#include <sstream>

bool ScriptInterpreter::_isListValue(const string& valueString)
{
	// Check if value has enough characters
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is surrounded by braces
	if (valueString.front() != '{' || valueString.back() != '}')
	{
		return false;
	}

	return true;
}

bool ScriptInterpreter::_isVec3Value(const string& valueString)
{
	// Check if value has enough characters
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is surrounded by brackets
	if (valueString.front() != '[' || valueString.back() != ']')
	{
		return false;
	}

	// Remove brackets
	std::istringstream iss(valueString.substr(1, valueString.size() - 2));

	// Extract XYZ
	string x, y, z;
	iss >> x >> y >> z;

	// Check if value is a valid vec3
	return (_isDecimalValue(x) && _isDecimalValue(y) && _isDecimalValue(z));
}

bool ScriptInterpreter::_isStringValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	return valueString.size() >= 2 && (valueString.front() == '"' && valueString.back() == '"');
}

bool ScriptInterpreter::_isDecimalValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (valueString.front() == '-')
	{
		startingIndex = 1;
	}

	// Validate every character
	unsigned dots = 0;
	for (unsigned int i = startingIndex; i < valueString.size(); i++)
	{
		if (!isdigit(valueString[i]) && valueString[i] != '.')
		{
			return false;
		}

		// Count dots in value
		if (valueString[i] == '.')
		{
			dots++;
		}
	}

	// Check if value is a valid decimal
	return (valueString.size() >= 3) && (isdigit(valueString[startingIndex]) && isdigit(valueString.back())) && (dots == 1);
}

bool ScriptInterpreter::_isIntegerValue(const string& valueString)
{
	// Check if value has characters at all
	if (valueString.empty())
	{
		return false;
	}

	// Check if value is perhaps negative
	unsigned int startingIndex = 0;
	if (valueString.front() == '-')
	{
		startingIndex = 1;
	}

	// Check if every character is a digit
	for (unsigned int i = startingIndex; i < valueString.size(); i++)
	{
		if (!isdigit(valueString[i]))
		{
			return false;
		}
	}

	return true;
}

bool ScriptInterpreter::_isBooleanValue(const string& valueString)
{
	return (valueString == "<true>" || valueString == "<false>");
}

Vec3 ScriptInterpreter::_extractVec3FromString(const string& valueString)
{
	// Check if vec3 value
	if (!_isVec3Value(valueString))
	{
		_fe3d.logger_throwError("Tried to extract Vec3 value from non-vec3 valuestring!");
	}

	// Remove brackets
	std::istringstream iss(valueString.substr(1, valueString.size() - 2));

	// Extract XYZ
	string x, y, z;
	iss >> x >> y >> z;

	return Vec3(stof(x), stof(y), stof(z));
}

Ivec3 ScriptInterpreter::_extractVec3PartFromString(const string& valueString)
{
	Ivec3 parts = Ivec3(0);

	if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".x" || valueString.substr(valueString.size() - 2) == ".r"))
	{
		parts.x = 1;
	}
	else if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".y" || valueString.substr(valueString.size() - 2) == ".g"))
	{
		parts.y = 1;
	}
	else if (valueString.size() > 2 &&
		(valueString.substr(valueString.size() - 2) == ".z" || valueString.substr(valueString.size() - 2) == ".b"))
	{
		parts.z = 1;
	}

	return parts;
}

int ScriptInterpreter::_extractListIndexFromString(const string& valueString, bool& isAccessingList)
{
	auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
	auto closingBracketFound = std::find(valueString.begin(), valueString.end(), ']');

	// Check if brackets are in string
	if (openingBracketFound != valueString.end() && closingBracketFound != valueString.end())
	{
		// Temporary values
		unsigned int bracketIndex = std::distance(valueString.begin(), openingBracketFound);
		string indexString = valueString.substr(bracketIndex + 1);
		indexString.pop_back();

		// Check if index is a number
		if (_isIntegerValue(indexString))
		{
			isAccessingList = true;
			return stoi(indexString);
		}
		else if (_isLocalVariableExisting(indexString) || _isGlobalVariableExisting(indexString))
		{
			// Retrieve variable
			auto& variable = _isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString);

			// Check if variable is an integer
			if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::INTEGER)
			{
				_throwScriptError("list index must be an integer!");
			}
			else
			{
				isAccessingList = true;
				return variable.getValue().getInteger();
			}
		}
		else
		{
			_throwScriptError("invalid list indexing syntax!");
		}
	}

	return -1;
}

unsigned int ScriptInterpreter::_countFrontSpaces(const string& scriptLineText)
{
	int countedSpaces = 0;

	// For every character
	for (unsigned int i = 0; i < scriptLineText.size(); i++)
	{
		// Check if current character is a space
		if (scriptLineText[i] == ' ')
		{
			// Check if any text comes after the last space character
			if (i == (scriptLineText.size() - 1))
			{
				_throwScriptError("useless indentation!");
				return 0;
			}
			else
			{
				countedSpaces++;
			}
		}
		else
		{
			break;
		}
	}

	return countedSpaces;
}

bool ScriptInterpreter::_validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth)
{
	// Calculate scope depth of current scriptline
	unsigned int currentLineScopeDepth = countedSpaces / _spacesPerIndent;

	// Check if there is any code right after a scope change
	if (_scopeHasChanged && ((currentLineScopeDepth != scopeDepth) || scriptLineText.substr(0, 3) == "///"))
	{
		_throwScriptError("no indented code after scope change!");
	}
	else if (currentLineScopeDepth < scopeDepth) // End of current scope
	{
		scopeDepth = currentLineScopeDepth;
	}
	else if (currentLineScopeDepth > scopeDepth) // Outside of current scope
	{
		if (_passedScopeChanger) // Skip current line
		{
			return false;
		}
		else // Useless indented statement
		{
			_throwScriptError("useless indentation before statement!");
		}
	}

	_scopeHasChanged = false;
	return true;
}

bool ScriptInterpreter::_validateKeyInputString(const string& inputString)
{
	if (KEY_INPUT_STRING_MAP.find(inputString) == KEY_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid keyboard key!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateMouseInputString(const string& inputString)
{
	if (MOUSE_INPUT_STRING_MAP.find(inputString) == MOUSE_INPUT_STRING_MAP.end())
	{
		_throwScriptError("invalid mouse button!");
		return false;
	}

	return true;
}

ScriptConditionStatement* ScriptInterpreter::_getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth)
{
	unsigned int i = statements.size();
	while (i--)
	{
		if (statements[i].scopeDepth == scopeDepth)
		{
			return &statements[i];
		}
	}

	return nullptr;
}

void ScriptInterpreter::_throwScriptError(const string& message)
{
	_fe3d.logger_throwWarning("ERROR @ script \"" + _currentScriptIDsStack.back() + "\" @ line " +
		to_string(_currentLineIndexStack.back() + 1) + ": " + message);
	_hasThrownError = true;
}

void ScriptInterpreter::_checkEngineWarnings()
{
	auto messageStack = _fe3d.logger_getMessageStack();

	// Check if any new messages were logged
	if (messageStack.size() > _lastLoggerMessageCount)
	{
		// Loop over all new messages
		for (unsigned int i = _lastLoggerMessageCount - 1; i < messageStack.size(); i++)
		{
			// Check if logged message is a warning
			if (messageStack[i].substr(0, string("[Warn]").size()) == "[Warn]")
			{
				_hasThrownError = true;
			}
		}
	}
}

Vec2 ScriptInterpreter::_convertGuiPositionToViewport(Vec2 position)
{
	if (_fe3d.engine_getSelectedGame().empty())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
		auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
		position *= sizeMultiplier;
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position += Vec2(fabsf(offset.x), fabsf(offset.y));
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiPositionFromViewport(Vec2 position)
{
	if (_fe3d.engine_getSelectedGame().empty())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
		auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
		auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
		position -= Vec2(fabsf(offset.x), fabsf(offset.y));
		sizeMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight())) /
			Vec2(_fe3d.misc_getViewportSize());
		positionMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight())) /
			Vec2(_fe3d.misc_getViewportPosition());
		position *= sizeMultiplier;
	}

	return position;
}

Vec2 ScriptInterpreter::_convertGuiSizeToViewport(Vec2 size)
{
	if (_fe3d.engine_getSelectedGame().empty())
	{
		auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
			Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
		size = size * sizeMultiplier;
	}

	return size;
}

Vec2 ScriptInterpreter::_convertGuiSizeFromViewport(Vec2 size)
{
	if (_fe3d.engine_getSelectedGame().empty())
	{
		auto sizeMultiplier = Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight())) /
			Vec2(_fe3d.misc_getViewportSize());
		size = size * sizeMultiplier;
	}

	return size;
}

bool ScriptInterpreter::hasThrownError()
{
	return _hasThrownError;
}

bool ScriptInterpreter::gameMustStop()
{
	return _gameMustStop;
}