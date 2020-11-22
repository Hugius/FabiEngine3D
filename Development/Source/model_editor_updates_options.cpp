#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingOptions()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "modelEditorMenuOptions")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			}
			else if (screen->getButton("isFaceculled")->isHovered())
			{
				_fe3d.gameEntity_setFaceCulled(_currentModelID, !_fe3d.gameEntity_isFaceCulled(_currentModelID));
			}
			else if (screen->getButton("isTransparent")->isHovered())
			{
				_fe3d.gameEntity_setTransparent(_currentModelID, !_fe3d.gameEntity_isTransparent(_currentModelID));
			}
			else if (screen->getButton("isInstanced")->isHovered())
			{
				_fe3d.gameEntity_setInstanced(_currentModelID, !_fe3d.gameEntity_isInstanced(_currentModelID), { Vec3(0.0f) });
			}
			else if (screen->getButton("setColor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.gameEntity_getColor(_currentModelID).r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.gameEntity_getColor(_currentModelID).g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.gameEntity_getColor(_currentModelID).b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", _fe3d.gameEntity_getUvRepeat(_currentModelID), Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("lodID")->isHovered())
			{
				string lodID = _fe3d.gameEntity_getLevelOfDetailEntityID(_currentModelID);
				lodID = (lodID == "") ? lodID : lodID.substr(1, lodID.size() - 1);
				_gui.getGlobalScreen()->addValueForm("lodID", "LOD entity ID", lodID, Vec2(0.0f, 0.0f), Vec2(0.4f, 0.1f));
			}
		}

		// Update GUI button contents
		auto faceculledID = screen->getButton("isFaceculled")->getTextfield()->getEntityID();
		auto isCulled = _fe3d.gameEntity_isFaceCulled(_currentModelID);
		auto transparentID = screen->getButton("isTransparent")->getTextfield()->getEntityID();
		auto isTransparent = _fe3d.gameEntity_isTransparent(_currentModelID);
		auto instancedID = screen->getButton("isInstanced")->getTextfield()->getEntityID();
		auto isInstanced = _fe3d.gameEntity_isInstanced(_currentModelID);
		_fe3d.textEntity_setTextContent(faceculledID, isCulled ? "Culling: ON" : "Culling: OFF");
		_fe3d.textEntity_setTextContent(transparentID, isTransparent ? "Alpha: ON" : "Alpha: OFF");
		_fe3d.textEntity_setTextContent(instancedID, isInstanced ? "Instanced: ON" : "Instanced: OFF");

		// Setting model color
		Vec3 newColor = _fe3d.gameEntity_getColor(_currentModelID) * 255.0f;
		_gui.getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
		_gui.getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
		_gui.getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
		newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
		newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
		newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
		_fe3d.gameEntity_setColor(_currentModelID, newColor);

		// Setting model UV repeat
		float newUvRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelID);
		_gui.getGlobalScreen()->checkValueForm("uvRepeat", newUvRepeat, { });
		_fe3d.gameEntity_setUvRepeat(_currentModelID, newUvRepeat);

		// Setting LOD entityID
		string lodID = "";
		if (_gui.getGlobalScreen()->checkValueForm("lodID", lodID, { }))
		{
			// Check if LOD entity exists
			if (std::find(_modelNames.begin(), _modelNames.end(), "@" + lodID) == _modelNames.end())
			{
				_fe3d.logger_throwWarning("Cannot find LOD entity name: \"" + lodID + "\"");
			}
			else
			{
				_fe3d.gameEntity_setLevelOfDetailEntity(_currentModelID, "@" + lodID);
			}
		}
	}
}