#pragma once

#include "viewport_controller.hpp"
#include "environment_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "scene_editor.hpp"
#include "animation_editor.hpp"
#include "script_editor.hpp"
#include "audio_editor.hpp"
#include "settings_editor.hpp"

#define LVPC LeftViewportController

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void initialize() override;
	void update() override;

	EnvironmentEditor& getEnvironmentEditor();
	ModelEditor& getModelEditor();
	AnimationEditor& getAnimationEditor();
	BillboardEditor& getBillboardEditor();
	AudioEditor& getAudioEditor();
	SceneEditor& getSceneEditor();
	ScriptEditor& getScriptEditor();
	SettingsEditor& getSettingsEditor();

	static inline const Vec3 frameColor = Vec3(0.4f);
	static inline const Vec3 buttonColor = Vec3(0.25f, 0.25f, 1.0f);
	static inline const Vec3 buttonHoverColor = Vec3(0.75f, 0.75f, 1.0f);
	static inline const Vec3 textColor = Vec3(1.0f);
	static inline const Vec3 textHoverColor = Vec3(0.0f);

private:
	EnvironmentEditor _environmentEditor;
	ModelEditor _modelEditor;
	AnimationEditor _animationEditor;
	BillboardEditor _billboardEditor;
	AudioEditor _audioEditor;
	SceneEditor _sceneEditor;
	ScriptEditor _scriptEditor;
	SettingsEditor _settingsEditor;

	string _lastActiveEditorScreen = "";
};