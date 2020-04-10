#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiButton.hpp"

class EngineGuiWritefield final : public EngineGuiButton
{
public:
	EngineGuiWritefield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor);

	void update(float delta) override;
	void setActive(bool active);

	bool cancelledInput();
	bool confirmedInput();

	string getTextContent();

private:
	void _updateActivation();
	void _updateTyping(float delta);

	bool _isActive = false;
	bool _cancelledInput = false;
	bool _confirmedInput = false;

	string _currentTextContent = "";

	const float _charWidth = 0.02f;
};