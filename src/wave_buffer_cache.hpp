#pragma once

#include "wave_buffer.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using std::unordered_map;
using std::vector;
using std::string;
using std::shared_ptr;

class WaveBufferCache final
{
public:
	void storeBuffer(const string& filePath, shared_ptr<WaveBuffer> buffer);
	void deleteBuffer(const string& filePath);
	void clearBuffers();

	const unordered_map<string, shared_ptr<WaveBuffer>>& getBuffers() const;

	const vector<string> getFilePaths() const;

	const shared_ptr<WaveBuffer> getBuffer(const string& filePath) const;

private:
	unordered_map<string, shared_ptr<WaveBuffer>> _buffers = {};
};