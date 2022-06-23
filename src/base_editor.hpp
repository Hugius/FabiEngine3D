#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseEditor
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<GuiManager> gui);
	void load();
	void update();
	void unload();
	void setCurrentProjectId(const string & currentProjectId);

	const string & getCurrentProjectId() const;

	const bool isLoading() const;
	const bool isLoaded() const;

protected:
	virtual void _load() = 0;
	virtual void _update() = 0;
	virtual void _unload() = 0;
	virtual void _loadGUI() = 0;
	virtual void _unloadGUI() = 0;

	static inline const fvec3 BUTTON_COLOR = fvec3(0.4f, 0.4f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.8f, 0.8f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

	static inline const fvec2 LEFT_CHOICE_FORM_POSITION = fvec2(-0.5f, 0.1f);
	static inline const fvec2 CENTER_CHOICE_FORM_POSITION = fvec2(0.0f, 0.1f);
	static inline const fvec2 RIGHT_CHOICE_FORM_POSITION = fvec2(0.5f, 0.1f);
	static inline const fvec2 VALUE_FORM_POSITION = fvec2(0.0f, 0.1f);
	static inline const fvec2 ANSWER_FORM_POSITION = fvec2(0.0f, 0.25f);

	static inline constexpr float CW = 0.11f;
	static inline constexpr float CH = 0.085f;

	static inline constexpr int VALUE_FORM_SIZE = 15;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _gui = nullptr;

private:
	string _currentProjectId = "";

	bool _isLoading = false;
	bool _isLoaded = false;
};