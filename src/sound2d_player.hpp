#pragma once

#include "sound2d_manager.hpp"
#include "started_sound2d.hpp"

#include <string>
#include <array>
#include <vector>
#include <memory>

using std::string;
using std::array;
using std::vector;
using std::shared_ptr;

class Sound2dPlayer final
{
public:
	void inject(shared_ptr<Sound2dManager> sound2dManager);
	void update();
	void startSound(const string& id, int playCount);
	void pauseSound(const string& id);
	void resumeSound(const string& id);
	void stopSound(const string& id);

	const bool isChannelAvailable() const;
	const bool isSoundStarted(const string& id) const;
	const bool isSoundPaused(const string& id) const;

private:
	const unsigned int _getFreeChannel() const;

	static inline constexpr unsigned int MAX_CHANNEL_COUNT = 1024;

	array<shared_ptr<StartedSound2D>, MAX_CHANNEL_COUNT> _startedSounds;

	shared_ptr<Sound2dManager> _sound2dManager = nullptr;
};