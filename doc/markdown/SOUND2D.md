# Sound2D

## 1. General

- The sound2D is a stereo audio in 2D space.
- A single sound2D can be simultaneously started multiple times.
- Each of these sound2D instances can be started and stopped individually.
- Every sound2D instance plays on a unique sound channel.
- Sound channels make sure that all the sound waves are mixed together.
- Changes in volume can be delayed if too many sounds are playing simultanously.
- If no audio memory is available, sounds cannot be started.
- If no audio device is connected, sounds cannot be started and all sounds are stopped immediately.
- Sounds with a large audio file (5 minutes long for example) can cause a lag spike when started.

## 2. Base Properties

- **ID**: the unique identifier of the sound
  - Type: `string`
  - Constraints: cannot be empty or contain spaces/capitals/specials
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: cannot be changed

## 3. Started Properties

- **Paused**: the audio is paused
  - Type: `boolean`
  - Constraints: none
- **Play Count**: the amount of (remaining) times the sound must play
  - Type: `integer`
  - Constraints: at least `-1`
- **Volume**: the volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Left Intensity**: the left speaker volume intensity of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Right Intensity**: the right speaker volume intensity of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
