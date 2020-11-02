#pragma once

#include "opengl_buffer.hpp"

#include <string>

using std::string;

class BaseEntity
{
public:
	BaseEntity(const string& ID);
	virtual ~BaseEntity();

	void addOglBuffer(OpenGLBuffer* buffer, bool deleteOnDestroy = true);
	void clearOglBuffers();
	void setVisible(bool val);

	const vector<OpenGLBuffer*> & getOglBuffers() const;
	const OpenGLBuffer* getOglBuffer(int index) const;
	const OpenGLBuffer* getOglBuffer() const;

	const string& getID() const;
	const bool isVisible() const;

private:
	vector<OpenGLBuffer*> _oglBuffers;
	vector<bool> _oglBufferMemoryManagement;

	string _ID = "ID_NULL";

	bool _visible = true;
};