#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateMainSettingsMenu()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettings")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuSettings");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("graphics")->isHovered()) // Set speed button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
				}
				else if (screen->getButton("setSpeed")->isHovered()) // Set speed button
				{
					_gui->getGlobalScreen()->addValueForm("setSpeed", "Camera speed", _customCameraSpeed, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuMain");
				}
			}

			// Setting camera speed
			_gui->getGlobalScreen()->checkValueForm("setSpeed", _customCameraSpeed, {});
		}
	}
}

void SceneEditor::_updateGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphics")
	{
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphics");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("shadows")->isHovered())
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphicsShadows");
				_fe3d.misc_enableShadowFrameRendering();
			}
			else if (screen->getButton("motionblur")->isHovered())
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphicsMotionblur");
			}
			else if (screen->getButton("dof")->isHovered())
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphicsDof");
			}
			else if (screen->getButton("fog")->isHovered())
			{

			}
			else if (screen->getButton("lensflare")->isHovered())
			{

			}
			else if (screen->getButton("skyHdr")->isHovered())
			{

			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettings");
			}
		}
	}
}

void SceneEditor::_updateShadowGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphicsShadows")
	{
		// Current values
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphicsShadows");
		bool enabled = _fe3d.gfx_isShadowsEnabled();
		float size = _fe3d.gfx_getShadowSize();
		vec3 position = _fe3d.gfx_getShadowEyePosition();
		vec3 center = _fe3d.gfx_getShadowCenter();
		bool isFollowingCamera = _fe3d.gfx_isShadowFollowingCamera();

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("size", "Size", _fe3d.gfx_getShadowSize(), vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("position")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("positionX", "X", _fe3d.gfx_getShadowEyePosition().x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionY", "Y", _fe3d.gfx_getShadowEyePosition().y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("positionZ", "Z", _fe3d.gfx_getShadowEyePosition().z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("center")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("centerX", "X", _fe3d.gfx_getShadowCenter().x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("centerY", "Y", _fe3d.gfx_getShadowCenter().y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				_gui->getGlobalScreen()->addValueForm("centerZ", "Z", _fe3d.gfx_getShadowCenter().z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("follow")->isHovered())
			{
				isFollowingCamera = !isFollowingCamera;
			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
				_fe3d.misc_disableShadowFrameRendering();
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Size value
		_gui->getGlobalScreen()->checkValueForm("size", size);

		// Position values
		_gui->getGlobalScreen()->checkValueForm("positionX", position.x);
		_gui->getGlobalScreen()->checkValueForm("positionY", position.y);
		_gui->getGlobalScreen()->checkValueForm("positionZ", position.z);

		// Center values
		_gui->getGlobalScreen()->checkValueForm("centerX", position.x);
		_gui->getGlobalScreen()->checkValueForm("centerY", position.y);
		_gui->getGlobalScreen()->checkValueForm("centerZ", position.z);

		// Following button content
		_fe3d.textEntity_setTextContent(screen->getButton("follow")->getTextfield()->getEntityID(), isFollowingCamera ? "Follow cam: ON" : "Follow cam: OFF");

		// Enable or disable shadows
		if (enabled)
		{
			_fe3d.gfx_enableShadows(position, center, size, size * 1.5f, isFollowingCamera);
		}
		else
		{
			_fe3d.gfx_disableShadows();
		}
	}
}

void SceneEditor::_updateMotionblurGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphicsMotionblur")
	{
		// Current values
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphicsMotionblur");
		bool enabled = _fe3d.gfx_isMotionBlurEnabled();
		float strength = _fe3d.gfx_getMotionBlurStrength();

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("strength")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("strength", "Strength", strength, vec2(0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
		}
		
		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Strength value
		_gui->getGlobalScreen()->checkValueForm("strength", strength);

		// Enable or disable motionblur
		if (enabled)
		{
			_fe3d.gfx_enableMotionBlur(strength);
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
		}
	}
}

void SceneEditor::_updateDofGraphicsSettingsMenu()
{
	if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuSettingsGraphicsDof")
	{
		// Current values
		auto screen = _leftWindow->getScreen("sceneEditorMenuSettingsGraphicsDof");
		bool enabled = _fe3d.gfx_isMotionBlurEnabled();
		float strength = _fe3d.gfx_getMotionBlurStrength();

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("enabled")->isHovered())
			{
				enabled = !enabled;
			}
			else if (screen->getButton("strength")->isHovered())
			{
				_gui->getGlobalScreen()->addValueForm("strength", "Strength", strength, vec2(0.0f), vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_leftWindow->setActiveScreen("sceneEditorMenuSettingsGraphics");
			}
		}

		// Enabled button content
		_fe3d.textEntity_setTextContent(screen->getButton("enabled")->getTextfield()->getEntityID(), enabled ? "Enabled: YES" : "Enabled: NO");

		// Strength value
		_gui->getGlobalScreen()->checkValueForm("strength", strength);

		// Enable or disable motionblur
		if (enabled)
		{
			_fe3d.gfx_enableMotionBlur(strength);
		}
		else
		{
			_fe3d.gfx_disableMotionBlur();
		}
	}
}

void SceneEditor::_updateFogGraphicsSettingsMenu()
{

}

void SceneEditor::_updateLensflareGraphicsSettingsMenu()
{

}

void SceneEditor::_updateskyHdrGraphicsSettingsMenu()
{

}