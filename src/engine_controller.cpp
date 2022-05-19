#include "engine_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

EngineController::EngineController()
{
	_guiManager = make_shared<GuiManager>();
	_leftViewportController = make_shared<LeftViewportController>();
	_rightViewportController = make_shared<RightViewportController>();
	_topViewportController = make_shared<TopViewportController>();
	_bottomViewportController = make_shared<BottomViewportController>();
	_skyEditor = make_shared<SkyEditor>();
	_terrainEditor = make_shared<TerrainEditor>();
	_waterEditor = make_shared<WaterEditor>();
	_modelEditor = make_shared<ModelEditor>();
	_quad3dEditor = make_shared<Quad3dEditor>();
	_quad2dEditor = make_shared<Quad2dEditor>();
	_text3dEditor = make_shared<Text3dEditor>();
	_text2dEditor = make_shared<Text2dEditor>();
	_animation3dEditor = make_shared<Animation3dEditor>();
	_animation2dEditor = make_shared<Animation2dEditor>();
	_aabbEditor = make_shared<AabbEditor>();
	_pointlightEditor = make_shared<PointlightEditor>();
	_spotlightEditor = make_shared<SpotlightEditor>();
	_sound3dEditor = make_shared<Sound3dEditor>();
	_sound2dEditor = make_shared<Sound2dEditor>();
	_worldEditor = make_shared<WorldEditor>();
	_scriptEditor = make_shared<ScriptEditor>();
	_customWorldBuilder = make_shared<CustomWorldBuilder>();
	_duplicator = make_shared<Duplicator>();
	_script = make_shared<Script>();
	_scriptExecutor = make_shared<ScriptExecutor>();
	_scriptInterpreter = make_shared<ScriptInterpreter>();

	_leftViewportController->inject(_guiManager);
	_leftViewportController->inject(_skyEditor);
	_leftViewportController->inject(_terrainEditor);
	_leftViewportController->inject(_waterEditor);
	_leftViewportController->inject(_modelEditor);
	_leftViewportController->inject(_quad3dEditor);
	_leftViewportController->inject(_quad2dEditor);
	_leftViewportController->inject(_text3dEditor);
	_leftViewportController->inject(_text2dEditor);
	_rightViewportController->inject(_guiManager);
	_rightViewportController->inject(_animation3dEditor);
	_rightViewportController->inject(_animation2dEditor);
	_rightViewportController->inject(_aabbEditor);
	_rightViewportController->inject(_pointlightEditor);
	_rightViewportController->inject(_spotlightEditor);
	_rightViewportController->inject(_sound3dEditor);
	_rightViewportController->inject(_sound2dEditor);
	_rightViewportController->inject(_worldEditor);
	_rightViewportController->inject(_scriptEditor);
	_rightViewportController->inject(_modelEditor);
	_bottomViewportController->inject(_guiManager);
	_bottomViewportController->inject(_scriptEditor);
	_bottomViewportController->inject(_scriptExecutor);
	_topViewportController->inject(_guiManager);
	_topViewportController->inject(_skyEditor);
	_topViewportController->inject(_terrainEditor);
	_topViewportController->inject(_waterEditor);
	_topViewportController->inject(_modelEditor);
	_topViewportController->inject(_quad3dEditor);
	_topViewportController->inject(_quad2dEditor);
	_topViewportController->inject(_text3dEditor);
	_topViewportController->inject(_text2dEditor);
	_topViewportController->inject(_animation3dEditor);
	_topViewportController->inject(_animation2dEditor);
	_topViewportController->inject(_aabbEditor);
	_topViewportController->inject(_pointlightEditor);
	_topViewportController->inject(_spotlightEditor);
	_topViewportController->inject(_sound3dEditor);
	_topViewportController->inject(_sound2dEditor);
	_topViewportController->inject(_worldEditor);
	_topViewportController->inject(_scriptEditor);
	_topViewportController->inject(_customWorldBuilder);
	_topViewportController->inject(_script);
	_topViewportController->inject(_scriptExecutor);
	_skyEditor->inject(_guiManager);
	_terrainEditor->inject(_guiManager);
	_waterEditor->inject(_guiManager);
	_waterEditor->inject(_skyEditor);
	_modelEditor->inject(_guiManager);
	_modelEditor->inject(_skyEditor);
	_quad3dEditor->inject(_guiManager);
	_quad2dEditor->inject(_guiManager);
	_text3dEditor->inject(_guiManager);
	_text2dEditor->inject(_guiManager);
	_animation3dEditor->inject(_guiManager);
	_animation3dEditor->inject(_modelEditor);
	_animation2dEditor->inject(_guiManager);
	_aabbEditor->inject(_guiManager);
	_pointlightEditor->inject(_guiManager);
	_spotlightEditor->inject(_guiManager);
	_sound3dEditor->inject(_guiManager);
	_sound2dEditor->inject(_guiManager);
	_worldEditor->inject(_guiManager);
	_worldEditor->inject(_skyEditor);
	_worldEditor->inject(_terrainEditor);
	_worldEditor->inject(_waterEditor);
	_worldEditor->inject(_modelEditor);
	_worldEditor->inject(_quad3dEditor);
	_worldEditor->inject(_text3dEditor);
	_worldEditor->inject(_animation3dEditor);
	_worldEditor->inject(_animation2dEditor);
	_worldEditor->inject(_aabbEditor);
	_worldEditor->inject(_pointlightEditor);
	_worldEditor->inject(_spotlightEditor);
	_worldEditor->inject(_sound3dEditor);
	_worldEditor->inject(_duplicator);
	_scriptEditor->inject(_guiManager);
	_scriptEditor->inject(_script);
	_scriptExecutor->inject(_scriptInterpreter);
	_scriptInterpreter->inject(_skyEditor);
	_scriptInterpreter->inject(_terrainEditor);
	_scriptInterpreter->inject(_waterEditor);
	_scriptInterpreter->inject(_modelEditor);
	_scriptInterpreter->inject(_quad3dEditor);
	_scriptInterpreter->inject(_quad2dEditor);
	_scriptInterpreter->inject(_text3dEditor);
	_scriptInterpreter->inject(_text2dEditor);
	_scriptInterpreter->inject(_animation3dEditor);
	_scriptInterpreter->inject(_animation2dEditor);
	_scriptInterpreter->inject(_aabbEditor);
	_scriptInterpreter->inject(_pointlightEditor);
	_scriptInterpreter->inject(_spotlightEditor);
	_scriptInterpreter->inject(_sound3dEditor);
	_scriptInterpreter->inject(_sound2dEditor);
	_scriptInterpreter->inject(_worldEditor);
	_scriptInterpreter->inject(_customWorldBuilder);
	_scriptInterpreter->inject(_duplicator);
	_scriptInterpreter->inject(_script);
}

void EngineController::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;

	_guiManager->inject(_fe3d);
	_leftViewportController->inject(_fe3d);
	_rightViewportController->inject(_fe3d);
	_bottomViewportController->inject(_fe3d);
	_topViewportController->inject(_fe3d);
	_skyEditor->inject(_fe3d);
	_terrainEditor->inject(_fe3d);
	_waterEditor->inject(_fe3d);
	_modelEditor->inject(_fe3d);
	_quad3dEditor->inject(_fe3d);
	_quad2dEditor->inject(_fe3d);
	_text3dEditor->inject(_fe3d);
	_text2dEditor->inject(_fe3d);
	_animation3dEditor->inject(_fe3d);
	_animation2dEditor->inject(_fe3d);
	_aabbEditor->inject(_fe3d);
	_pointlightEditor->inject(_fe3d);
	_spotlightEditor->inject(_fe3d);
	_sound3dEditor->inject(_fe3d);
	_sound2dEditor->inject(_fe3d);
	_worldEditor->inject(_fe3d);
	_scriptEditor->inject(_fe3d);
	_customWorldBuilder->inject(_fe3d);
	_customWorldBuilder->inject(_duplicator);
	_duplicator->inject(_fe3d);
	_scriptExecutor->inject(_fe3d);
	_scriptInterpreter->inject(_fe3d);
}

void EngineController::initialize()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto meshDirectoryPath = string("engine\\assets\\mesh\\");
	const auto diffuseMapDirectoryPath = string("engine\\assets\\image\\diffuse_map\\");
	const auto fontMapDirectoryPath = string("engine\\assets\\image\\font_map\\");

	if(Configuration::getInst().isApplicationExported())
	{
		if(_topViewportController->isProjectCorrupted(rootPath))
		{
			_fe3d->application_stop();

			return;
		}

		const auto skyImagePaths = _skyEditor->getImagePathsFromFile();
		const auto terrainImagePaths = _terrainEditor->getImagePathsFromFile();
		const auto waterImagePaths = _waterEditor->getImagePathsFromFile();
		const auto modelMeshPaths = _modelEditor->getMeshPathsFromFile();
		const auto modelImagePaths = _modelEditor->getImagePathsFromFile();
		const auto quad3dImagePaths = _quad3dEditor->getImagePathsFromFile();
		const auto quad2dImagePaths = _quad2dEditor->getImagePathsFromFile();
		const auto text3dImagePaths = _text3dEditor->getImagePathsFromFile();
		const auto text2dImagePaths = _text2dEditor->getImagePathsFromFile();
		const auto sound3dAudioPaths = _sound3dEditor->getAudioPathsFromFile();
		const auto sound2dAudioPaths = _sound2dEditor->getAudioPathsFromFile();

		vector<string> imagePaths = {};

		imagePaths.insert(imagePaths.end(), skyImagePaths.begin(), skyImagePaths.end());
		imagePaths.insert(imagePaths.end(), terrainImagePaths.begin(), terrainImagePaths.end());
		imagePaths.insert(imagePaths.end(), waterImagePaths.begin(), waterImagePaths.end());
		imagePaths.insert(imagePaths.end(), modelImagePaths.begin(), modelImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad3dImagePaths.begin(), quad3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), quad2dImagePaths.begin(), quad2dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text3dImagePaths.begin(), text3dImagePaths.end());
		imagePaths.insert(imagePaths.end(), text2dImagePaths.begin(), text2dImagePaths.end());

		vector<string> audioPaths = {};

		audioPaths.insert(audioPaths.end(), sound3dAudioPaths.begin(), sound3dAudioPaths.end());
		audioPaths.insert(audioPaths.end(), sound2dAudioPaths.begin(), sound2dAudioPaths.end());

		_fe3d->misc_cacheMeshes(modelMeshPaths, false);
		_fe3d->misc_cacheImages(imagePaths, false);
		_fe3d->misc_cacheAudios(audioPaths, false);

		_scriptEditor->loadScriptFiles(true);

		_scriptExecutor->start();

		if(!_scriptExecutor->isRunning())
		{
			_fe3d->application_stop();
		}
	}
	else
	{
		vector<string> meshPaths = {};
		meshPaths.push_back(meshDirectoryPath + "box.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "lens.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		meshPaths.push_back(meshDirectoryPath + "torch.obj");

		vector<string> imagePaths = {};
		imagePaths.push_back(diffuseMapDirectoryPath + "box.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "color.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_caret.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_default.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_pointing.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "debug.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "grid.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "light_source.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "minus.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "pause.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "plus.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "position.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "radius.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "restart.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "rotation.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "settings.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "size.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "start.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "stop.tga");
		imagePaths.push_back(fontMapDirectoryPath + "font.tga");

		_fe3d->misc_cacheMeshes(meshPaths, true);
		_fe3d->misc_cacheImages(imagePaths, true);

		Tools::setCursorVisible(false);

		_fe3d->quad2d_create(CURSOR_ID, true);
		_fe3d->quad2d_setSize(CURSOR_ID, fvec2(CURSOR_SIZE.x, (CURSOR_SIZE.y * Tools::getWindowAspectRatio())));

		_fe3d->misc_setCursorId(CURSOR_ID);

		_guiManager->initialize();
		_leftViewportController->initialize();
		_rightViewportController->initialize();
		_bottomViewportController->initialize();
		_topViewportController->initialize();
	}
}

void EngineController::update()
{
	if(Configuration::getInst().isApplicationExported())
	{
		if(_scriptExecutor->isRunning())
		{
			_scriptExecutor->update(false);
		}
		else
		{
			_fe3d->application_stop();
		}
	}
	else
	{
		_fe3d->quad2d_setPosition(_fe3d->misc_getCursorId(), Tools::convertToNdc(Tools::getCursorPosition()));
		_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), Tools::isCursorInsideWindow());

		_guiManager->updateOverlay();

		_leftViewportController->update();
		_rightViewportController->update();
		_bottomViewportController->update();
		_topViewportController->update();

		_guiManager->updateViewports();
	}
}

void EngineController::terminate()
{
	if(_scriptExecutor->isRunning())
	{
		_scriptExecutor->stop();
	}
}