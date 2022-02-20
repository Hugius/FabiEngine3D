#pragma once

#include "vertex_buffer.hpp"

#include <unordered_map>
#include <string>
#include <memory>

using std::unordered_map;
using std::pair;
using std::string;
using std::shared_ptr;

class VertexBufferCache final
{
public:
	void storeBuffer(const string& filePath, const string& partId, shared_ptr<VertexBuffer> buffer);
	void deleteBuffer(const string& filePath, const string& partId);
	void clearBuffers();

	const shared_ptr<VertexBuffer> getBuffer(const string& filePath, const string& partId) const;

	const unordered_map<string, shared_ptr<VertexBuffer>>& getBuffers() const;
	const vector<string> getFilePaths() const;
	const vector<string> getPartIds(const string& filePath) const;

private:
	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<VertexBuffer>> _buffers;
};