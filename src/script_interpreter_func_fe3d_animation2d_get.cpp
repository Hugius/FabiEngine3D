#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_is_billboard_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isBillboardAnimationStarted(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isBillboardAnimationPlaying(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isBillboardAnimationPaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isBillboardAnimationAutopaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationRowCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationColumnCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationRowIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationColumnIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationPlayCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getBillboardAnimationFramestep(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuadAnimationStarted(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuadAnimationPlaying(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuadAnimationPaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_quad_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->isQuadAnimationAutopaused(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationRowCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationColumnCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationRowIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationColumnIndex(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationPlayCount(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_quad_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dQuad(args[1].getString(), false))
			{
				const auto result = _animation2dEditor->getQuadAnimationFramestep(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation2d` functionality as networking server!");
	}

	return true;
}