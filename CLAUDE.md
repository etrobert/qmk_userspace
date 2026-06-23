# CLAUDE.md — qmk_userspace

## Flashing (tower gotchas)

- Enter the bootloader via the **S49 program button**, reached through a hole in
  the acrylic bottom plate (no need to open the case); the half turns red. It
  then enumerates as `1c11:b007` (Kiibohd DFU bootloader); running QMK it is
  `1c11:b04d`.
- **Tower has a second DFU device** — an Audient iD14 audio interface
  (`2708:0008`). Always pass `-d 1c11:b007` to dfu-util so it targets the
  keyboard's bootloader and never the audio interface:
  `sudo dfu-util -d 1c11:b007 -D result/input_club_ergodox_infinity_soft.bin`
- Needs `sudo` (no udev rule on tower). Each half is flashed separately, each on
  its own USB connection — the inter-half cable is not a flash path.
