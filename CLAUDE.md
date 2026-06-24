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

## Known Hardware Faults

### Left-thumb Left-Ctrl switch is dead (Infinity ErgoDox)

The left-thumb inner-upper key — mapped to `KC_LCTL` in the `soft` keymap,
matrix position `[0,4]` (row pin `B2` × col pin `D7`) — registers **nothing**
(confirmed with `wev`: no event on press).

This is a **hardware fault on that single switch/diode**, not a firmware or
keymap bug. The keymap is correct and symmetric (its mirror `KC_RCTL` at `[9,4]`
works fine). Both matrix lines reaching the key are proven healthy:

- Row `B2` is good — the adjacent LAlt key (`[0,3]`, same row) emits `Alt_L`.
- Col `D7` is good — Home, LSft, Space, and the left under-row keys share that
  column and all work.

So the fault is isolated to the switch or its 1N4148 diode at `[0,4]`. Fix
order: reflow the four joints (2 switch pads + 2 diode pads), then check the
diode in diode mode (~0.5–0.7 V one way, open the other), then replace
switch/diode.

Until repaired, Ctrl is reachable only via the right-thumb `KC_RCTL`. A software
stopgap (remap Ctrl onto a known-good key, or add a home-row Ctrl mod per PLAN
step 2) is possible if needed.
