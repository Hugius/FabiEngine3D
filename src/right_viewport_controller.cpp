#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "right_viewport_controller.hpp"

void RightViewportController::initialize()
{
	_gui->getRightViewport()->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), FRAME_COLOR);

	const auto window = _gui->getRightViewport()->getWindow("main");
	const auto positions = Mathematics::calculateDistributedPositions(9, CH, false);

	window->createScreen("empty");
	window->createScreen("main");
	window->getScreen("main")->createButton("animation3dEditor", fvec2(0.0f, positions[0]), TEXT_SIZE("Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation2dEditor", fvec2(0.0f, positions[1]), TEXT_SIZE("Animation2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("aabbEditor", fvec2(0.0f, positions[2]), TEXT_SIZE("AABB"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "AABB", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("pointlightEditor", fvec2(0.0f, positions[3]), TEXT_SIZE("Pointlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pointlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("spotlightEditor", fvec2(0.0f, positions[4]), TEXT_SIZE("Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("sound3dEditor", fvec2(0.0f, positions[5]), TEXT_SIZE("Sound3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sound3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("sound2dEditor", fvec2(0.0f, positions[6]), TEXT_SIZE("Sound2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Sound2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("worldEditor", fvec2(0.0f, positions[7]), TEXT_SIZE("World"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "World", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("scriptEditor", fvec2(0.0f, positions[8]), TEXT_SIZE("Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->setActiveScreen("main");
}

void RightViewportController::update()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "main")
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("animation3dEditor")->isHovered())
		{
			if(_modelEditor->loadModelsFromFile() && _animation3dEditor->loadAnimation3dsFromFile())
			{
				_animation3dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("animation2dEditor")->isHovered())
		{
			if(_animation2dEditor->loadAnimation2dsFromFile())
			{
				_animation2dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("aabbEditor")->isHovered())
		{
			if(_aabbEditor->loadAabbsFromFile())
			{
				_aabbEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("pointlightEditor")->isHovered())
		{
			if(_pointlightEditor->loadPointlightsFromFile())
			{
				_pointlightEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("spotlightEditor")->isHovered())
		{
			if(_spotlightEditor->loadSpotlightsFromFile())
			{
				_spotlightEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sound3dEditor")->isHovered())
		{
			if(_sound3dEditor->loadSound3dsFromFile())
			{
				_sound3dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sound2dEditor")->isHovered())
		{
			if(_sound2dEditor->loadSound2dsFromFile())
			{
				_sound2dEditor->load();
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("worldEditor")->isHovered())
		{
			_worldEditor->load();
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("scriptEditor")->isHovered())
		{
			if(_scriptEditor->loadScriptFiles(true))
			{
				_scriptEditor->load();
			}
		}
	}

	_animation3dEditor->update();
	_animation2dEditor->update();
	_aabbEditor->update();
	_pointlightEditor->update();
	_spotlightEditor->update();
	_sound3dEditor->update();
	_sound2dEditor->update();
	_worldEditor->update();
	_scriptEditor->update();
}

void RightViewportController::inject(shared_ptr<PointlightEditor> pointlightEditor)
{
	_pointlightEditor = pointlightEditor;
}

void RightViewportController::inject(shared_ptr<Sound3dEditor> sound3dEditor)
{
	_sound3dEditor = sound3dEditor;
}

void RightViewportController::inject(shared_ptr<SpotlightEditor> spotlightEditor)
{
	_spotlightEditor = spotlightEditor;
}

void RightViewportController::inject(shared_ptr<Animation3dEditor> animation3dEditor)
{
	_animation3dEditor = animation3dEditor;
}

void RightViewportController::inject(shared_ptr<Sound2dEditor> sound2dEditor)
{
	_sound2dEditor = sound2dEditor;
}

void RightViewportController::inject(shared_ptr<WorldEditor> worldEditor)
{
	_worldEditor = worldEditor;
}

void RightViewportController::inject(shared_ptr<ScriptEditor> scriptEditor)
{
	_scriptEditor = scriptEditor;
}

void RightViewportController::inject(shared_ptr<Animation2dEditor> animation2dEditor)
{
	_animation2dEditor = animation2dEditor;
}

void RightViewportController::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void RightViewportController::inject(shared_ptr<AabbEditor> aabbEditor)
{
	_aabbEditor = aabbEditor;
}