# Sound2D

## 1. General

- Sound2D is stereo audio in 2D space.
- A single sound can be simultaneously started multiple times.
- Each of these sound instances can be started and stopped individually.
- Every sound instance plays on a unique sound channel (with a maximum of 1024).
- Sound channels make sure that all the sound waves are mixed together.
- Stereo audio is supported.
- If no audio device is connected, sounds cannot be started and all sounds are stopped immediately.

## 2. Base Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
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
- **Speed**: the speed of the audio
  - Type: `decimal`
  - Constraints: at least `0.0`
