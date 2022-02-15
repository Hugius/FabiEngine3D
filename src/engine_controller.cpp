#include "engine_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
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
	_text3dEditor = make_shared<Text3dEditor>();
	_quad2dEditor = make_shared<Quad2dEditor>();
	_text2dEditor = make_shared<Text2dEditor>();
	_animation2dEditor = make_shared<Animation2dEditor>();
	_animation3dEditor = make_shared<Animation3dEditor>();
	_soundEditor = make_shared<SoundEditor>();
	_worldEditor = make_shared<WorldEditor>();
	_scriptEditor = make_shared<ScriptEditor>();
	_customWorldManager = make_shared<CustomWorldBuilder>();
	_worldUtilities = make_shared<WorldUtilities>();
	_script = make_shared<Script>();
	_scriptExecutor = make_shared<ScriptExecutor>();
	_scriptInterpreter = make_shared<ScriptInterpreter>();

	_leftViewportController->inject(_guiManager);
	_leftViewportController->inject(_skyEditor);
	_leftViewportController->inject(_terrainEditor);
	_leftViewportController->inject(_waterEditor);
	_leftViewportController->inject(_modelEditor);
	_leftViewportController->inject(_quad3dEditor);
	_leftViewportController->inject(_text3dEditor);
	_leftViewportController->inject(_quad2dEditor);
	_leftViewportController->inject(_text2dEditor);
	_leftViewportController->inject(_animation2dEditor);
	_leftViewportController->inject(_animation3dEditor);
	_leftViewportController->inject(_soundEditor);
	_leftViewportController->inject(_worldEditor);
	_leftViewportController->inject(_scriptEditor);
	_rightViewportController->inject(_guiManager);
	_bottomViewportController->inject(_guiManager);
	_bottomViewportController->inject(_scriptEditor);
	_bottomViewportController->inject(_scriptExecutor);
	_topViewportController->inject(_guiManager);
	_topViewportController->inject(_skyEditor);
	_topViewportController->inject(_terrainEditor);
	_topViewportController->inject(_waterEditor);
	_topViewportController->inject(_modelEditor);
	_topViewportController->inject(_quad3dEditor);
	_topViewportController->inject(_text3dEditor);
	_topViewportController->inject(_quad2dEditor);
	_topViewportController->inject(_text2dEditor);
	_topViewportController->inject(_animation2dEditor);
	_topViewportController->inject(_animation3dEditor);
	_topViewportController->inject(_soundEditor);
	_topViewportController->inject(_worldEditor);
	_topViewportController->inject(_scriptEditor);
	_topViewportController->inject(_script);
	_topViewportController->inject(_scriptExecutor);
	_skyEditor->inject(_guiManager);
	_terrainEditor->inject(_guiManager);
	_waterEditor->inject(_guiManager);
	_modelEditor->inject(_guiManager);
	_quad3dEditor->inject(_guiManager);
	_text3dEditor->inject(_guiManager);
	_quad2dEditor->inject(_guiManager);
	_text2dEditor->inject(_guiManager);
	_animation2dEditor->inject(_guiManager);
	_animation3dEditor->inject(_guiManager);
	_animation3dEditor->inject(_modelEditor);
	_soundEditor->inject(_guiManager);
	_worldEditor->inject(_guiManager);
	_worldEditor->inject(_skyEditor);
	_worldEditor->inject(_terrainEditor);
	_worldEditor->inject(_waterEditor);
	_worldEditor->inject(_modelEditor);
	_worldEditor->inject(_quad3dEditor);
	_worldEditor->inject(_text3dEditor);
	_worldEditor->inject(_animation2dEditor);
	_worldEditor->inject(_animation3dEditor);
	_worldEditor->inject(_soundEditor);
	_worldEditor->inject(_worldUtilities);
	_scriptEditor->inject(_guiManager);
	_scriptEditor->inject(_script);
	_scriptExecutor->inject(_scriptInterpreter);
	_scriptInterpreter->inject(_skyEditor);
	_scriptInterpreter->inject(_terrainEditor);
	_scriptInterpreter->inject(_waterEditor);
	_scriptInterpreter->inject(_modelEditor);
	_scriptInterpreter->inject(_quad3dEditor);
	_scriptInterpreter->inject(_text3dEditor);
	_scriptInterpreter->inject(_quad2dEditor);
	_scriptInterpreter->inject(_text2dEditor);
	_scriptInterpreter->inject(_animation2dEditor);
	_scriptInterpreter->inject(_animation3dEditor);
	_scriptInterpreter->inject(_soundEditor);
	_scriptInterpreter->inject(_worldEditor);
	_scriptInterpreter->inject(_customWorldManager);
	_scriptInterpreter->inject(_worldUtilities);
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
	_text3dEditor->inject(_fe3d);
	_quad2dEditor->inject(_fe3d);
	_text2dEditor->inject(_fe3d);
	_animation2dEditor->inject(_fe3d);
	_animation3dEditor->inject(_fe3d);
	_soundEditor->inject(_fe3d);
	_worldEditor->inject(_fe3d);
	_scriptEditor->inject(_fe3d);
	_customWorldManager->inject(_fe3d);
	_worldUtilities->inject(_fe3d);
	_scriptExecutor->inject(_fe3d);
	_scriptInterpreter->inject(_fe3d);
}

void EngineController::initialize()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto meshDirectoryPath = string("engine\\assets\\mesh\\");
	const auto diffuseMapDirectoryPath = string("engine\\assets\\image\\diffuse_map\\");
	const auto fontMapDirectoryPath = string("engine\\assets\\image\\font_map\\");

	if(Config::getInst().isApplicationExported())
	{
		if(_topViewportController->isProjectCorrupted(rootPath))
		{
			_fe3d->application_stop();
			return;
		}

		_scriptEditor->loadScriptFiles(true);

		_scriptExecutor->start();

		if(!_scriptExecutor->isRunning())
		{
			_fe3d->application_stop();
			_mustPromptOnExit = true;
		}
	}
	else
	{
		vector<string> meshPaths;
		meshPaths.push_back(meshDirectoryPath + "box.obj");
		meshPaths.push_back(meshDirectoryPath + "camera.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		meshPaths.push_back(meshDirectoryPath + "torch.obj");
		_fe3d->misc_cacheMeshes(meshPaths, true);

		vector<string> imagePaths;
		imagePaths.push_back(diffuseMapDirectoryPath + "box.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "color.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_default.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_pointing.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_text.tga");
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
		imagePaths.push_back(diffuseMapDirectoryPath + "shape_circle.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "shape_square.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "size.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "start.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "stop.tga");
		imagePaths.push_back(fontMapDirectoryPath + "font.tga");
		_fe3d->misc_cacheImages(imagePaths, true);

		_fe3d->quad2d_create("@@cursor", true);
		_fe3d->quad2d_setSize("@@cursor", fvec2(CURSOR_SIZE.x, (CURSOR_SIZE.y * Tools::getWindowAspectRatio())));
		_fe3d->quad2d_setDiffuseMap("@@cursor", diffuseMapDirectoryPath + "cursor_default.tga");
		_fe3d->misc_setCursorEntityId("@@cursor");
		_fe3d->misc_setCursorVisible(false);

		_guiManager->initialize();
		_leftViewportController->initialize();
		_rightViewportController->initialize();
		_bottomViewportController->initialize();
		_topViewportController->initialize();

		_fe3d->misc_setVsyncEnabled(true);
	}
}

void EngineController::update()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_scriptExecutor->isRunning())
		{
			_animation2dEditor->update();
			_animation3dEditor->update();

			_scriptExecutor->update(false);
		}
		else
		{
			_fe3d->application_stop();
			_mustPromptOnExit = true;
		}
	}
	else
	{
		static string lastScreen = "";
		string activeScreen = _guiManager->getLeftViewport()->getWindow("main")->getActiveScreen()->getId();
		if(activeScreen == "main" && lastScreen != "main")
		{
			_fe3d->camera_reset();
		}
		lastScreen = activeScreen;

		_fe3d->quad2d_setPosition("@@cursor", Tools::convertToNdc(_fe3d->misc_getCursorPosition()));
		_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_default.tga");
		_fe3d->quad2d_setVisible("@@cursor", _fe3d->misc_isCursorInsideWindow());

		_guiManager->update();

		_leftViewportController->update();
		_rightViewportController->update();
		_bottomViewportController->update();
		_topViewportController->update();
	}
}

void EngineController::terminate()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_scriptExecutor->isRunning())
		{
			_scriptExecutor->stop();
		}
	}
	else
	{

	}

	if(_mustPromptOnExit)
	{
		cout << endl;
		cout << "Press a key to continue...";
		auto temp = _getch();
	}
}