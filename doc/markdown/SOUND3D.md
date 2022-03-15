# Sound3D

## 1. General

- Sound3D is stereo audio in 3D space.
- A single sound can be simultaneously started multiple times.
- Each of these sound instances can be started and stopped individually.
- Every sound instance plays on a unique sound channel (with a maximum of 1024).
- Sound channels make sure that all the sound waves are mixed together.
- Stereo audio is supported.
- Volume cannot be changed directly, because it is calculated by FabiEngine3D based on the sound position.
- The calculated volume uses stereo panning to achieve a 3D effect.
- Changes in volume can be delayed if too many sounds are playing simultanously.
- If no audio memory is available, sounds cannot be started.
- If no audio device is connected, sounds cannot be started and all sounds are stopped immediately.

## 2. Base Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: cannot be changed
- **Position**: the XYZ position of the sound
  - Type: `decimal3`
  - Constraints: none
- **Max Volume**: the maximum volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Max Distance**: the maximum distance from which the audio is audible
  - Type: `decimal`
  - Constraints: at least `0.0`

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
