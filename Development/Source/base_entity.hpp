#pragma once

#include <string>

using std::string;

#include "opengl_buffer.hpp"

class BaseEntity
{
public:
	BaseEntity() = default;
	virtual ~BaseEntity();

	void load(const string & ID);
	void addOglBuffer(OpenGLBuffer * buffer);
	void setEnabled(bool val);

	const vector<OpenGLBuffer*> & getOglBuffers() const;
	const OpenGLBuffer * getOglBuffer(int index) const;
	const OpenGLBuffer * getOglBuffer() const;

	const string & getID() const;
	const bool isEnabled() const;

private:
	vector<OpenGLBuffer*> _oglBuffers;

	string _ID = "ID_NULL";

	bool _enabled = true;
};