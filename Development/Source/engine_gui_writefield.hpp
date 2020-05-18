#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_button.hpp"

class EngineGuiWriteField final : public EngineGuiButton
{
public:
	EngineGuiWriteField(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, 
		vec3 textColor, vec3 textHoverColor, bool noNumbers = false, bool noCaps = false, bool noSpecials = false, bool noLetters = false);

	void update(float delta, bool hoverable) override;
	void setActive(bool active);

	bool cancelledInput();
	bool confirmedInput();

	string getTextContent();

	void setTextContent(string content);

private:
	void _updateActivation();
	void _updateTyping(float delta);

	bool _mustBeActive = false;
	bool _isActive = false;
	bool _cancelledInput = false;
	bool _confirmedInput = false;
	const bool _noNumbers;
	const bool _noCaps;
	const bool _noSpecials;
	const bool _noLetters;

	string _currentTextContent = "";

	const float _charWidth = 0.02f;
};