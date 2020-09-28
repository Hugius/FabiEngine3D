#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"
#include "script_executor.hpp"

class ScriptEditor final
{
public:
	ScriptEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~ScriptEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string & projectName);

	ScriptExecutor& getScriptExecutor();

	bool isLoaded();

private:
	void _updateGUI();
	void _updateTextWriter();
	void _updateMiscellaneous();
	void _loadScriptFromFile();
	void _saveScriptToFile();
	void _reloadScriptTextDisplay();

	// General stuff
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;
	shared_ptr<EngineGuiWindow> _rightWindow = nullptr;
	Script _script;
	ScriptExecutor _scriptExecutor;

	// Editor constants
	const string _fontPath = "engine\\fonts\\lucida.ttf";
	const vec3 _cameraStartingPosition = vec3(0.0f, 0.0f, 10.0f);
	const vec3 _scriptTextStartingPosition = vec3(-11.0f, 5.5f, 0.5f);
	const vec3 _lineNumberColor = vec3(0.0f, 1.0f, 0.0f);
	const vec3 _characterColor = vec3(1.0f);
	const float _scrollingSpeed = 0.1f;
	const float _maxScrollingAcceleration = 10.0f;
	const float _characterWidth = 0.25f;
	const float _characterHeight = 0.75f;
	const float _horizontalCharacterOffset = 0.25f;
	const float _verticalLineOffset = 1.0f;
	const float _horizontalLineOffset = 0.5f;
	const int _continuousTextActionFrameMinimum = 75;
	const int _continuousTextActionInterval = 5;
	
	// Editor variables
	string _currentProjectName = "";
	string _currentScriptFileID = "";
	float _scrollingAcceleration = 0.0f;
	unsigned int _cursorLineIndex = 0;
	unsigned int _cursorPlaceIndex = 0;
	unsigned int _maxPassedBarFrames = 50;
	bool _isLoaded = false;
	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;
};