#include "script_editor.hpp"

#include <sstream>

using std::istringstream;

void ScriptEditor::_reloadScriptTextDisplay(bool reloadAabbs)
{
	// Remove all existing BILLBOARD & AABB entities
	_fe3d.billboardEntity_deleteAll();
	_fe3d.aabbEntity_deleteAll();

	// Create line separator BILLBOARD
	float lineCount = static_cast<float>(_script.getScriptFile(_currentScriptFileID)->getLineCount());
	Vec2 separatorSize = Vec2((TEXT_CHARACTER_SIZE.x / 4.0f), (lineCount * VERTICAL_LINE_OFFSET));
	Vec3 separatorPosition = SCRIPT_TEXT_STARTING_POSITION + Vec3(HORIZONTAL_LINE_OFFSET / 2.0f, -(((lineCount - 1) / 2.0f) * VERTICAL_LINE_OFFSET), 0.0f);
	_fe3d.billboardEntity_create("separator");
	_fe3d.billboardEntity_setPosition("separator", (separatorPosition - Vec3(0.0f, separatorSize.y / 2.0f, 0.0f)));
	_fe3d.billboardEntity_setSize("separator", separatorSize);
	_fe3d.billboardEntity_setColor("separator", SEPARATOR_COLOR);
	_fe3d.billboardEntity_setBright("separator", true);

	// Create visible billboards for display and invisible billboards for logic
	for (unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		// Generation values
		const string lineNumberID = to_string(lineIndex);
		const string lineTextID = "text_" + lineNumberID;
		const string lineNumberString = to_string(lineIndex + 1);
		const string lineTextString = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
		const Vec2 lineNumberSize = Vec2(lineNumberString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const Vec2 lineTextSize = Vec2(lineTextString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const Vec3 lineNumberPosition = SCRIPT_TEXT_STARTING_POSITION -
			Vec3((lineNumberString.size() - 1) * (TEXT_CHARACTER_SIZE.x / 2.0f), VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f);
		const Vec3 lineTextPosition = SCRIPT_TEXT_STARTING_POSITION +
			Vec3((lineTextString.size() - 1) * (TEXT_CHARACTER_SIZE.x / 2.0f), -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f) +
			Vec3(HORIZONTAL_LINE_OFFSET, 0.0f, 0.0f);

		// Create line number BILLBOARD
		_fe3d.billboardEntity_create(lineNumberID);
		_fe3d.billboardEntity_setFont(lineNumberID, FONT_PATH);
		_fe3d.billboardEntity_setTextContent(lineNumberID, lineNumberString);
		_fe3d.billboardEntity_setPosition(lineNumberID, (lineNumberPosition - Vec3(0.0f, lineNumberSize.y / 2.0f, 0.0f)));
		_fe3d.billboardEntity_setSize(lineNumberID, lineNumberSize);
		_fe3d.billboardEntity_setColor(lineNumberID, LINE_NUMBER_COLOR);
		_fe3d.billboardEntity_setBright(lineNumberID, true);

		// Create line number AABB
		const Vec3 lineAabbPosition = (lineNumberPosition - Vec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, AABB_DEPTH));
		const Vec3 lineAabbSize = Vec3(TEXT_CHARACTER_SIZE.x * static_cast<float>(MAX_CHARACTERS_PER_LINE * 2) * 1.1f, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
		_fe3d.aabbEntity_create(lineNumberID);
		_fe3d.aabbEntity_setPosition(lineNumberID, lineAabbPosition);
		_fe3d.aabbEntity_setSize(lineNumberID, lineAabbSize);

		// Create line text display BILLBOARD
		istringstream iss(lineTextString);
		string noWhiteSpace;
		iss >> noWhiteSpace;
		bool isComment = (noWhiteSpace.substr(0, 3) == "///");
		_fe3d.billboardEntity_create(lineTextID);
		_fe3d.billboardEntity_setFont(lineTextID, FONT_PATH);
		_fe3d.billboardEntity_setTextContent(lineTextID, lineTextString);
		_fe3d.billboardEntity_setPosition(lineTextID, (lineTextPosition - Vec3(0.0f, lineTextSize.y / 2.0f, 0.0f)));
		_fe3d.billboardEntity_setSize(lineTextID, lineTextSize);
		_fe3d.billboardEntity_setColor(lineTextID, (isComment ? COMMENT_TEXT_COLOR : DEFAULT_TEXT_COLOR));
		_fe3d.billboardEntity_setBright(lineTextID, true);

		// Iterate through every character
		for (unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
		{
			// Create new character BILLBOARD for logic
			const string characterID = (lineNumberID + "_" + to_string(charIndex));
			const float characterX = (HORIZONTAL_LINE_OFFSET + (HORIZONTAL_CHARACTER_OFFSET * static_cast<float>(charIndex)));
			const Vec3 characterPosition = (SCRIPT_TEXT_STARTING_POSITION + Vec3(characterX, -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f));
			_fe3d.billboardEntity_create(characterID);
			_fe3d.billboardEntity_setPosition(characterID, (characterPosition - Vec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, 0.0f)));
			_fe3d.billboardEntity_setSize(characterID, TEXT_CHARACTER_SIZE);
			_fe3d.billboardEntity_setVisible(characterID, false);

			// Create new character AABB for logic
			if (reloadAabbs)
			{
				const Vec3 characterAabbPosition = (characterPosition - Vec3(0.0f, TEXT_CHARACTER_SIZE.y / 2.0f, 0.0f));
				const Vec3 characterAabbSize = Vec3(TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
				_fe3d.aabbEntity_create(characterID);
				_fe3d.aabbEntity_setPosition(characterID, characterAabbPosition);
				_fe3d.aabbEntity_setSize(characterID, characterAabbSize);
			}
		}
	}
}

void ScriptEditor::_copySelectedText()
{
	if (_firstSelectedLineIndex != -1) // Check if anything is selected at all
	{
		_copyClipboard.clear(); // Clear last copy

		if (_lastSelectedLineIndex == -1) // Check if only 1 line selected
		{
			_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(_firstSelectedLineIndex));
		}
		else // If multiple selected lines
		{
			// Determine selection direction
			for (int i = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
				i <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); i++)
			{
				_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(i)); // Copy text lines
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor()
{	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
	_scriptExecutor.setCurrentProjectID(projectID);
}

bool ScriptEditor::isLoaded()
{
	return _isEditorLoaded;
}

bool ScriptEditor::isWritingScript()
{
	return !_currentScriptFileID.empty();
}