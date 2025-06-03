/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 * Copyright 2024 (Your Name/Handle) for modifications
 */

#include QMK_KEYBOARD_H

// Layer Names based on VIA JSON and intended use
enum dilemma_keymap_layers {
    _BASE = 0,
    _SYMNUM,
    _NAVFUNC,
    _MEDIA,
    _POINTER,
    _NUMPAD_L,
    _SYMBOLS_L,
    _UNUSED_VIA7,
};

// --- Home Row Mod Aliases for Combos ---
// Left Hand
#define HM_A LGUI_T(KC_A)
#define HM_R LALT_T(KC_R)
#define HM_S LSFT_T(KC_S)
#define HM_T LCTL_T(KC_T)
// Right Hand
#define HM_O RGUI_T(KC_O)
#define HM_I LALT_T(KC_I)
#define HM_E RSFT_T(KC_E)
#define HM_N RCTL_T(KC_N)

// For custom keycodes used in LAYER_POINTER, matching VIA's CUSTOM(x)
#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#else
void dilemma_set_pointer_sniping_enabled(bool enabled);
#endif

// --- Combos ---
enum qmk_combos {
  // Existing
  C_ESC,
  C_UNDS,
  C_SQT,
  C_DEL,
  C_NUBS,
  C_CW,
  // New Brackets
  C_LPRN, // (
  C_RPRN, // )
  C_LBRC, // [
  C_RBRC, // ]
  C_LCBR, // {
  C_RCBR, // }
  COMBO_COUNT
};

// Existing combo key definitions
const uint16_t PROGMEM combo_esc_keys[]  = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_unds_keys[] = {HM_S, HM_T, COMBO_END};
const uint16_t PROGMEM combo_sqt_keys[]  = {HM_E, HM_I, COMBO_END}; // Tap of RSFT_T(E), RCTL_T(N)
const uint16_t PROGMEM combo_del_keys[]  = {HM_A, HM_R, COMBO_END}; // Tap of LGUI_T(A), LALT_T(R)
const uint16_t PROGMEM combo_nubs_keys[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_cw_keys[]   = {HM_S, HM_E, COMBO_END}; // Tap of LSFT_T(S), RSFT_T(E)

// New Bracket combo key definitions
const uint16_t PROGMEM combo_lprn_keys[] = {KC_F, KC_P, COMBO_END};    // (
const uint16_t PROGMEM combo_rprn_keys[] = {KC_P, KC_G, COMBO_END};    // )
const uint16_t PROGMEM combo_lbrc_keys[] = {KC_Z, KC_X, COMBO_END};    // [
const uint16_t PROGMEM combo_rbrc_keys[] = {KC_X, KC_C, COMBO_END};    // ]
const uint16_t PROGMEM combo_lcbr_keys[] = {KC_C, KC_V, COMBO_END};    // {
const uint16_t PROGMEM combo_rcbr_keys[] = {KC_V, KC_B, COMBO_END};    // }


combo_t key_combos[] = {
  // Existing
  [C_ESC]  = COMBO(combo_esc_keys, KC_ESC),
  [C_UNDS] = COMBO(combo_unds_keys, KC_UNDS),
  [C_SQT]  = COMBO(combo_sqt_keys, KC_QUOT),
  [C_DEL]  = COMBO(combo_del_keys, KC_DEL),
  [C_NUBS] = COMBO(combo_nubs_keys, KC_NUBS),
  [C_CW]   = COMBO(combo_cw_keys, CW_TOGG),
  // New Brackets
  [C_LPRN] = COMBO(combo_lprn_keys, KC_LPRN), // Shift + 9
  [C_RPRN] = COMBO(combo_rprn_keys, KC_RPRN), // Shift + 0
  [C_LBRC] = COMBO(combo_lbrc_keys, KC_LBRC), // [
  [C_RBRC] = COMBO(combo_rbrc_keys, KC_RBRC), // ]
  [C_LCBR] = COMBO(combo_lcbr_keys, KC_LCBR), // Shift + [
  [C_RCBR] = COMBO(combo_rcbr_keys, KC_RCBR), // Shift + ]

};

// --- End Combos ---

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3(
    // Left Hand                                       // Right Hand
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,          KC_J, KC_L, KC_U, KC_Y, KC_SCLN,
    HM_A,    HM_R,    HM_S,    HM_T,    KC_D,          KC_H, HM_N,    HM_E,    HM_I,    HM_O,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_K, KC_M,  KC_COMM, KC_DOT,    KC_SLSH, 
    KC_ESC, LT(_NAVFUNC, KC_ENT), LT(_SYMNUM, KC_SPC),    KC_BSPC, LT(_NAVFUNC, KC_TAB), KC_MUTE
  ),

  [_SYMNUM] = LAYOUT_split_3x5_3(
    KC_NO,   KC_AT,   KC_DQUO, KC_LPRN, KC_RPRN,       KC_GRV,  KC_9,    KC_8,    KC_7,    KC_NO,
    KC_NUHS, KC_EQL,  KC_MINS, KC_EXLM, KC_PERC,       KC_0,    KC_6,    KC_5,    KC_4,    KC_NO,
    KC_NO,   KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,       KC_DOT,  KC_3,    KC_2,    KC_1,    KC_NO,
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAVFUNC] = LAYOUT_split_3x5_3(
    KC_LNUM, KC_F7,   KC_F8,   KC_F9,   KC_F10,        KC_NO,   KC_END,  KC_UP,   KC_HOME, KC_PGUP,
    KC_LCAP, KC_F4,   KC_F5,   KC_F6,   KC_F11,        KC_RGHT, KC_DOWN, KC_LEFT, KC_LEFT, KC_PGDN,
    KC_LSCR, KC_F1,   KC_F2,   KC_F3,   KC_F12,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_MEDIA] = LAYOUT_split_3x5_3(
    KC_NO,   RGB_RMOD,RGB_TOG, RGB_MOD, KC_NO,         KC_NO,   RGB_MOD, RGB_TOG, RGB_RMOD,KC_NO,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,       KC_MNXT, KC_VOLU, KC_MUTE, KC_VOLD, KC_MPRV,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_MPLY, KC_MSTP, KC_TRNS,       KC_MPLY, KC_MSTP, KC_MUTE
  ),

  [_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT, EE_CLR,  KC_NO,   DPI_MOD, S_D_MOD,       QK_BOOT, EE_CLR,  KC_NO,   DPI_MOD, S_D_MOD,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,
    KC_TRNS, DRGSCRL, SNIPING, KC_BTN3, KC_NO,         KC_TRNS, DRGSCRL, SNIPING, KC_BTN3, KC_NO,
                      KC_BTN3, KC_BTN2, KC_BTN1,       KC_BTN1, KC_BTN2, KC_BTN3
  ),

  [_NUMPAD_L] = LAYOUT_split_3x5_3(
    KC_LBRC, KC_P7,   KC_P8,   KC_P9,   KC_RBRC,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_SCLN, KC_P4,   KC_P5,   KC_P6,   KC_PEQL,       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS,
    KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_BSLS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      KC_PMNS, KC_P0,   KC_PDOT,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_SYMBOLS_L] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      KC_GRV,  KC_UNDS, KC_LPRN,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_UNUSED_VIA7] = LAYOUT_split_3x5_3(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  )
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef DILEMMA_TARGET_AUTO_SNIPING_LAYER
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_TARGET_AUTO_SNIPING_LAYER));
    #endif
    return state;
}
#    endif
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]       = {ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_SYMNUM]     = {ENCODER_CCW_CW(KC_DOWN, KC_UP),             ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [_NAVFUNC]    = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [_MEDIA]      = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [_NUMPAD_L]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [_SYMBOLS_L]  = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [_UNUSED_VIA7]= {ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};
#endif