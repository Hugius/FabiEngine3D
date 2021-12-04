# Audio

## 1. General

- There are 2 types of audio: music (2D) and sound (2D & 3D)
- Musics play automatically (and randomly) from a playlist
- Only 1 music can be playing at a time
- Sounds play only when you start it
- Multiple sounds can be playing at the same time

## 2. Music

### 2.1 `string`

- **Audio Path**: the path of the audio file
  - Constraints: none

## 3. Sound 2D

### 3.1 `string`

- **ID**: the identifier of the sound
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Constraints: none

### 3.2 `decimal`

- **Volume**: the volume of the audio
  - Constraints: between `0.0` and `1.0`

## 4. Sound 3D

### 4.1 `string`

- **ID**: the identifier of the sound
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Constraints: none

### 4.2 `decimal3`

- **Position**: the XYZ position of the sound
  - Constraints: none
- **Position Target**: the target XYZ position of the sound
  - Constraints: none

### 4.2 `decimal`

- **Position Target Speed**: the speed with which the sound moves to the target position
  - Constraints: at least `0.0`
- **Volume**: the volume of the audio
  - Constraints: between `0.0` and `1.0`
- **Max Volume**: the maximum volume of the audio
  - Constraints: between `0.0` and `1.0`
- **Max Distance**: the maximum distance from which the audio is audible
  - Constraints: at least `0.0`
