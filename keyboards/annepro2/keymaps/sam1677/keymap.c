#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"

#ifdef ANNEPRO2_C18
#   include "eeprom_w25x20cl.h"
#endif

typedef struct {
    uint8_t  magic : 8;
    bool    led_is_on : 1;
    uint8_t led_profile : 8;
} Settings;

Settings settings = {.magic = 0XEA, .led_is_on = TRUE, .led_profile = 0};


enum custom_keys {
    KC_AP2_LED_TOGGLE = AP2_SAFE_RANGE,
};

enum anne_pro_layers {
  _BASE_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _SHIFT_LAYER,
};

// clang-format off
// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Ctrl    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Fn2  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  Caps  |  Del  |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    LM(_SHIFT_LAYER, KC_LSHIFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    MO(_FN2_LAYER), KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_FN1_LAYER), KC_CAPS, KC_DEL
),
  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |  a  |  s  |  d  |  f  |  g  |LEFT |DOWN | UP  |RIGHT|PGUP |PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | FN2  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  CAPS  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_HOME, KC_END, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_PGUP, KC_PGDN, _______,
    _______, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______, KC_INS, KC_DEL, _______,
    MO(_FN2_LAYER), _______, _______, _______, _______, _______, _______, _______
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |  F8 |LEDMD|LEDP |BRDN |BRUP |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |  a  |  s  |  d  |  f  |  g  |LEFT |DOWN | UP  |RIGHT|PGUP |PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DN |MUTE |  z  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | FN2  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  CAPS  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    _______, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_HOME, KC_END, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_PGUP, KC_PGDN, _______,
    _______, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______, KC_INS, KC_DEL, _______,
    MO(_FN2_LAYER), _______, _______, _______, _______, MO(_FN1_LAYER), _______, _______
 ),
   /*
  * Layer _SHIFT_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |  F8 |LEDMD|LEDP |BRDN |BRUP |    DEL    |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  "  |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | FN2  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  CAPS  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_SHIFT_LAYER] = KEYMAP( /* Base */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    MO(_FN2_LAYER), _______, _______, _______, _______, MO(_FN1_LAYER), _______, _______
 ),
};
// clang-format on

const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

void save_settings() {
    eeprom_write((void *)&settings, 0, sizeof(Settings));
}

void init_settings() {
    eeprom_read((void *)&settings, 0, sizeof(Settings));

    if(settings.magic != 0xEA) {
        settings.magic = 0xEA;
        settings.led_is_on = TRUE;
        settings.led_profile = 0;
        eeprom_write((void *)&settings, 0, sizeof(Settings));
    }
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    init_eeprom();

    if (settings.led_is_on) annepro2LedEnable();

    annepro2LedSetProfile(settings.led_profile);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_AP2_LED_TOGGLE:
            if (record->event.pressed) {
                if (settings.led_is_on) {
                    annepro2LedDisable();
                    settings.led_is_on = false;
                    save_settings();
                } else {
                    annepro2LedEnable();
                    settings.led_is_on = true;
                }
            }

            return false;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    // Set the leds to red
    annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);
  } else {
    annepro2LedResetForegroundColor();
  }

  return true;
}
