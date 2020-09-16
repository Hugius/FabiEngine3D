#pragma once

#include "script_action.hpp"

class ScriptActionCamera final : public ScriptAction
{
public:
	using ScriptAction::ScriptAction;

	void execute() override;
	void reset() override;

private:
	
};