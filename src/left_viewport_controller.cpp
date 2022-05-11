#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "left_viewport_controller.hpp"

void LeftViewportController::initialize()
{
	_gui->getLeftViewport()->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), FRAME_COLOR);

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto positions = Mathematics::calculateDistributedPositions(8, CH, false);

	window->createScreen("empty");
	window->createScreen("main");
	window->getScreen("main")->createButton("skyEditor", fvec2(0.0f, positions[0]), TEXT_SIZE("Sky"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("terrainEditor", fvec2(0.0f, positions[1]), TEXT_SIZE("Terrain"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Terrain", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("waterEditor", fvec2(0.0f, positions[2]), TEXT_SIZE("Water"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Water", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("modelEditor", fvec2(0.0f, positions[3]), TEXT_SIZE("Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quad3dEditor", fvec2(0.0f, positions[4]), TEXT_SIZE("Quad3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quad2dEditor", fvec2(0.0f, positions[5]), TEXT_SIZE("Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("text3dEditor", fvec2(0.0f, positions[6]), TEXT_SIZE("Text3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("text2dEditor", fvec2(0.0f, positions[7]), TEXT_SIZE("Text2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Text2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->setActiveScreen("main");
}

void LeftViewportController::update()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "main")
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
		{
			if(_skyEditor->loadSkiesFromFile())
			{
				_skyEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("terrainEditor")->isHovered())
		{
			if(_terrainEditor->loadTerrainsFromFile())
			{
				_terrainEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("waterEditor")->isHovered())
		{
			if(_waterEditor->loadWatersFromFile())
			{
				_waterEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("modelEditor")->isHovered())
		{
			if(_modelEditor->loadModelsFromFile())
			{
				_modelEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quad3dEditor")->isHovered())
		{
			if(_quad3dEditor->loadQuad3dsFromFile())
			{
				_quad3dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("quad2dEditor")->isHovered())
		{
			if(_quad2dEditor->loadQuad2dsFromFile())
			{
				_quad2dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("text3dEditor")->isHovered())
		{
			if(_text3dEditor->loadText3dsFromFile())
			{
				_text3dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("text2dEditor")->isHovered())
		{
			if(_text2dEditor->loadText2dsFromFile())
			{
				_text2dEditor->load();
			}
		}
	}

	_skyEditor->update();
	_terrainEditor->update();
	_waterEditor->update();
	_modelEditor->update();
	_quad3dEditor->update();
	_quad2dEditor->update();
	_text3dEditor->update();
	_text2dEditor->update();
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