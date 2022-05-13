#include "sound3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void Sound3dEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound3dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createSound3d", "Create Sound3d", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto sound3dIds = _loadedSound3dIds;

			for(auto & sound3dId : sound3dIds)
			{
				sound3dId = sound3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editSound3d", "Edit Sound3d", fvec2(-0.5f, 0.1f), sound3dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto sound3dIds = _loadedSound3dIds;

			for(auto & sound3dId : sound3dIds)
			{
				sound3dId = sound3dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteSound3d", "Delete Sound3d", fvec2(-0.5f, 0.1f), sound3dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveSound3dsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Sound3dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "sound3dEditorMenuChoice")
	{
		const auto radius = _fe3d->sound3d_getRadius(_currentSound3dId);
		const auto color = _fe3d->sound3d_getColor(_currentSound3dId);
		const auto intensity = _fe3d->sound3d_getIntensity(_currentSound3dId);
		const auto shape = _fe3d->sound3d_getShape(_currentSound3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->sound3d_setVisible(_currentSound3dId, false);
			_fe3d->model_setVisible("@@sound3d", false);
			_gui->getOverlay()->getTextField("sound3dId")->setVisible(false);

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("sound3dEditorMenuMain");

			_currentSound3dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("radius")->isHovered())
		{
			_gui->getOverlay()->openValueForm("radiusX", "X", (radius.x * RADIUS_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("radiusY", "Y", (radius.y * RADIUS_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("radiusZ", "Z", (radius.z * RADIUS_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "R", (color.r * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "G", (color.g * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "B", (color.b * COLOR_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("intensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("intensity", "X", (intensity * INTENSITY_MULTIPLIER), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("shape")->isHovered())
		{
			switch(shape)
			{
				case Sound3dShapeType::CIRCLE:
				{
					_fe3d->sound3d_setShape(_currentSound3dId, Sound3dShapeType::SQUARE);

					break;
				}
				case Sound3dShapeType::SQUARE:
				{
					_fe3d->sound3d_setShape(_currentSound3dId, Sound3dShapeType::CIRCLE);

					break;
				}
			}
		}

		if((_gui->getOverlay()->getValueFormId() == "radiusX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setRadius(_currentSound3dId, fvec3((value / RADIUS_MULTIPLIER), radius.y, radius.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "radiusY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setRadius(_currentSound3dId, fvec3(radius.x, (value / RADIUS_MULTIPLIER), radius.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "radiusZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setRadius(_currentSound3dId, fvec3(radius.x, radius.y, (value / RADIUS_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setColor(_currentSound3dId, fvec3((value / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setColor(_currentSound3dId, fvec3(color.r, (value / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setColor(_currentSound3dId, fvec3(color.r, color.g, (value / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->sound3d_setIntensity(_currentSound3dId, (value / INTENSITY_MULTIPLIER));
		}

		switch(shape)
		{
			case Sound3dShapeType::CIRCLE:
			{
				screen->getButton("shape")->setTextContent("Shape: CIRCLE");

				break;
			}
			case Sound3dShapeType::SQUARE:
			{
				screen->getButton("shape")->setTextContent("Shape: SQUARE");

				break;
			}
		}
	}
}