#pragma once

#include "audio.hpp"

#include <memory>
#include <windows.h>

using std::shared_ptr;

class WaveBuffer final
{
public:
	WaveBuffer(shared_ptr<Audio> audio);
	~WaveBuffer();

	const HWAVEOUT getHandle() const;

	const PWAVEHDR getHeader() const;

	const PWAVEFORMATEX getFormat() const;

private:
	HWAVEOUT _handle = nullptr;
	PWAVEHDR _header = nullptr;
	PWAVEFORMATEX _format = nullptr;
};