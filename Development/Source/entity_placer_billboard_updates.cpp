#include "entity_placer.hpp"

void EntityPlacer::_updateBillboardScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "billboardPlaceManagement")
		{
			auto screen = _leftWindow->getScreen("billboardPlaceManagement");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				// Back button
				if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("placeManagement");
				}
			}
		}
	}
}