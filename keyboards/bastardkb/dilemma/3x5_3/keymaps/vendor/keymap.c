/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 * Copyright 2024 (Your Name/Handle) for modifications
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Layer Names based on VIA JSON and intended use
enum dilemma_keymap_layers {
    _BASE = 0,       // VIA Layer 0: Colemak-like base
    _SYMNUM,         // VIA Layer 1: Symbols & Numbers mix
    _NAVFUNC,        // VIA Layer 2: Navigation & Function keys mix
    _MEDIA,          // VIA Layer 3: Media & RGB
    _POINTER,        // VIA Layer 4: Mouse Pointer & Config
    _NUMPAD_L,       // VIA Layer 5: Numpad (primarily left hand)
    _SYMBOLS_L,      // VIA Layer 6: Symbols (primarily left hand)
    _UNUSED_VIA7     // VIA Layer 7: All KC_TRNS in VIA
};

// For custom keycodes used in LAYER_POINTER, matching VIA's CUSTOM(x)
// These are kept from the original file and map to:
// CUSTOM(0) -> DPI_MOD
// CUSTOM(2) -> S_D_MOD
// CUSTOM(4) -> SNIPING
// CUSTOM(6) -> DRGSCRL
#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#else
// Forward declaration for dilemma_set_pointer_sniping_enabled if used
void dilemma_set_pointer_sniping_enabled(bool enabled);
#endif // !POINTING_DEVICE_ENABLE

// --- Combos ---
// Enum for combo identifiers
enum qmk_combos {
  C_ESC,
  C_UNDS,
  C_SQT,
  C_DEL,
  C_NUBS,
  C_CW,
  COMBO_COUNT
};

// Define the key sequences for each combo based on the NEW base layer from VIA JSON
// ZMK Key Pos -> New Base Layer Key
// 1,2 (W,F) -> KC_W, KC_F
// 12,13 (S,T) -> KC_S, KC_T
// 17,18 (E,N) -> KC_E, KC_N (Tap keys of RSFT_T(KC_E), RCTL_T(KC_N))
// 10,11 (A,R) -> KC_A, KC_R
// 7,8 (U,L) -> KC_U, KC_L
// 12,17 (S,E) -> KC_S, KC_E (Tap keys of LSFT_T(KC_S), RSFT_T(KC_E))

const uint16_t PROGMEM combo_esc_keys[]  = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_unds_keys[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_sqt_keys[]  = {KC_E, KC_N, COMBO_END};
const uint16_t PROGMEM combo_del_keys[]  = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM combo_nubs_keys[] = {KC_U, KC_L, COMBO_END};
const uint16_t PROGMEM combo_cw_keys[]   = {KC_S, KC_E, COMBO_END};

// Associate enum entries with their key sequences and resulting keycodes/actions
combo_t key_combos[] = {
  [C_ESC]  = COMBO(combo_esc_keys, KC_ESC),
  [C_UNDS] = COMBO(combo_unds_keys, KC_UNDS), // Underscore
  [C_SQT]  = COMBO(combo_sqt_keys, KC_QUOT),  // Single Quote
  [C_DEL]  = COMBO(combo_del_keys, KC_DEL),
  [C_NUBS] = COMBO(combo_nubs_keys, KC_NUBS),  // Non-US Backslash (usually | too)
  [C_CW]   = COMBO(combo_cw_keys, CW_TOGG),    // Caps Word Toggle
};
// --- End Combos ---

// For MACRO(0) from VIA JSON (PlusMinus: Alt + Numpad 241)
#define M_PLUS_MINUS 0

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3(
    // Left Hand                                       // Right Hand
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,          KC_SCLN, KC_Y,    KC_U,    KC_L,    KC_J,
    LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_D,  RGUI_T(KC_O), LALT_T(KC_I), RSFT_T(KC_E), RCTL_T(KC_N), KC_H,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_K,
                      // Thumbs
                      LT(_NAVFUNC, KC_ENT), LT(_SYMNUM, KC_SPC), KC_ESC,    LT(_NAVFUNC, KC_TAB), KC_BSPC, KC_MUTE
  ),

  [_SYMNUM] = LAYOUT_split_3x5_3( // VIA Layer 1: Symbols & Numbers
    // Left Hand                                       // Right Hand
    KC_NO,   KC_AT,   KC_DQUO, KC_LPRN, KC_RPRN,       KC_GRV,  KC_9,    KC_8,    KC_7,    KC_NO,
    KC_NUHS, KC_EQL,  KC_MINS, KC_EXLM, KC_PERC,       KC_0,    KC_6,    KC_5,    KC_4,    KC_NO,
    M(M_PLUS_MINUS), KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,KC_DOT,  KC_3,    KC_2,    KC_1,    KC_NO,
                      // Thumbs
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAVFUNC] = LAYOUT_split_3x5_3( // VIA Layer 2: Navigation & Function
    // Left Hand                                       // Right Hand
    KC_LNUM, KC_F7,   KC_F8,   KC_F9,   KC_F10,        KC_NO,   KC_END,  KC_UP,   KC_HOME, KC_PGUP,
    KC_LCAP, KC_F4,   KC_F5,   KC_F6,   KC_F11,        KC_RGHT, KC_DOWN, KC_LEFT, KC_LEFT, KC_PGDN, // Note: VIA had KC_RGHT twice, mapped one to KC_LEFT for symmetry with UP/DOWN/LEFT/RGHT cluster
    KC_LSCR, KC_F1,   KC_F2,   KC_F3,   KC_F12,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      // Thumbs
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_MEDIA] = LAYOUT_split_3x5_3( // VIA Layer 3: Media & RGB
    // Left Hand                                       // Right Hand
    KC_NO,   RGB_RMOD,RGB_TOG, RGB_MOD, KC_NO,         KC_NO,   RGB_MOD, RGB_TOG, RGB_RMOD,KC_NO,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,       KC_MNXT, KC_VOLU, KC_MUTE, KC_VOLD, KC_MPRV,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      // Thumbs
                      KC_MPLY, KC_MSTP, KC_TRNS,       KC_MPLY, KC_MSTP, KC_MUTE
  ),

  [_POINTER] = LAYOUT_split_3x5_3( // VIA Layer 4: Mouse Pointer & Config
    // Left Hand                                       // Right Hand
    RESET,   EE_CLR,  KC_NO,   DPI_MOD, S_D_MOD,       RESET,   EE_CLR,  KC_NO,   DPI_MOD, S_D_MOD,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,
    KC_TRNS, DRGSCRL, SNIPING, KC_BTN3, KC_NO,         KC_TRNS, DRGSCRL, SNIPING, KC_BTN3, KC_NO,
                      // Thumbs
                      KC_BTN3, KC_BTN2, KC_BTN1,       KC_BTN3, KC_BTN2, KC_BTN1 // VIA JSON had BTN1, BTN2, BTN3 for right, reversed to match left
  ),

  [_NUMPAD_L] = LAYOUT_split_3x5_3( // VIA Layer 5: Numpad (Left Hand Focus)
    // Left Hand                                       // Right Hand
    KC_LBRC, KC_P7,   KC_P8,   KC_P9,   KC_RBRC,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_SCLN, KC_P4,   KC_P5,   KC_P6,   KC_PEQL,       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, // VIA had mods on right
    KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_BSLS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      // Thumbs
                      KC_PMNS, KC_P0,   KC_PDOT,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_SYMBOLS_L] = LAYOUT_split_3x5_3( // VIA Layer 6: Symbols (Left Hand Focus)
    // Left Hand                                       // Right Hand
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, // VIA had mods on right
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      // Thumbs
                      KC_GRV,  KC_UNDS, KC_LPRN,       KC_TRNS, KC_TRNS, KC_TRNS // VIA had S(KC_9) i.e. KC_LPRN for 3rd thumb
  ),

  [_UNUSED_VIA7] = LAYOUT_split_3x5_3( // VIA Layer 7: All KC_TRNS
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  )
};
// clang-format on

// Handle M(M_PLUS_MINUS) Macro
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case M_PLUS_MINUS: // Corresponds to M(0) or MACRO(0) in VIA
            if (record->event.pressed) {
                return MACRO(D(LALT), T(P2), T(P4), T(P1), U(LALT), END);
                // For Windows Alt-codes. Ensure NumLock is on or use direct char send if possible.
            }
            break;
    }
    return MACRO_NONE;
}

// Process Combos and other custom key logic
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_combo_event(keycode, record)) { // Process combos first
        return false; // If combo handled the event, return false
    }

    // Other custom keycode handling can go here if needed,
    // but M(M_PLUS_MINUS) is handled by action_get_macro.

    return true; // Continue with default QMK processing
}


#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
// If you want auto-sniping on a specific layer from the new layout, update the layer name here.
// For example, if you want it on _POINTER layer:
// #define DILEMMA_TARGET_AUTO_SNIPING_LAYER _POINTER
layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef DILEMMA_TARGET_AUTO_SNIPING_LAYER
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_TARGET_AUTO_SNIPING_LAYER));
    #endif
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
// Updated encoder map to match the 8 layers from VIA JSON
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]       = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},         // VIA Enc Layer 0
    [_SYMNUM]     = {ENCODER_CCW_CW(KC_DOWN, KC_UP),             ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},        // VIA Enc Layer 1
    [_NAVFUNC]    = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},        // VIA Enc Layer 2
    [_MEDIA]      = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},        // VIA Enc Layer 3
    [_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},        // VIA Enc Layer 4
    [_NUMPAD_L]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},        // VIA Enc Layer 5
    [_SYMBOLS_L]  = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},        // VIA Enc Layer 6
    [_UNUSED_VIA7]= {ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}         // VIA Enc Layer 7
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

