#include "aabb_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void AabbEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "aabbEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAabb", "Create AABB", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto aabbIds = _loadedAabbIds;

			for(auto & aabbId : aabbIds)
			{
				aabbId = aabbId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editAabb", "Edit AABB", fvec2(-0.5f, 0.1f), aabbIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto aabbIds = _loadedAabbIds;

			for(auto & aabbId : aabbIds)
			{
				aabbId = aabbId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteAabb", "Delete AABB", fvec2(-0.5f, 0.1f), aabbIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				saveAabbsToFile();
				unload();
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				unload();
			}
		}
	}
}

void AabbEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "aabbEditorMenuChoice")
	{
		const auto size = _fe3d->aabb_getBaseSize(_currentAabbId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible(_currentAabbId, false);
			_gui->getOverlay()->getTextField("aabbId")->setVisible(false);
			_currentAabbId = "";
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("aabbEditorMenuMain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setBaseSize(_currentAabbId, fvec3((content / 100.0f), size.y, size.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setBaseSize(_currentAabbId, fvec3(size.x, (content / 100.0f), size.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setBaseSize(_currentAabbId, fvec3(size.x, size.y, (content / 100.0f)));
		}
	}
}