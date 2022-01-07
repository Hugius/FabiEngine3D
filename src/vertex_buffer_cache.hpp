#pragma once

#include "vertex_buffer.hpp"

#include <map>
#include <string>
#include <memory>

using std::map;
using std::pair;
using std::string;
using std::shared_ptr;

class VertexBufferCache final
{
public:
	void storeBuffer(const string& filePath, const string& partID, shared_ptr<VertexBuffer> buffer);

	const shared_ptr<VertexBuffer> getBuffer(const string& filePath, const string& partID) const;

	const vector<shared_ptr<VertexBuffer>> getBuffers() const;

private:
	map<pair<string, string>, shared_ptr<VertexBuffer>> _buffers;
};