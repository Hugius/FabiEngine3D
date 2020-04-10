#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiButton.hpp"

class EngineGuiWritefield final : public EngineGuiButton
{
public:
	//EngineGuiWritefield(EngineGuiWritefield&& other) = default;
	EngineGuiWritefield(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 textColor);

	void update(float delta) override;

private:
	void _updateTyping(float delta);
};