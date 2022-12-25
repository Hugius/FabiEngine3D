#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:model_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			const auto result = _fe3d->model_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:model_get_editor_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _duplicator->getEditorModelId(args[0]->getString()).substr(1);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->model_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->model_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				for(const auto & result : _fe3d->model_getPartIds(args[0]->getString()))
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_visible")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isVisible(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBasePosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBasePosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBasePosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotation(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotation(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotation(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_origin_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotationOrigin(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_origin_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotationOrigin(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_rotation_origin_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseRotationOrigin(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_size_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseSize(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_size_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseSize(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_base_size_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getBaseSize(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_position_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartPosition(args[0]->getString(), args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_position_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartPosition(args[0]->getString(), args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_position_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartPosition(args[0]->getString(), args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotation(args[0]->getString(), args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotation(args[0]->getString(), args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotation(args[0]->getString(), args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_origin_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotationOrigin(args[0]->getString(), args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_origin_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotationOrigin(args[0]->getString(), args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_rotation_origin_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartRotationOrigin(args[0]->getString(), args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_size_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartSize(args[0]->getString(), args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_size_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartSize(args[0]->getString(), args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_part_size_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getPartSize(args[0]->getString(), args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMinClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMinClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMinClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_max_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMaxClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_max_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMaxClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_max_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMaxClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lightness")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getLightness(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_r")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getColor(args[0]->getString(), args[1]->getString()).r;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_g")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getColor(args[0]->getString(), args[1]->getString()).g;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_b")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getColor(args[0]->getString(), args[1]->getString()).b;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_r")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getWireframeColor(args[0]->getString(), args[1]->getString()).r;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_g")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getWireframeColor(args[0]->getString(), args[1]->getString()).g;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_b")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getWireframeColor(args[0]->getString(), args[1]->getString()).b;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_opacity")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getOpacity(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_intensity")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getEmissionIntensity(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_texture_repeat")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getTextureRepeat(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_shininess")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getSpecularShininess(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_intensity")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getSpecularIntensity(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflectivity")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getReflectivity(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_refractivity")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getRefractivity(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_distance")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getLevelOfDetailDistance(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getLevelOfDetailId(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_mesh_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getMeshPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_diffuse_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getDiffuseMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getEmissionMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getSpecularMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflection_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getReflectionMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_refraction_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getRefractionMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_normal_map_path")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getNormalMapPath(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_diffuse_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasDiffuseMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_emission_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasEmissionMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_specular_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasSpecularMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_reflection_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasReflectionMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_refraction_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasRefractionMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_has_normal_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_hasNormalMap(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_shadowed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isShadowed(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_reflected")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isReflected(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_refracted")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isRefracted(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_bright")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isBright(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_face_culled")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isFaceCulled(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_reflective")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isReflective(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_refractive")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isRefractive(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflection_type")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					switch(_fe3d->model_getReflectionType(args[0]->getString(), args[1]->getString()))
					{
						case ReflectionType::CUBE:
						{
							const auto result = "CUBE";

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

							break;
						}
						case ReflectionType::PLANAR:
						{
							const auto result = "PLANAR";

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

							break;
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_refraction_type")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					switch(_fe3d->model_getRefractionType(args[0]->getString(), args[1]->getString()))
					{
						case RefractionType::CUBE:
						{
							const auto result = "CUBE";

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

							break;
						}
						case RefractionType::PLANAR:
						{
							const auto result = "PLANAR";

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

							break;
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_specular")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isSpecular(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_wireframed")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_isWireframed(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_alpha")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getMinAlpha(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_order")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto rotationOrder = _fe3d->model_getRotationOrder(args[0]->getString());

				switch(rotationOrder)
				{
					case DirectionOrderType::XYZ:
					{
						const auto result = "XYZ";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::XZY:
					{
						const auto result = "XZY";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::YXZ:
					{
						const auto result = "YXZ";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::YZX:
					{
						const auto result = "YZX";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::ZXY:
					{
						const auto result = "ZXY";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::ZYX:
					{
						const auto result = "ZYX";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation3d_started")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				const auto result = _fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation3d_paused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				if(!_fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_isAnimation3dPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation3d_autopaused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				if(!_fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_isAnimation3dAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation3d_speed_multiplier")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				if(!_fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimation3dSpeedMultiplier(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation3d_play_count")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				if(!_fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimation3dPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation3d_frame_index")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dAnimation3d(args[1]->getString()))
			{
				if(!_fe3d->model_isAnimation3dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimation3dFrameIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				for(const auto & childAabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
				{
					const auto result = childAabbId.substr(string("model@" + args[0]->getString() + "@").size());

					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_aabb_visible")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_isVisible("model@" + args[0]->getString() + "@" + args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_position_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBasePosition("model@" + args[0]->getString() + "@" + args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_position_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBasePosition("model@" + args[0]->getString() + "@" + args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_position_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBasePosition("model@" + args[0]->getString() + "@" + args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_size_x")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBaseSize("model@" + args[0]->getString() + "@" + args[1]->getString()).x;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_size_y")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBaseSize("model@" + args[0]->getString() + "@" + args[1]->getString()).y;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_aabb_size_z")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelAabb(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->aabb_getBaseSize("model@" + args[0]->getString() + "@" + args[1]->getString()).z;

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:model` functionality as a networking server");

		return true;
	}

	return true;
}