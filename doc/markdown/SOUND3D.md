# Sound3D

## 1. General

- Sound3D is stereo audio in 3D space.
- Each sound plays on a unique sound channel.
- Multiple sounds can be playing at the same time.
- Only a maximum of 1024 sounds can exist.

## 2. Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: cannot be changed
- **Position**: the XYZ position of the sound
  - Type: `decimal3`
  - Constraints: none
- **Volume**: the volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Max Volume**: the maximum volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Max Distance**: the maximum distance from which the audio is audible
  - Type: `decimal`
  - Constraints: at least `0.0`
