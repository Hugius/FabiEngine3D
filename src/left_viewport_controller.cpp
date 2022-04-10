#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "left_viewport_controller.hpp"
#include "tools.hpp"

void LeftViewportController::initialize()
{
	_gui->getLeftViewport()->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), FRAME_COLOR);
	auto window = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(13, CH, false);
	window->createScreen("main");
	window->getScreen("main")->createButton("skyEditor", fvec2(0.0f, positions[0]), TEXT_SIZE("Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("terrainEditor", fvec2(0.0f, positions[1]), TEXT_SIZE("Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("waterEditor", fvec2(0.0f, positions[2]), TEXT_SIZE("Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("modelEditor", fvec2(0.0f, positions[3]), TEXT_SIZE("Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quad3dEditor", fvec2(0.0f, positions[4]), TEXT_SIZE("Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("text3dEditor", fvec2(0.0f, positions[5]), TEXT_SIZE("Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quad2dEditor", fvec2(0.0f, positions[6]), TEXT_SIZE("Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("text2dEditor", fvec2(0.0f, positions[7]), TEXT_SIZE("Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation2dEditor", fvec2(0.0f, positions[8]), TEXT_SIZE("Animation2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation3dEditor", fvec2(0.0f, positions[9]), TEXT_SIZE("Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("soundEditor", fvec2(0.0f, positions[10]), TEXT_SIZE("Sound"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("worldEditor", fvec2(0.0f, positions[11]), TEXT_SIZE("World"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("scriptEditor", fvec2(0.0f, positions[12]), TEXT_SIZE("Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	window->setActiveScreen("main");
}

void LeftViewportController::update()
{
	auto window = _gui->getLeftViewport()->getWindow("main");
	auto screen = window->getActiveScreen();

	if(screen->getId() == "main")
	{
		if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
		{
			if(_skyEditor->loadEntitiesFromFile())
			{
				_skyEditor->load();
				window->setActiveScreen("skyEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("terrainEditor")->isHovered())
		{
			if(_terrainEditor->loadEntitiesFromFile())
			{
				_terrainEditor->load();
				window->setActiveScreen("terrainEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("waterEditor")->isHovered())
		{
			if(_waterEditor->loadEntitiesFromFile())
			{
				_waterEditor->load();
				window->setActiveScreen("waterEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("modelEditor")->isHovered())
		{
			if(_modelEditor->loadEntitiesFromFile())
			{
				_modelEditor->load();
				window->setActiveScreen("modelEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("quad3dEditor")->isHovered())
		{
			if(_quad3dEditor->loadEntitiesFromFile())
			{
				_quad3dEditor->load();
				window->setActiveScreen("quad3dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("text3dEditor")->isHovered())
		{
			if(_text3dEditor->loadEntitiesFromFile())
			{
				_text3dEditor->load();
				window->setActiveScreen("text3dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("quad2dEditor")->isHovered())
		{
			if(_quad2dEditor->loadEntitiesFromFile())
			{
				_quad2dEditor->load();
				window->setActiveScreen("quad2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("text2dEditor")->isHovered())
		{
			if(_text2dEditor->loadEntitiesFromFile())
			{
				_text2dEditor->load();
				window->setActiveScreen("text2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("animation2dEditor")->isHovered())
		{
			if(_animation2dEditor->loadAnimationsFromFile())
			{
				_animation2dEditor->load();
				window->setActiveScreen("animation2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("animation3dEditor")->isHovered())
		{
			if(_modelEditor->loadEntitiesFromFile() && _animation3dEditor->loadAnimationsFromFile())
			{
				_animation3dEditor->load();
				window->setActiveScreen("animation3dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("soundEditor")->isHovered())
		{
			if(_soundEditor->loadSoundsFromFile())
			{
				_soundEditor->load();
				window->setActiveScreen("soundEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("worldEditor")->isHovered())
		{
			_worldEditor->load();
			window->setActiveScreen("worldEditorMenuMain");
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("scriptEditor")->isHovered())
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
	_quad3dEditor->update();
	_text3dEditor->update();
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

void LeftViewportController::inject(shared_ptr<Quad3dEditor> quad3dEditor)
{
	_quad3dEditor = quad3dEditor;
}

void LeftViewportController::inject(shared_ptr<Text3dEditor> text3dEditor)
{
	_text3dEditor = text3dEditor;
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