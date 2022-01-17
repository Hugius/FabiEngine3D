#define TW(text) calculateTextWidth(text, CW)

#include "left_viewport_controller.hpp"

using LVPC = LeftViewportController;

void LeftViewportController::initialize()
{
	_gui->getLeftViewport()->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	auto window = _gui->getLeftViewport()->getWindow("main");

	auto positions = calculateButtonPositions(12, CH);
	window->createScreen("main");
	window->getScreen("main")->createButton("skyEditor", fvec2(0.0f, positions[0]), fvec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("terrainEditor", fvec2(0.0f, positions[1]), fvec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("waterEditor", fvec2(0.0f, positions[2]), fvec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("modelEditor", fvec2(0.0f, positions[3]), fvec2(TW("Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("billboardEditor", fvec2(0.0f, positions[4]), fvec2(TW("Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quad2dEditor", fvec2(0.0f, positions[5]), fvec2(TW("Quad2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quad2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("text2dEditor", fvec2(0.0f, positions[6]), fvec2(TW("Text2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Text2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation2dEditor", fvec2(0.0f, positions[7]), fvec2(TW("Animation2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation3dEditor", fvec2(0.0f, positions[8]), fvec2(TW("Animation3D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation3D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("soundEditor", fvec2(0.0f, positions[9]), fvec2(TW("Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("worldEditor", fvec2(0.0f, positions[10]), fvec2(TW("World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("scriptEditor", fvec2(0.0f, positions[11]), fvec2(TW("Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	window->setActiveScreen("main");
}

void LeftViewportController::update()
{
	auto window = _gui->getLeftViewport()->getWindow("main");
	auto screen = window->getActiveScreen();

	if(screen->getID() == "main")
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
		{
			if(_skyEditor->loadFromFile())
			{
				_skyEditor->load();
				window->setActiveScreen("skyEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("terrainEditor")->isHovered())
		{
			if(_terrainEditor->loadFromFile())
			{
				_terrainEditor->load();
				window->setActiveScreen("terrainEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waterEditor")->isHovered())
		{
			if(_waterEditor->loadFromFile())
			{
				_waterEditor->load();
				window->setActiveScreen("waterEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("modelEditor")->isHovered())
		{
			if(_modelEditor->loadFromFile())
			{
				_modelEditor->load();
				window->setActiveScreen("modelEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardEditor")->isHovered())
		{
			if(_billboardEditor->loadFromFile())
			{
				_billboardEditor->load();
				window->setActiveScreen("billboardEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quad2dEditor")->isHovered())
		{
			if(_quad2dEditor->loadFromFile())
			{
				_quad2dEditor->load();
				window->setActiveScreen("quad2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("text2dEditor")->isHovered())
		{
			if(_text2dEditor->loadFromFile())
			{
				_text2dEditor->load();
				window->setActiveScreen("text2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation2dEditor")->isHovered())
		{
			if(_animation2dEditor->loadFromFile(true))
			{
				_animation2dEditor->load();
				window->setActiveScreen("animation2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation3dEditor")->isHovered())
		{
			if(_modelEditor->loadFromFile() && _animation3dEditor->loadFromFile(true))
			{
				_animation3dEditor->load();
				window->setActiveScreen("animation3dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("soundEditor")->isHovered())
		{
			if(_soundEditor->loadFromFile())
			{
				_soundEditor->load();
				window->setActiveScreen("soundEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("worldEditor")->isHovered())
		{
			_worldEditor->load();
			window->setActiveScreen("worldEditorMenuMain");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("scriptEditor")->isHovered())
		{
			if(_scriptEditor->loadScriptFiles(true))
			{
				_scriptEditor->load();
				window->setActiveScreen("scriptEditorMenuMain");
			}
		}
	}

	_skyEditor->update();
	_terrainEditor->update();
	_waterEditor->update();
	_modelEditor->update();
	_billboardEditor->update();
	_quad2dEditor->update();
	_text2dEditor->update();
	_animation2dEditor->update();
	_animation3dEditor->update();
	_soundEditor->update();
	_worldEditor->update();
	_scriptEditor->update();
}

void LeftViewportController::inject(shared_ptr<SkyEditor> skyEditor)
{
	_skyEditor = skyEditor;
}

void LeftViewportController::inject(shared_ptr<TerrainEditor> terrainEditor)
{
	_terrainEditor = terrainEditor;
}

void LeftViewportController::inject(shared_ptr<WaterEditor> waterEditor)
{
	_waterEditor = waterEditor;
}

void LeftViewportController::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void LeftViewportController::inject(shared_ptr<BillboardEditor> billboardEditor)
{
	_billboardEditor = billboardEditor;
}

void LeftViewportController::inject(shared_ptr<Quad2dEditor> quad2dEditor)
{
	_quad2dEditor = quad2dEditor;
}

void LeftViewportController::inject(shared_ptr<Text2dEditor> text2dEditor)
{
	_text2dEditor = text2dEditor;
}

void LeftViewportController::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void LeftViewportController::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void LeftViewportController::inject(shared_ptr<SoundEditor> soundEditor)
{
	_soundEditor = soundEditor;
}

void LeftViewportController::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}

void LeftViewportController::inject(shared_ptr<ScriptEditor> scriptEditor)
{
	_scriptEditor = scriptEditor;
}