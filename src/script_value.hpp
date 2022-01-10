#pragma once

#include "engine_interface.hpp"
#include "script_value_type.hpp"

class ScriptValue final
{
public:
	ScriptValue(EngineInterface& fe3d, ScriptValueType type);
	ScriptValue(EngineInterface& fe3d, ScriptValueType type, const string& value);
	ScriptValue(EngineInterface& fe3d, ScriptValueType type, float value);
	ScriptValue(EngineInterface& fe3d, ScriptValueType type, int value);
	ScriptValue(EngineInterface& fe3d, ScriptValueType type, bool value);

	void setString(const string& value);
	void setDecimal(float value);
	void setInteger(int value);
	void setBoolean(bool value);

	const string& getString() const;

	const float getDecimal() const;

	const int getInteger() const;

	const bool getBoolean() const;

	const ScriptValueType& getType() const;

private:
	string _string = "";

	float _decimal = 0.0f;

	int _integer = 0;

	bool _boolean = false;

	ScriptValueType _type;
	EngineInterface& _fe3d;
};