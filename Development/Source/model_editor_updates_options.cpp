#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void ModelEditor::_updateOptionsMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuOptions")
	{
		// Temporary values
		auto lodID = _fe3d.modelEntity_getLevelOfDetailEntityID(_currentModelID);
		auto color = _fe3d.modelEntity_getColor(_currentModelID);
		auto uvRepeat = _fe3d.modelEntity_getUvRepeat(_currentModelID);
		auto isFaceculled = _fe3d.modelEntity_isFaceCulled(_currentModelID);
		auto isTransparent = _fe3d.modelEntity_isTransparent(_currentModelID);
		auto isInstanced = _fe3d.modelEntity_isInstanced(_currentModelID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
				return;
			}
			else if (screen->getButton("isFaceculled")->isHovered())
			{
				isFaceculled = !isFaceculled;
				_fe3d.modelEntity_setFaceCulled(_currentModelID, isFaceculled);
			}
			else if (screen->getButton("isTransparent")->isHovered())
			{
				isTransparent = !isTransparent;
				_fe3d.modelEntity_setTransparent(_currentModelID, isTransparent);
			}
			else if (screen->getButton("isInstanced")->isHovered())
			{
				isInstanced = !isInstanced;

				if (isInstanced)
				{
					_fe3d.modelEntity_enableInstancing(_currentModelID, { Vec3(0.0f) });
				}
				else
				{
					_fe3d.modelEntity_disableInstancing(_currentModelID);
				}
				
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("uvRepeat", "UV Repeat", uvRepeat, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("lodID")->isHovered())
			{
				lodID = (lodID.empty()) ? lodID : lodID.substr(1, lodID.size() - 1);
				_gui.getGlobalScreen()->createValueForm("lodID", "LOD entity ID", lodID, Vec2(0.0f, 0.1f), Vec2(0.4f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r, {}))
		{
			color.r = clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.modelEntity_setColor(_currentModelID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g, {}))
		{
			color.g = clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.modelEntity_setColor(_currentModelID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b, {}))
		{
			color.b = clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.modelEntity_setColor(_currentModelID, color);
		}
		if (_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat, {}))
		{
			_fe3d.modelEntity_setUvRepeat(_currentModelID, uvRepeat);
		}
		if (_gui.getGlobalScreen()->checkValueForm("lodID", lodID, {}))
		{
			if (lodID == "@") // No LOD entity
			{
				_fe3d.modelEntity_setLevelOfDetailEntity(_currentModelID, "");
			}
			else if (find(_loadedModelIDs.begin(), _loadedModelIDs.end(), "@" + lodID) == _loadedModelIDs.end()) // Check LOD entity
			{
				Logger::throwWarning("Cannot find LOD entity with ID \"" + lodID + "\"");
			}
			else // Set LOD entity
			{
				_fe3d.modelEntity_setLevelOfDetailEntity(_currentModelID, "@" + lodID);
			}
		}

		// Update button text contents
		screen->getButton("isFaceculled")->changeTextContent(isFaceculled ? "Culling: ON" : "Culling: OFF");
		screen->getButton("isTransparent")->changeTextContent(isTransparent ? "Alpha: ON" : "Alpha: OFF");
		screen->getButton("isInstanced")->changeTextContent(isInstanced ? "Instanced: ON" : "Instanced: OFF");
	}
}