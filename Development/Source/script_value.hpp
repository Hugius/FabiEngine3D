#pragma once

#include "fabi_engine_3d.hpp"

enum class ScriptValueType
{
	STRING,
	BOOLEAN,
	NUMBER,
	NONE
};

class ScriptValue
{
public:
	ScriptValue(ScriptValueType type, bool isConstant);

	void setString(string str);
	void setBoolean(bool boolean);
	void setNumber(float number);

	ScriptValueType getType();
	string getString();
	bool getBoolean();
	float getNumber();

private:
	const ScriptValueType _type;
	const bool _isConstant;

	string _string = "";
	bool _boolean = false;
	float _number = 0.0f;
};