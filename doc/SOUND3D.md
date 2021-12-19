# Sound3D

## 1. General

- Sound3D is stereo audio in 3D space.
- Each sound plays on a unique sound channel.
- Multiple sounds can be playing at the same time.

## 2. Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
  - Write Access: editor
  - Read Access: editor + script
- **Audio Path**: the path of the audio file
  - Type: `string`
  - Constraints: none
  - Write Access: editor
  - Read Access: editor + script
- **Position**: the XYZ position of the sound
  - Type: `decimal3`
  - Constraints: none
  - Write Access: editor + script
  - Read Access: editor + script
- **Volume**: the volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
  - Write Access: none
  - Read Access: script
- **Max Volume**: the maximum volume of the audio
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
  - Write Access: editor + script
  - Read Access: editor + script
- **Max Distance**: the maximum distance from which the audio is audible
  - Type: `decimal`
  - Constraints: at least `0.0`
  - Write Access: editor + script
  - Read Access: editor + script
