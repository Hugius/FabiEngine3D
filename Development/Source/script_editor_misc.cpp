#include "script_editor.hpp"

void ScriptEditor::_reloadScriptTextDisplay()
{
	if (_isLoaded)
	{
		// Remove all existing billboards & their respective AABBs
		_fe3d.billboardEntity_deleteAll();
		_fe3d.aabbEntity_deleteAll();

		// Create visible billboards for display and invisible billboards for logic
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
		{
			// Generation values
			string lineNumberID = to_string(lineIndex);
			string lineTextID = lineNumberID + "_text";
			string lineNumberString = to_string(lineIndex + 1);
			string lineTextString = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
			vec2 lineNumberSize = vec2(lineNumberString.size() * _textCharacterSize.x, _textCharacterSize.y);
			vec2 lineTextSize = vec2(lineTextString.size() * _textCharacterSize.x, _textCharacterSize.y);
			vec3 lineNumberPosition = _scriptTextStartingPosition -
				vec3((lineNumberString.size() - 1) * (_textCharacterSize.x / 2.0f), _verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
			vec3 lineTextPosition = _scriptTextStartingPosition +
				vec3((lineTextString.size() - 1) * (_textCharacterSize.x / 2.0f), -_verticalLineOffset * static_cast<float>(lineIndex), 0.0f) +
				vec3(_horizontalCharacterOffset + _textCharacterSize.x, 0.0f, 0.0f);

			// Create line billboard
			_fe3d.billBoardEntity_add(lineNumberID, lineNumberString, _fontPath, _lineNumberColor, lineNumberPosition, vec3(0.0f), lineNumberSize, 0, 0);
			vec3 aabbPosition = lineNumberPosition - vec3(0.0f, _textCharacterSize.y / 2.0f, 0.0f);
			vec3 aabbSize = vec3(_textCharacterSize.x * static_cast<float>(_maxCharactersPerLine * 2), _textCharacterSize.y, 0.05f);
			_fe3d.aabbEntity_add(lineNumberID, aabbPosition, aabbSize, true);

			// Create line text display billboard
			_fe3d.billBoardEntity_add(lineTextID, lineTextString, _fontPath, _characterColor, lineTextPosition, vec3(0.0f), lineTextSize, false, false);

			// Loop over every character
			for (unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
			{
				// Generation values
				string characterID = lineNumberID + "_" + to_string(charIndex);
				float characterX = _horizontalLineOffset + (_horizontalCharacterOffset * static_cast<float>(charIndex));
				vec3 characterPosition = lineNumberPosition + vec3(characterX, 0.0f, 0.0f);

				// Create new billboard
				_fe3d.billBoardEntity_add(characterID, vec3(0.0f), characterPosition, vec3(0.0f), _textCharacterSize, false, false, false);
				_fe3d.aabbEntity_bindToBillboardEntity(characterID, true);
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (!_isScriptLoadedFromFile)
	{
		_loadScriptsFromFile();
	}
	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}