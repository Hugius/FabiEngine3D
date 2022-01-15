#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

void ModelEditor::_updateTexturingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuTexturing")
	{
		auto textureRepeat = _fe3d->model_getTextureRepeat(_currentModelID, _currentPartID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			for(const auto& partID : _fe3d->model_getPartIDs(_currentModelID))
			{
				_fe3d->model_setTransparency(_currentModelID, partID, 1.0f);
			}

			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("partID")->getEntityID(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\model\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->model_setDiffuseMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\model\\emission_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->model_setEmissionMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("specularMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\model\\specular_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->model_setSpecularMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("reflectionMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\model\\reflection_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->model_setReflectionMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("normalMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("ModelEditor::_updateTexturingMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\model\\normal_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->model_setNormalMap(_currentModelID, _currentPartID, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clearMaps")->isHovered())
		{
			_fe3d->model_setDiffuseMap(_currentModelID, _currentPartID, "");
			_fe3d->model_setEmissionMap(_currentModelID, _currentPartID, "");
			_fe3d->model_setSpecularMap(_currentModelID, _currentPartID, "");
			_fe3d->model_setReflectionMap(_currentModelID, _currentPartID, "");
			_fe3d->model_setNormalMap(_currentModelID, _currentPartID, "");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->createValueForm("textureRepeat", "Texture Repeat", textureRepeat, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("textureRepeat", textureRepeat, {}))
		{
			_fe3d->model_setTextureRepeat(_currentModelID, _currentPartID, textureRepeat);
		}
	}
}