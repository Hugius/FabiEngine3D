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

	const PWAVEFORMATEX getFormat() const;

	const PWAVEHDR getHeader() const;

private:
	PWAVEFORMATEX _format = nullptr;

	PWAVEHDR _header = nullptr;
};