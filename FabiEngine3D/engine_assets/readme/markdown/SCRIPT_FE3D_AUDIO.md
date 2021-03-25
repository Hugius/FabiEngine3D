# Audio (only 2D)
- `fe3d:audio_place2D`(`STR` newID, `STR` previewID) ---> `NONE`  
  Places a new 2D audio with **newID** (cannot start with @) based on audio with **previewID**.
- `fe3d:audio_set_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the **volume** of audio with **ID**.
- `fe3d:audio_get_volume`(`STR` ID) ---> `DEC`  
  Returns the volume of audio with **ID**.

# Audio (only 3D)
- `fe3d:audio_place3D`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z, `DEC` volume, `DEC` distance) ---> `NONE`  
  Places a new 3D audio with **newID** (cannot start with @) based on audio with **previewID** at position as **xyz** at a maximum **volume** and **distance**.
- `fe3d:audio_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of audio with **ID**.
- `fe3d:audio_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the audio with factor **xyz** of audio with **ID**.
- `fe3d:audio_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of audio with **ID**.
- `fe3d:audio_set_max_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the maximum **volume** of 3D audio with **ID**.
- `fe3d:audio_get_max_volume`(`STR` ID) ---> `DEC`  
  Returns the maximum volume of 3D audio with **ID**.
- `fe3d:audio_set_max_distance`(`STR` ID, `DEC` distance) ---> `NONE`  
  Sets the maximum **distance** of 3D audio with **ID**.
- `fe3d:audio_get_max_distance`(`STR` ID) ---> `DEC`  
  Returns the maximum distance of 3D audio with **ID**.

# Audio (2D & 3D)
- `fe3d:audio_is_existing`(`STR` ID) ---> `BOOL`  
  Returns true if audio with **ID** is existing.
- `fe3d:audio_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all audio which IDs start with **subID**.
- `fe3d:audio_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all audios.
- `fe3d:audio_delete`(`STR` ID) ---> `NONE`  
  Deletes audio with **ID** if existing.
- `fe3d:audio_delete_all`() ---> `NONE`  
  Deletes all audio.
- `fe3d:audio_is_playing`(`STR` ID) ---> `BOOL`  
  Returns true if audio with **ID** is playing.
- `fe3d:audio_play`(`STR` ID, `INT` loops, `DEC` volume) ---> `NONE`  
  Plays audio with **ID** and repeat it **loops** times at a maximum **volume**.
- `fe3d:audio_is_paused`(`STR` ID) ---> `BOOL`  
  Returns true if audio with **ID** is paused.
- `fe3d:audio_pause`(`STR` ID) ---> `NONE`  
  Pauses playing audio with **ID**.
- `fe3d:audio_pause_all`() ---> `NONE`  
  Pauses all playing audio.
- `fe3d:audio_resume`(`STR` ID) ---> `NONE`  
  Resumes paused audio with **ID**.
- `fe3d:audio_resume_all`() ---> `NONE`  
  Resumes all paused audio.
- `fe3d:audio_stop`(`STR` ID) ---> `NONE`  
  Stops playing audio with **ID**.
- `fe3d:audio_stop_all`() ---> `NONE`  
  Stops all playing audio.
- `fe3d:audio_is_3D`(`STR` ID) ---> `BOOL`  
  Returns true if audio with **ID** is 3D audio.
  
# Music
- `fe3d:music_add_to_playlist`(`STR` previewID) ---> `NONE`  
  Adds music to the playlist based on audio with **previewID**.
- `fe3d:music_clear_playlist`() ---> `NONE`  
  Clears and stops all music from the playlist.
- `fe3d:music_set_volume`(`DEC` volume) ---> `NONE`  
  Sets music volume.
- `fe3d:music_get_volume`(`STR` previewID) ---> `DEC`  
  Returns music volume.
- `fe3d:music_is_playing`(`STR` previewID) ---> `BOOL`  
  Returns true if music is playing.
- `fe3d:music_pause`() ---> `NONE`  
  Pauses playing music.
- `fe3d:music_is_paused`() ---> `BOOL`  
  Returns true if music is paused.
- `fe3d:music_resume`() ---> `NONE`  
  Resumes paused music.
