#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:model_is_existing")
	{
		auto types = {SVT::STRING};

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
	else if(functionName == "fe3d:model_find_ids")
	{
		auto types = {SVT::STRING};

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
	else if(functionName == "fe3d:model_is_visible")
	{
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
	else if(functionName == "fe3d:model_get_lod_distance")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getLevelOfDetailDistance(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_entity_id")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_getLevelOfDetailEntityId(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_mesh_path")
	{
		auto types = {SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
	else if(functionName == "fe3d:model_get_normal_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
	else if(functionName == "fe3d:model_has_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isShadowed(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_frozen")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isFrozen(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_reflected")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto result = _fe3d->model_isReflected(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_bright")
	{
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
	else if(functionName == "fe3d:model_get_reflection_type")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto reflectionType = _fe3d->model_getReflectionType(args[0]->getString(), args[1]->getString());

					if(reflectionType == ReflectionType::CUBE)
					{
						const auto result = "CUBE";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
					if(reflectionType == ReflectionType::PLANAR)
					{
						const auto result = "PLANAR";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_specular")
	{
		auto types = {SVT::STRING, SVT::STRING};

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
		auto types = {SVT::STRING, SVT::STRING};

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
	else if(functionName == "fe3d:model_get_min_texture_alpha")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					const auto result = _fe3d->model_getMinTextureAlpha(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_order")
	{
		auto types = {SVT::STRING};

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
	else if(functionName == "fe3d:model_is_animation_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				const auto result = _fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_isAnimationAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_speed_multiplier")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimationSpeedMultiplier(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimationPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_frame_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				const auto result = _fe3d->model_getAnimationFrameIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
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