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
	void storeBuffer(const string& filePath, const string& partId, shared_ptr<VertexBuffer> buffer);
	void deleteBuffer(const string& filePath, const string& partId);
	void clear();

	const shared_ptr<VertexBuffer> getBuffer(const string& filePath, const string& partId) const;

	const map<pair<string, string>, shared_ptr<VertexBuffer>> getBuffers() const;

private:
	map<pair<string, string>, shared_ptr<VertexBuffer>> _buffers;
};