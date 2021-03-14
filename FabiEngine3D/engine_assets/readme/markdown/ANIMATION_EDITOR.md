# Animation Editor
![animation_editor](../images/animation_editor.png)
![frame_editor](../images/frame_editor.png)
### General
- You can **create/edit/delete** animations for **models**.
- Every created animation can be applied to models through **scripting**.
- You can select a **preview model** for the animation playback.
- An animation consists of 1 or more **keyframes**.
- You can **create/edit/delete** keyframes to make a full animation.
### Keyframes
- The first keyframe is always the default model transformation.
- Every keyframe has a different **target** transformation.
- Every keyframe has a different animation **speed**, with 2 types to choose from: **linear & exponential**.
- Rotational transformations can each have a different **rotation origin**.
- If the model has **multiple parts**, each part has its own transformation every keyframe.
- The **last** animation keyframe should be the same as the **initial** frame, for a full animation.
