#pragma once

#include <string>

using std::string;

#include "OpenGLBuffer.hpp"

class Entity
{
public:
	Entity() = default;
	virtual ~Entity();

	void load(const string & ID);
	void addOglBuffer(OpenGLBuffer * buffer);
	void setEnabled(bool val);

	const vector<OpenGLBuffer*> & getOglBuffers() const;
	const OpenGLBuffer * getOglBuffer(int index) const;
	const OpenGLBuffer * getOglBuffer() const;

	const string & getID() const;
	const bool isEnabled() const;

private:
	vector<OpenGLBuffer*> p_oglBuffers;

	string p_ID = "ID_NULL";

	bool p_enabled = true;
};