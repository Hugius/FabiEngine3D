#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "text3d_editor.hpp"
#include "quad2d_editor.hpp"
#include "text2d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"
#include "script_executor.hpp"

class TopViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Quad2dEditor> quad2dEditor);
	void inject(shared_ptr<Text2dEditor> text2dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<SoundEditor> soundEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);
	void inject(shared_ptr<ScriptEditor> scriptEditor);
	void inject(shared_ptr<CustomWorldBuilder> customWorldBuilder);
	void inject(shared_ptr<Script> script);
	void inject(shared_ptr<ScriptExecutor> scriptExecutor);

	void initialize();
	void update();

	const bool isScriptStarted() const;
	const bool isScriptRunning() const;
	const bool isProjectCorrupted(const string& projectDirectoryPath) const;

private:
	void _updateProjectScreenManagement();
	void _updateGameScreenManagement();
	void _updateMiscScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreating();
	void _updateProjectLoading();
	void _updateProjectDeleting();
	void _saveCurrentProject();
	void _applyProjectChange();

	const bool _prepareProjectChoosing(const string& title) const;

	string _currentProjectId = "";

	static inline const fvec3 FRAME_COLOR = fvec3(0.075f);

	bool _isCreatingProject = false;
	bool _isLoadingProject = false;
	bool _isDeletingProject = false;

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<SoundEditor> _soundEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
	shared_ptr<CustomWorldBuilder> _customWorldBuilder = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;

	static inline const fvec3 BUTTON_COLOR = fvec3(0.0f, 0.1f, 0.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);
};