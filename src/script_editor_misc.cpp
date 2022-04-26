#include "script_editor.hpp"

#include <sstream>

using std::istringstream;

void ScriptEditor::_createScriptDisplayEntities()
{
	const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();

	const auto separatorId = "separator";
	const auto separatorPosition = (ROOT_TEXT_POSITION + fvec3(HORIZONTAL_LINE_OFFSET * 0.5f, -(((static_cast<float>(lineCount) - 1) * 0.5f) * VERTICAL_LINE_OFFSET), 0.0f));
	const auto separatorSize = fvec2((CHAR_SIZE.x * 0.25f), (static_cast<float>(lineCount) * VERTICAL_LINE_OFFSET));

	_fe3d->quad3d_create(separatorId, true);
	_fe3d->quad3d_setPosition(separatorId, separatorPosition);
	_fe3d->quad3d_setSize(separatorId, separatorSize);
	_fe3d->quad3d_setColor(separatorId, SEPARATOR_COLOR);
	_fe3d->quad3d_setBright(separatorId, true);

	_loadedQuadIds.push_back(separatorId);

	for(int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		const auto lineNumberId = ("number_" + to_string(lineIndex));
		const auto lineNumberString = to_string(lineIndex + 1);
		const auto lineNumberOffset = -fvec3((lineNumberString.size() - 1) * (CHAR_SIZE.x * 0.5f), VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f);
		const auto lineNumberPosition = (ROOT_TEXT_POSITION + lineNumberOffset);
		const auto lineNumberSize = fvec2((lineNumberString.size() * CHAR_SIZE.x), CHAR_SIZE.y);

		_fe3d->text3d_create(lineNumberId, FONT_MAP_PATH, true);
		_fe3d->text3d_setMinTextureAlpha(lineNumberId, 0.05f);
		_fe3d->text3d_setContent(lineNumberId, lineNumberString);
		_fe3d->text3d_setPosition(lineNumberId, lineNumberPosition);
		_fe3d->text3d_setSize(lineNumberId, lineNumberSize);
		_fe3d->text3d_setColor(lineNumberId, LINE_NUMBER_COLOR);
		_fe3d->text3d_setBright(lineNumberId, true);

		_loadedTextIds.push_back(lineNumberId);

		const auto lineTextId = ("text_" + to_string(lineIndex));
		const auto lineTextString = _script->getScriptFile(_currentScriptFileId)->getLine(lineIndex);
		const auto lineTextOffset = fvec3((((lineTextString.size() - 1) * (CHAR_SIZE.x * 0.5f)) + HORIZONTAL_LINE_OFFSET), (-VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex)), 0.0f);
		const auto lineTextPosition = (ROOT_TEXT_POSITION + lineTextOffset);
		const auto lineTextSize = fvec2(lineTextString.size() * CHAR_SIZE.x, CHAR_SIZE.y);

		istringstream iss(lineTextString);
		string noWhiteSpace;
		iss >> noWhiteSpace;
		const auto isComment = (noWhiteSpace.substr(0, 3) == "///");

		_fe3d->text3d_create(lineTextId, FONT_MAP_PATH, true);
		_fe3d->text3d_setMinTextureAlpha(lineTextId, 0.05f);
		_fe3d->text3d_setContent(lineTextId, lineTextString);
		_fe3d->text3d_setPosition(lineTextId, lineTextPosition);
		_fe3d->text3d_setSize(lineTextId, lineTextSize);
		_fe3d->text3d_setColor(lineTextId, (isComment ? COMMENT_TEXT_COLOR : DEFAULT_TEXT_COLOR));
		_fe3d->text3d_setBright(lineTextId, true);

		_loadedTextIds.push_back(lineTextId);

		const auto lineAabbId = to_string(lineIndex);
		const auto lineAabbOffset = fvec3(0.0f, 0.0f, -AABB_DEPTH);
		const auto lineAabbPosition = (lineTextPosition + lineAabbOffset);
		const auto lineAabbSize = fvec3(FLT_MAX, CHAR_SIZE.y, AABB_DEPTH);

		_fe3d->aabb_create(lineAabbId, true);
		_fe3d->aabb_setBasePosition(lineAabbId, lineAabbPosition);
		_fe3d->aabb_setBaseSize(lineAabbId, lineAabbSize);

		_loadedAabbIds.push_back(lineAabbId);

		for(int charIndex = 0; charIndex < static_cast<int>(lineTextString.size()); charIndex++)
		{
			const auto characterId = (to_string(lineIndex) + "_" + to_string(charIndex));
			const auto characterOffset = fvec3(((CHAR_OFFSET * static_cast<float>(charIndex)) + HORIZONTAL_LINE_OFFSET), (-VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex)), 0.0f);
			const auto characterPosition = (ROOT_TEXT_POSITION + characterOffset);
			const auto characterAabbOffset = fvec3(0.0f);
			const auto characterAabbPosition = (characterPosition + characterAabbOffset);
			const auto characterAabbSize = fvec3(CHAR_SIZE.x, CHAR_SIZE.y, AABB_DEPTH);

			_fe3d->aabb_create(characterId, true);
			_fe3d->aabb_setBasePosition(characterId, characterAabbPosition);
			_fe3d->aabb_setBaseSize(characterId, characterAabbSize);

			_loadedAabbIds.push_back(characterId);
		}
	}
}

void ScriptEditor::_deleteScriptDisplayEntities()
{
	for(const auto & id : _loadedQuadIds)
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto & id : _loadedTextIds)
	{
		_fe3d->text3d_delete(id);
	}

	for(const auto & id : _loadedAabbIds)
	{
		_fe3d->aabb_delete(id);
	}

	_loadedQuadIds.clear();
	_loadedTextIds.clear();
	_loadedAabbIds.clear();
}

void ScriptEditor::_clearDisplay()
{
	_deleteScriptDisplayEntities();
	_fe3d->quad3d_setVisible("selection", false);
	_fe3d->text3d_setVisible("cursor", false);
	_isWritingScript = false;
	_currentScriptFileId = "";
}

void ScriptEditor::_clearSelection()
{
	_fe3d->quad3d_setVisible("selection", false);
	_fe3d->quad3d_setPosition("selection", fvec3(0.0f));
	_fe3d->quad3d_setSize("selection", fvec2(0.0f));

	_firstSelectionAabbId = "";
	_secondSelectionAabbId = "";
	_selectionType = {};
}

void ScriptEditor::inject(shared_ptr<Script> script)
{
	_script = script;
}

const bool ScriptEditor::isWritingScript() const
{
	return !_currentScriptFileId.empty();
}