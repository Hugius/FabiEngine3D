# Audio

## 1. General

- There are 2 types of audio: music (2D) and sound (2D & 3D)
- Musics play automatically (and randomly) from a playlist
- Only 1 music can be playing at a time
- Sounds play only when you start it
- Multiple sounds can be playing at the same time

- **Audio Channels**: the amount of allocated audio channels
  - Type: `integer`
  - Constraints: between `64` and `512`

## 2. Music Properties

- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: none

## 3. Sound 2D Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: none
- **Volume**: the volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`

## 4. Sound 3D Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: none
- **Position**: the XYZ position of the sound
  - Type: `decimal3`
  - Constraints: none
- **Position Target**: the target XYZ position of the sound
  - Type: `decimal3`
  - Constraints: none
- **Position Target Speed**: the speed with which the sound moves to the target position
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Volume**: the volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Max Volume**: the maximum volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Max Distance**: the maximum distance from which the audio is audible
  - Type: `decimal`
  - Constraints: at least `0.0`
