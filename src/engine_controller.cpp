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
	_scriptExecutor = make_shared<ScriptExecutor>();
	_scriptInterpreter = make_shared<ScriptInterpreter>();

	_leftViewportController->inject(_guiManager);
	_rightViewportController->inject(_guiManager);
	_topViewportController->inject(_guiManager);
	_bottomViewportController->inject(_guiManager);

	_topViewportController->inject(_leftViewportController->getSkyEditor());
	_topViewportController->inject(_leftViewportController->getTerrainEditor());
	_topViewportController->inject(_leftViewportController->getWaterEditor());
	_topViewportController->inject(_leftViewportController->getModelEditor());
	_topViewportController->inject(_leftViewportController->getBillboardEditor());
	_topViewportController->inject(_leftViewportController->getQuadEditor());
	_topViewportController->inject(_leftViewportController->getAnimation2dEditor());
	_topViewportController->inject(_leftViewportController->getAnimation3dEditor());
	_topViewportController->inject(_leftViewportController->getSoundEditor());
	_topViewportController->inject(_leftViewportController->getWorldEditor());
	_topViewportController->inject(_leftViewportController->getScriptEditor());
}

void EngineController::inject(shared_ptr<EngineInterface> fe3d)
{
	_guiManager->inject(fe3d);
	_leftViewportController->inject(fe3d);
	_rightViewportController->inject(fe3d);
	_topViewportController->inject(fe3d);
	_bottomViewportController->inject(fe3d);
	_scriptExecutor->inject(fe3d);
	_scriptInterpreter->inject(fe3d);

	_fe3d = fe3d;
}

void EngineController::initialize()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const string meshDirectoryPath = "engine\\assets\\mesh\\";
	const string diffuseMapDirectoryPath = "engine\\assets\\image\\diffuse_map\\";
	const string fontMapDirectoryPath = "engine\\assets\\image\\font_map\\";

	if(Config::getInst().isApplicationExported())
	{
		if(_topViewportController->isProjectCorrupted(rootPath))
		{
			Logger::throwFatalWarning("Cannot load application: missing files/directories!");
		}

		_fe3d->misc_setBackgroundColor(RENDER_COLOR);

		_leftViewportController->getScriptEditor()->loadScriptFiles(true);
		_scriptExecutor->load();

		if(!_scriptExecutor->isRunning())
		{
			_fe3d->application_stop();
			_mustPromptOnExit = true;
		}
	}
	else
	{
		vector<string> meshPaths;
		meshPaths.push_back(meshDirectoryPath + "camera.obj");
		meshPaths.push_back(meshDirectoryPath + "box.obj");
		meshPaths.push_back(meshDirectoryPath + "lamp.obj");
		meshPaths.push_back(meshDirectoryPath + "plane.obj");
		meshPaths.push_back(meshDirectoryPath + "speaker.obj");
		meshPaths.push_back(meshDirectoryPath + "torch.obj");
		_fe3d->misc_cacheMeshes(meshPaths);

		vector<string> imagePaths;
		imagePaths.push_back(diffuseMapDirectoryPath + "box.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "color.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_default.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_pointing.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "cursor_text.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "debug.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "grid.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "light_source.tga");
		imagePaths.push_back(diffuseMapDirectoryPath + "logo.tga");
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
		_fe3d->misc_cacheImages(imagePaths);

		_fe3d->misc_setBackgroundColor(RENDER_COLOR);

		_fe3d->quad_create("@@cursor", true);
		_fe3d->quad_setSize("@@cursor", fvec2(CURSOR_QUAD_SIZE, (CURSOR_QUAD_SIZE * Tools::getWindowAspectRatio())));
		_fe3d->quad_setDiffuseMap("@@cursor", diffuseMapDirectoryPath + "cursor_default.tga");
		_fe3d->misc_setCursorEntityID("@@cursor");
		_fe3d->misc_setCursorVisible(false);

		_rightViewportController->initialize();
		_bottomViewportController->initialize();
		_topViewportController->initialize();
		_leftViewportController->initialize();

		_fe3d->misc_enableVsync();
	}
}

void EngineController::update()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_scriptExecutor->isRunning())
		{
			_leftViewportController->getAnimation2dEditor()->update();
			_leftViewportController->getAnimation3dEditor()->update();

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
		string activeScreen = _guiManager->getViewport("left")->getWindow("main")->getActiveScreen()->getID();
		if(activeScreen == "main" && lastScreen != "main")
		{
			_fe3d->misc_setBackgroundColor(RENDER_COLOR);

			_fe3d->camera_reset();
		}
		lastScreen = activeScreen;

		_fe3d->quad_setPosition("@@cursor", Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPosition())));
		_fe3d->quad_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_default.tga");
		_fe3d->quad_setVisible("@@cursor", _fe3d->misc_isCursorInsideWindow());

		_guiManager->update();

		_topViewportController->update();
		_leftViewportController->update();
		_rightViewportController->update();
		_bottomViewportController->update();
	}
}

void EngineController::terminate()
{
	if(Config::getInst().isApplicationExported())
	{
		if(_scriptExecutor->isRunning())
		{
			_scriptExecutor->unload();
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