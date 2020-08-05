#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_button.hpp"

class EngineGuiWriteField final : public EngineGuiButton
{
public:
	EngineGuiWriteField(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, 
		vec3 textColor, vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed);

	void update(bool hoverable) override;
	void setActive(bool active);
	void setPermActive(bool active);

	bool cancelledInput();
	bool confirmedInput();
	bool isActive();
	bool hasTextContentChanged();

	string getTextContent();

	void setTextContent(const string& content);

private:
	void _updateActivation();
	void _updateTyping();

	bool _mustBeActive = false;
	bool _isActive = false;
	bool _cancelledInput = false;
	bool _confirmedInput = false;

	const bool _noNumbers;
	const bool _noCaps;
	const bool _noSpecials;
	const bool _noLetters;
	const bool _minusAllowed;

	const int _maxPassedBarFrames = 50;
	const int _maxPassedBackspaceFrames = 20;

	string _lastTextContent = "";
	string _currentTextContent = "";

	const float _charWidth = 0.02f;
};