#include "entity_placer.hpp"

void EntityPlacer::update()
{
	if (_isLoaded)
	{
		_updateCamera();
		_updateManagementScreen();
		_updateModelScreen();
		_updateBillboardScreen();
		_updateLightScreen();
	}
}

void EntityPlacer::_updateManagementScreen()
{
	auto screen = _leftWindow->getScreen("placeManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("placeModel")->isHovered()) // Add model button
		{
			_leftWindow->setActiveScreen("modelPlaceManagement");
		}
		else if (screen->getButton("placeBillboard")->isHovered()) // Place billboard button
		{
			_leftWindow->setActiveScreen("billboardPlaceManagement");
		}
		else if (screen->getButton("placeLight")->isHovered()) // Place light button
		{
			_leftWindow->setActiveScreen("lightPlaceManagement");
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitEntityPlacer", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitEntityPlacer"))
	{
		save();
		_leftWindow->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitEntityPlacer"))
	{
		_leftWindow->setActiveScreen("main");
		unload();
	}
}

void EntityPlacer::_updateModelScreen()
{
	auto screen = _leftWindow->getScreen("placeModel");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{

	}
}

void EntityPlacer::_updateBillboardScreen()
{

}

void EntityPlacer::_updateLightScreen()
{

}

void EntityPlacer::_updateCamera()
{
	// Looking
	if (_fe3d.misc_isMouseInsideViewport() && _fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
	{
		// Move mouse to middle when pressed first time
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_RIGHT))
		{
			_fe3d.misc_centerMousePos();
		}

		// Enable FPS camera
		_fe3d.gfx_enableMotionBlur();
		_fe3d.camera_enableFirstPersonView(10.0f);
		_fe3d.camera_disableLookat();
		_fe3d.misc_hideCursor();
	}
	else
	{
		_fe3d.gfx_disableMotionBlur();
		_fe3d.camera_disableFirstPersonView();
		_fe3d.misc_showCursor();
	}

	// X movement
	if (_fe3d.input_getKeyDown(Input::KEY_A))
	{
		_fe3d.camera_translateFollowX(-20.0f);
	}
	else if (_fe3d.input_getKeyDown(Input::KEY_D))
	{
		_fe3d.camera_translateFollowX(20.0f);
	}

	// Y movement
	if (_fe3d.input_getKeyDown(Input::KEY_SPACE))
	{
		_fe3d.camera_translate(vec3(0.0f, 0.5f, 0.0f));
	}
	else if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT))
	{
		_fe3d.camera_translate(vec3(0.0f, -0.5f, 0.0f));
	}

	// Z movement
	if (_fe3d.input_getKeyDown(Input::KEY_W))
	{
		_fe3d.camera_translateFollowZ(20.0f);
	}
	else if (_fe3d.input_getKeyDown(Input::KEY_S))
	{
		_fe3d.camera_translateFollowZ(-20.0f);
	}
}