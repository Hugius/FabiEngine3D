#pragma once

#include "vertex_buffer.hpp"

#include <map>
#include <string>
#include <memory>

using std::map;
using std::string;
using std::shared_ptr;

class VertexBufferCache final
{
public:
	void storeBuffer(const string& ID, shared_ptr<VertexBuffer> buffer);

	const shared_ptr<VertexBuffer> getBuffer(const string& ID) const;

	const map<string, shared_ptr<VertexBuffer>>& getBuffers() const;

private:
	map<string, shared_ptr<VertexBuffer>> _cache;
};