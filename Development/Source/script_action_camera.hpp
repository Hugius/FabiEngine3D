#pragma once

#include "script_action.hpp"

class ScriptActionCamera final : public ScriptAction
{
public:
	ScriptActionCamera(FabiEngine3D& fe3d);

	void execute() override;

private:
	
};