#pragma once

#include "fabi_engine_3d.hpp"

enum class ScriptActionType
{

};

class ScriptAction
{
public:
	ScriptAction(FabiEngine3D& fe3d, ScriptActionType actionType);

	virtual void execute() = 0;

	const ScriptActionType getType();

protected:
	FabiEngine3D& _fe3d;

private:
	const ScriptActionType _actionType;
};