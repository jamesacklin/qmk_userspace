#include QMK_KEYBOARD_H

extern uint8_t is_master;

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_sethsv(0, 0, 100);
#endif
}

enum custom_keycodes {  
    DEFAULT = SAFE_RANGE,
    LOWER,
    RAISE,
    FUNC,
    MOUSE,
};

enum combos {
  DF_DASH,
  JK_ESC
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  // Add commonly used dash to home row
  [DF_DASH]    = COMBO(df_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),

};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _FUNC   3
#define _MOUSE  4
#define _SHORTCUT  5

// For _QWERTY layer
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define MOU_GUI  LT(_MOUSE, KC_LGUI)
#define OSL_FUN  OSL(_FUNC)
#define OSM_AGR  OSM(MOD_RALT)
#define OSM_ALT  OSM(MOD_LALT)
#define OSM_CTL  OSM(MOD_LCTL)
#define OSM_SFT  OSM(MOD_LSFT)
#define LOW_BSP  LT(_LOWER, KC_BSPC)
#define RSE_ENT  LT(_RAISE, KC_ENT)
#define MOD_TAB  MT(MOD_LALT, KC_TAB)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       MOD_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_ESC  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      OSM_CTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       MO(_LOWER), KC_LGUI, KC_BSPC,   KC_ENT  ,KC_SPC  , MO(_RAISE)
                                    //`----------------------------'  `-----------------------------'
  ),

[_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
  ),

[_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , KC_COPY, KC_PSTE, KC_SCLN,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),

[_FUNC] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
                                      //`--------------------------'  `--------------------------'
  ),

// There's no keybinding to activate the mouse layer yet!
[_MOUSE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),
  
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      case LT(_MOUSE, KC_LGUI):
            return TAPPING_TERM_THUMB;
      case LT(_SHORTCUT, OSM_SFT):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  
    return rotation;
}

bool oled_task_user(){
    static const char htid [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x1c, 0x1e, 0x3e, 0x0c, 0x1e, 0x3e, 0x0c, 
        0x00, 0x00, 0x0f, 0x10, 0xbf, 0x63, 0x0e, 0xfc, 0x00, 0x00, 0xf1, 0xf1, 0xbf, 0xbf, 0x31, 0x21, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x90, 0x40, 0x28, 0xe8, 0x10, 0x20, 0xc0, 
        0x00, 0x70, 0x0c, 0xe2, 0x19, 0x04, 0x02, 0x01, 0x01, 0x02, 0x7c, 0xff, 0xfd, 0x7f, 0xf7, 0xf2, 
        0x30, 0x28, 0x28, 0x14, 0x12, 0x09, 0x04, 0x02, 0xff, 0x04, 0xf8, 0x00, 0xff, 0x00, 0x00, 0xff, 
        0x00, 0x00, 0x03, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfb, 0x1f, 0x1e, 0xff, 0xf3, 
        0x81, 0x42, 0x44, 0x4c, 0x58, 0x70, 0xe0, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00, 0x00, 0xff, 
        0x03, 0x02, 0x06, 0x04, 0x0c, 0x0c, 0x0c, 0x08, 0x0a, 0x0a, 0xfb, 0xf9, 0x8d, 0x8c, 0xfc, 0x7a, 
        0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0xff, 0x06, 0xff, 0x18, 0x20, 0xc1, 0x03, 0x01, 
        0x08, 0x10, 0x10, 0x30, 0x20, 0x20, 0x30, 0x10, 0x10, 0x20, 0xef, 0xeb, 0xe1, 0xf5, 0xf7, 0xc2, 
        0x0a, 0x18, 0x35, 0x65, 0xc5, 0x82, 0x02, 0x02, 0xfe, 0x00, 0xff, 0x02, 0x02, 0xc5, 0x1f, 0xf8, 
        0x00, 0x00, 0xfe, 0x02, 0xfc, 0x0c, 0x58, 0xe0, 0x00, 0x00, 0xfc, 0xf7, 0xff, 0xfc, 0xff, 0xc3, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x87, 0xc8, 0x5f, 0x30, 0x06, 0x60, 0x8c, 0x01, 
        0x00, 0x00, 0x03, 0x04, 0xcf, 0x38, 0xc0, 0x3f, 0x00, 0x00, 0xc3, 0xc1, 0xc1, 0xc1, 0xf3, 0xe1, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x01, 0x00, 0x1f, 0x7c, 0xfe, 0x80, 0x80, 0xfe, 
        0x08, 0x10, 0xfc, 0x63, 0xf8, 0xe6, 0x61, 0x60, 0x50, 0x50, 0xdc, 0xec, 0x2c, 0x24, 0x37, 0x17, 
        0x02, 0x0a, 0x0a, 0x05, 0x05, 0x05, 0x01, 0x13, 0x93, 0x5b, 0x3a, 0xb2, 0xb4, 0x2c, 0x59, 0x9f, 
        0x00, 0x00, 0x7f, 0xc0, 0xff, 0xc1, 0x03, 0xfe, 0x04, 0x08, 0x99, 0xb8, 0xd8, 0xd8, 0xd8, 0xd0, 
        0x80, 0xa0, 0x90, 0x48, 0xe8, 0x24, 0x1a, 0x09, 0x04, 0x02, 0x01, 0x00, 0xff, 0x00, 0x00, 0xff, 
        0x00, 0x00, 0x80, 0x60, 0x18, 0xc7, 0x38, 0x07, 0x00, 0x00, 0xdf, 0xff, 0xf1, 0xf1, 0xff, 0xcf, 
        0x40, 0x40, 0x20, 0xa0, 0xa0, 0xa1, 0x63, 0x66, 0x6c, 0x78, 0x70, 0x60, 0xff, 0x80, 0x00, 0xff, 
        0x01, 0x02, 0x07, 0x04, 0x07, 0x0c, 0x0c, 0x0a, 0x0a, 0x0a, 0x3d, 0x1d, 0x1d, 0x1e, 0x3e, 0x1e, 
        0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0x81, 0x81, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(htid, sizeof(htid));
    
    return false;
}

#endif


