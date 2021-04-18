# Sound (only 2D)
- `fe3d:sound_place2D`(`STR` newID, `STR` previewID, `DEC` volume) ---> `NONE`  
  Places a new 2D sound with **newID** (cannot start with @) based on audio with **previewID**. Has an initial **volume**.
- `fe3d:sound_set_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the **volume** of sound with **ID**.

# Sound (only 3D)
- `fe3d:sound_place3D`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z, `DEC` volume, `DEC` distance) ---> `NONE`  
  Places a new 3D sound with **newID** (cannot start with @) based on audio with **previewID** at position as **xyz** with a maximum **volume** and a maximum **distance**.
- `fe3d:sound_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of sound with **ID**.
- `fe3d:sound_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the sound with factor **xyz** of sound with **ID**.
- `fe3d:sound_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of sound with **ID**.
- `fe3d:sound_set_max_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the maximum **volume** of 3D sound with **ID**.
- `fe3d:sound_get_max_volume`(`STR` ID) ---> `DEC`  
  Returns the maximum volume of 3D sound with **ID**.
- `fe3d:sound_set_max_distance`(`STR` ID, `DEC` distance) ---> `NONE`  
  Sets the maximum **distance** of 3D sound with **ID**.
- `fe3d:sound_get_max_distance`(`STR` ID) ---> `DEC`  
  Returns the maximum distance of 3D sound with **ID**.

# Sound (2D & 3D)
- `fe3d:sound_is_existing`(`STR` ID) ---> `BOOL`  
  Returns true if sound with **ID** is existing.
- `fe3d:sound_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all sound which IDs start with **subID**.
- `fe3d:sound_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all sounds.
- `fe3d:sound_delete`(`STR` ID) ---> `NONE`  
  Deletes sound with **ID** if existing.
- `fe3d:sound_set_enabled`(`BOOL` enabled) ---> `NONE`  
  Sets sound system to **enabled**.
- `fe3d:sound_play`(`STR` ID, `INT` loops, `INT` fadeMS) ---> `NONE`  
  Plays sound with **ID** and repeats it **loops** times (-1 to play forever). Fades in with **fadeMS** milliseconds.
- `fe3d:sound_play_forced`(`STR` ID, `INT` loops, `INT` fadeMS) ---> `NONE`  
  Plays sound with **ID** and repeats it **loops** times (-1 to play forever). Fades in with **fadeMS** milliseconds. The sound playback will be forced even if the sound is already playing (sound playbacks will be stacked and playing at the same time).
- `fe3d:sound_pause`(`STR` ID) ---> `NONE`  
  Pauses playing sound with **ID**.
- `fe3d:sound_pause_all`() ---> `NONE`  
  Pauses all playing sound.
- `fe3d:sound_resume`(`STR` ID) ---> `NONE`  
  Resumes paused sound with **ID**.
- `fe3d:sound_resume_all`() ---> `NONE`  
  Resumes all paused sound.
- `fe3d:sound_stop`(`STR` ID, `INT` fadeMS) ---> `NONE`  
  Stops playing sound with **ID**. Fades out with **fadeMS** milliseconds.
- `fe3d:sound_stop_all`() ---> `NONE`  
  Stops all playing sound.
- `fe3d:sound_is_started`(`STR` ID) ---> `BOOL`  
  Returns true if sound with **ID** was started
- `fe3d:sound_is_playing`(`STR` ID) ---> `BOOL`  
  Returns true if sound with **ID** is currently playing.
- `fe3d:sound_is_paused`(`STR` ID) ---> `BOOL`  
  Returns true if sound with **ID** is paused.
- `fe3d:sound_is_3D`(`STR` ID) ---> `BOOL`  
  Returns true if sound with **ID** is 3D sound.
- `fe3d:sound_get_volume`(`STR` ID) ---> `DEC`  
  Returns the volume of sound with **ID**.
  
# Music
- `fe3d:music_add_to_playlist`(`STR` previewID) ---> `NONE`  
  Adds music to the playlist based on audio with **previewID** and plays random music from the playlist.
- `fe3d:music_clear_playlist`() ---> `NONE`  
  Clears and stops all music from the playlist.
- `fe3d:music_set_enabled`(`BOOL` enabled) ---> `NONE`  
  Sets music system to **enabled**.
- `fe3d:music_set_volume`(`DEC` volume) ---> `NONE`  
  Sets music volume.
- `fe3d:music_get_volume`() ---> `DEC`  
  Returns music volume.
- `fe3d:music_is_started`() ---> `BOOL`  
  Returns true if music was started.
- `fe3d:music_is_playing`() ---> `BOOL`  
  Returns true if music is currently playing.
- `fe3d:music_pause`() ---> `NONE`  
  Pauses playing music.
- `fe3d:music_is_paused`() ---> `BOOL`  
  Returns true if music is paused.
- `fe3d:music_resume`() ---> `NONE`  
  Resumes paused music.
