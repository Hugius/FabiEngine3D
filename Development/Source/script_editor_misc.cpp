#include "script_editor.hpp"

void ScriptEditor::_reloadScriptTextDisplay()
{
	if (_isLoaded)
	{
		// Remove all existing billboards
		_fe3d.billboardEntity_deleteAll();

		// Create a billboard for every line number
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
		{
			// Generation values
			string ID = to_string(lineIndex);
			string textContent = to_string(lineIndex + 1);
			vec3 position = _scriptTextStartingPosition - vec3((textContent.size() - 1) * (_textCharacterSize.x / 2.0f), _verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
			vec2 size = vec2(textContent.size() * _textCharacterSize.x, _textCharacterSize.y);

			// Create new billboard
			_fe3d.billBoardEntity_add(ID, textContent, _fontPath, _lineNumberColor, position, vec3(0.0f), size, 0, 0);
		}

		// Create a billboard for every character in every scriptline
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount(); lineIndex++)
		{
			// Retrieve line text
			string textContent = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);

			// Generation values
			const vec3 linePosition = _fe3d.billboardEntity_getPosition(to_string(lineIndex));
			
			// Loop over every character
			for (unsigned int charIndex = 0; charIndex < textContent.size(); charIndex++)
			{
				// Generation values
				string ID = to_string(lineIndex) + "_" + to_string(charIndex);
				string charContent = string(1, textContent[charIndex]);
				vec3 position = linePosition + vec3(_horizontalLineOffset + (_horizontalCharacterOffset * static_cast<float>(charIndex)), 0.0f, 0.0f);

				// Create new billboard
				_fe3d.billBoardEntity_add(ID, charContent, _fontPath, _characterColor, position, vec3(0.0f), _textCharacterSize, 0, 0);
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (!_isScriptLoadedFromFile)
	{
		_loadScriptFromFile();
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