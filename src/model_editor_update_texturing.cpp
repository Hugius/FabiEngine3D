#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void ModelEditor::_updateTexturingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuTexturing")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || !_currentPartId.empty());
		const auto hasDiffuseMap = (isPartSelected ? _fe3d->model_hasDiffuseMap(_currentModelId, _currentPartId) : false);
		const auto hasEmissionMap = (isPartSelected ? _fe3d->model_hasEmissionMap(_currentModelId, _currentPartId) : false);
		const auto hasSpecularMap = (isPartSelected ? _fe3d->model_hasSpecularMap(_currentModelId, _currentPartId) : false);
		const auto hasReflectionMap = (isPartSelected ? _fe3d->model_hasReflectionMap(_currentModelId, _currentPartId) : false);
		const auto hasRefractionMap = (isPartSelected ? _fe3d->model_hasRefractionMap(_currentModelId, _currentPartId) : false);
		const auto hasNormalMap = (isPartSelected ? _fe3d->model_hasNormalMap(_currentModelId, _currentPartId) : false);
		const auto textureRepeat = (isPartSelected ? _fe3d->model_getTextureRepeat(_currentModelId, _currentPartId) : 0);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setDiffuseMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\emission_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setEmissionMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("specularMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\specular_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setSpecularMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("reflectionMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\reflection_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setReflectionMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("refractionMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\refraction_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setRefractionMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\model\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->model_setNormalMap(_currentModelId, _currentPartId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d->model_setDiffuseMap(_currentModelId, _currentPartId, "");
			_fe3d->model_setEmissionMap(_currentModelId, _currentPartId, "");
			_fe3d->model_setSpecularMap(_currentModelId, _currentPartId, "");
			_fe3d->model_setReflectionMap(_currentModelId, _currentPartId, "");
			_fe3d->model_setRefractionMap(_currentModelId, _currentPartId, "");
			_fe3d->model_setNormalMap(_currentModelId, _currentPartId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->model_setTextureRepeat(_currentModelId, _currentPartId, value);
		}

		screen->getButton("diffuseMap")->setHoverable(isPartSelected);
		screen->getButton("emissionMap")->setHoverable(isPartSelected);
		screen->getButton("specularMap")->setHoverable(isPartSelected);
		screen->getButton("reflectionMap")->setHoverable(isPartSelected);
		screen->getButton("refractionMap")->setHoverable(isPartSelected);
		screen->getButton("normalMap")->setHoverable(isPartSelected);
		screen->getButton("clearMaps")->setHoverable(isPartSelected);
		screen->getButton("textureRepeat")->setHoverable(isPartSelected);
	}
}