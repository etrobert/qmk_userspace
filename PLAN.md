# Plan — Infinity ErgoDox split-keyboard trial

## Objective

Use a **borrowed Input Club Infinity ErgoDox** to decide whether a **Corne**
(42-key split) would suit me — testing both the split/columnar **form factor**
and the **programmable-keyboard configuration** experience.

The ErgoDox is a _proxy_ for the Corne decision, not the end goal. The friend
who lent it is fine with wiping its current firmware.

## Hardware facts

- Two halves, each a Kinetis **`mk20dx256`** MCU, **flashed separately** over
  DFU.
- Ships with Input Club's **Kiibohd/KLL** firmware; the modern path is **QMK**
  (`keyboards/input_club/ergodox_infinity`).
- Has small per-half **LCD screens** and white backlight — ignored for this
  trial (QMK's LCD support is fiddly and irrelevant to the verdict).
- **No turnkey VIA and no Vial port** for this board: mainline QMK ships only
  `default`, `halfkeyboard`, `input_club` keymaps (no `via` target), and the
  dual-MCU + LCD Infinity isn't a standard Vial board. Live GUI remapping would
  require porting it myself.

## Decisions

| Area              | Decision                                                                    | Why                                                                                            |
| ----------------- | --------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| Firmware          | **QMK**, wiping KLL                                                         | Modern, the real programmable-split experience; friend OK'd wipe                               |
| Iteration         | **Plain QMK, C keymap, compile + `dfu-util` flash**                         | No VIA/Vial for this board; HRM tuning lives in QMK config anyway; ~30s loop                   |
| Config home       | **This repo** (`qmk_userspace`), external-userspace layout, own `flake.nix` | Version-controls the feature-by-feature evolution; future Corne drops in as another keymap dir |
| Base layout       | **QWERTY**                                                                  | Isolates the form-factor variable; keeps daily Mac-keyboard switching survivable               |
| Keymap aggression | **Conservative start**, add features one at a time                          | Honest read on the split before the adaptation curve is poisoned                               |

### Repo naming

Named `qmk_userspace` (snake_case) — the canonical QMK external-userspace
template name and the overwhelming community convention; the QMK userspace
tooling / GitHub Actions expect it. This deliberately overrides the usual
kebab-case directory preference, because ecosystem recognizability wins for a
public repo.

## Keymap progression

Start minimal, add **one feature at a time** so each change's effect is legible:

1. QWERTY alphas in normal positions; real mod keys on the **thumb clusters**
   (the ErgoDox's actual selling point); one symbol/nav layer via a thumb.
2. Home-row mods (tune `TAPPING_TERM`, permissive hold, etc.).
3. More layers.
4. Combos.

## The experiment

- **Commitment:** ErgoDox for **everything on tower, zero exceptions, however
  slow.** Mac laptop keyboard is unavoidable for mobile work, so this is
  _partial_ cold-turkey — adaptation will be slower because of the constant
  row-stagger ↔ columnar switching.
- **Physical setup:** halves **spread to shoulder width, flat** (no tenting
  hardware). DIY tenting risers — binder clips / Lego / 3D-printed — are an
  optional later upgrade that meaningfully improves the wrist angle.
- **Verdict:** open-ended / vibes.
- **Guardrail (against drifting to an undecided hand-back):** a ~2-line weekly
  note in `~/sync/doc` — speed? pain? dread plugging it in?

## Deferred / open

- **42-key Corne-constraint phase** (decide later). ⚠️ This is the _only_ phase
  that truly answers the Corne question: a full ErgoDox (~76 keys, generous
  6-key thumb clusters) does **not** test whether 42 keys forcing layers + HRM
  is enough. End state: ignore the outer columns + extra thumb keys and live on
  the inner 3×6+3 that mirror a Corne. Flagged so it doesn't quietly never
  happen.
- LCD screens / backlight — ignored for now.

## Flashing reference

Per half: hold the program button (back of the board, above the thumb pad), then
flash. With this userspace + QMK:

```sh
qmk compile -kb input_club/ergodox_infinity -km <keymap>
# plug in / program one half, flash, then repeat for the other half
qmk flash   -kb input_club/ergodox_infinity -km <keymap>
```

(`qmk` + `dfu-util` provided by this repo's `flake.nix` devshell.)
