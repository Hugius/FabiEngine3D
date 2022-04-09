#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseEditor
{
public:
	virtual void update() = 0;

	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<GuiManager> gui);
	void setCurrentProjectId(const string & currentProjectId);
	void load();
	void unload();

	const bool isLoaded() const;

protected:
	virtual void _load() = 0;
	virtual void _unload() = 0;
	virtual void _loadGUI() = 0;
	virtual void _unloadGUI() = 0;

	const string & getCurrentProjectId() const;

	static inline const fvec3 SCROLLING_LIST_COLOR = fvec3(0.25f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.1f, 0.1f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.5f, 0.5f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

	static inline constexpr float COLOR_MULTIPLIER = 255.0f;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _gui = nullptr;

private:
	string _currentProjectId = "";

	bool _isEditorLoaded = false;
};