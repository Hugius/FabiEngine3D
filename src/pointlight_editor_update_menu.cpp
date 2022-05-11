#include "pointlight_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void PointlightEditor::_updateMainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "pointlightEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createPointlight", "Create Pointlight", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto pointlightIds = _loadedPointlightIds;

			for(auto & pointlightId : pointlightIds)
			{
				pointlightId = pointlightId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editPointlight", "Edit Pointlight", fvec2(-0.5f, 0.1f), pointlightIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto pointlightIds = _loadedPointlightIds;

			for(auto & pointlightId : pointlightIds)
			{
				pointlightId = pointlightId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deletePointlight", "Delete Pointlight", fvec2(-0.5f, 0.1f), pointlightIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				savePointlightsToFile();
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

void PointlightEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "pointlightEditorMenuChoice")
	{
		const auto radius = _fe3d->pointlight_getRadius(_currentPointlightId);
		const auto color = _fe3d->pointlight_getColor(_currentPointlightId);
		const auto intensity = _fe3d->pointlight_getIntensity(_currentPointlightId);
		const auto shape = _fe3d->pointlight_getShape(_currentPointlightId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->pointlight_setVisible(_currentPointlightId, false);
			_fe3d->model_setVisible("@@pointlight", false);
			_gui->getOverlay()->getTextField("pointlightId")->setVisible(false);

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("pointlightEditorMenuMain");

			_currentPointlightId = "";

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
				case PointlightShapeType::CIRCLE:
				{
					_fe3d->pointlight_setShape(_currentPointlightId, PointlightShapeType::SQUARE);

					break;
				}
				case PointlightShapeType::SQUARE:
				{
					_fe3d->pointlight_setShape(_currentPointlightId, PointlightShapeType::CIRCLE);

					break;
				}
			}
		}

		if((_gui->getOverlay()->getValueFormId() == "radiusX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setRadius(_currentPointlightId, fvec3((value / RADIUS_MULTIPLIER), radius.y, radius.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "radiusY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setRadius(_currentPointlightId, fvec3(radius.x, (value / RADIUS_MULTIPLIER), radius.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "radiusZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setRadius(_currentPointlightId, fvec3(radius.x, radius.y, (value / RADIUS_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setColor(_currentPointlightId, fvec3((value / COLOR_MULTIPLIER), color.g, color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setColor(_currentPointlightId, fvec3(color.r, (value / COLOR_MULTIPLIER), color.b));
		}
		if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setColor(_currentPointlightId, fvec3(color.r, color.g, (value / COLOR_MULTIPLIER)));
		}
		if((_gui->getOverlay()->getValueFormId() == "intensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->pointlight_setIntensity(_currentPointlightId, (value / INTENSITY_MULTIPLIER));
		}

		switch(shape)
		{
			case PointlightShapeType::CIRCLE:
			{
				screen->getButton("shape")->setTextContent("Shape: CIRCLE");

				break;
			}
			case PointlightShapeType::SQUARE:
			{
				screen->getButton("shape")->setTextContent("Shape: SQUARE");

				break;
			}
		}
	}
}