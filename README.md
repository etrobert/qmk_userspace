# qmk_userspace

QMK external userspace for an **Input Club Infinity ErgoDox** — a trial to
decide whether a columnar split (ultimately a Corne) suits me. See
[PLAN.md](PLAN.md) for the rationale and the experiment.

## Keymap

[`soft`](keyboards/input_club/ergodox_infinity/keymaps/soft/keymap.c) — a
deliberately conservative starting point: standard QWERTY, real modifiers on the
thumb clusters, and one symbol/navigation layer (`NAV`) held via the left big
thumb. No home-row mods yet; features are added one at a time so each change's
effect stays legible.

## Build

```sh
nix build          # pinned, reproducible -> result/*.{hex,bin}
```

Or, inside the devshell, the faster incremental loop:

```sh
qmk compile -kb input_club/ergodox_infinity -km soft
```

## Flash

Each half has its own MCU and is flashed separately over DFU. Per half: connect
it to USB, press the program button (the half turns red), then:

```sh
sudo dfu-util -d 1c11:b007 -D result/input_club_ergodox_infinity_soft.bin
```

## Reference

Upstream QMK ships keymaps for this board that are worth mining for later steps
(home-row mods, symbol-layer arrangements):
[`input_club/ergodox_infinity`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/input_club/ergodox_infinity/keymaps)
— `default`, `halfkeyboard`, `input_club`. `soft` is an original layout, not
derived from these; it only borrows the `LAYOUT_ergodox` key ordering.
