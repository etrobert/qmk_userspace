#pragma once

// Home-row-mod tuning (PLAN step 2). Starting point — adjust by feel.

// How long a home-row key must be held before it registers as a modifier
// instead of its letter. Lower = mods trigger sooner (more accidental mods);
// higher = more hold delay (more accidental letters). 200ms is a common
// middle-ground starting value.
#define TAPPING_TERM 200

// Resolve a mod-tap as HOLD as soon as another key is pressed *and released*
// inside the tapping term. Makes fast rolls into modified chords (e.g. hold-F
// then tap a letter) register reliably without waiting out the full term.
#define PERMISSIVE_HOLD

// Disable the "tap-then-hold to auto-repeat" shortcut on mod-taps: after
// tapping a letter, holding the same key again immediately acts as a HOLD
// (modifier) rather than repeating the letter. Avoids surprise mods when
// double-tapping home-row keys quickly.
#define QUICK_TAP_TERM 0
