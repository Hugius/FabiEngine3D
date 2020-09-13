#include "script_action_camera.hpp"

ScriptActionCamera::ScriptActionCamera(FabiEngine3D& fe3d) :
	ScriptAction(fe3d, ScriptActionType::CAMERA)
{

}

void ScriptActionCamera::execute()
{
	_fe3d.logger_throwInfo("JEMOEDER");
}