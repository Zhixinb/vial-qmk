/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "env.h"
// TODO:
// light for while recording macro (red) and while running (green/white): https://www.reddit.com/r/MechanicalKeyboards/comments/f4mk5t/qmk_docsexamples_on_blinking_led_during_dynamic/
// MO3 toggle layer with MO0 for Windows/Mac layout switch (modifer switch, macros from mac -> win), slowly remove Karbiner, Mac shortcut, switched mod layouts
// refactor each feature into own file with include
// upgrade VIAL with merging from flytiger branch (be careful, might brick device, baseline with basic keymap first)
enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

enum custom_keycodes { RGB_STA = SAFE_RANGE, RGB_GRA, RGB_CYC, RGB_MSK, KC_00, KC_WINLCK, CKC_EMAIL, CKC_HIBERNATE, CKC_PIN, CKC_WUP, CKC_WLFT, CKC_DWN, CKC_RGT, CKC_DELL };

// Combos
enum combo_events {
  GIT_STATUS,
  GIT_ADD,
  GIT_CMT,
  GIT_PUSH,
  GIT_SWTCH,
  GIT_BRCH,
  GIT_CHKOUT,
  GIT_AMND,
  GIT_REBASE,
  GIT_ADOG,
  B_C,
  B_R,
  B_C_R,
  B_W_S,
  COMBO_LENGTH
};

const uint16_t PROGMEM git_status_combo[] = {KC_G, KC_S, COMBO_END};
const uint16_t PROGMEM git_add_combo[] = {KC_G, KC_A, COMBO_END};
const uint16_t PROGMEM git_comment_combo[] = {KC_G, KC_C, COMBO_END};
const uint16_t PROGMEM git_push_combo[] = {KC_G, KC_P, COMBO_END};
const uint16_t PROGMEM git_swtch_combo[] = {KC_G, KC_W, COMBO_END};
const uint16_t PROGMEM git_brch_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM git_chkout_combo[] = {KC_G, KC_K, COMBO_END};
const uint16_t PROGMEM git_amnd_combo[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM git_rebase_combo[] = {KC_G, KC_R, COMBO_END};
const uint16_t PROGMEM git_adog_combo[] = {KC_G, KC_L, COMBO_END};
const uint16_t PROGMEM b_c_combo[] = {KC_B, KC_C, COMBO_END};
const uint16_t PROGMEM b_r_combo[] = {KC_B, KC_R, COMBO_END};
const uint16_t PROGMEM b_c_r_combo[] = {KC_B, KC_ENT, COMBO_END};
const uint16_t PROGMEM b_w_s_combo[] = {KC_B, KC_W, COMBO_END};
combo_t key_combos[] = {
  [GIT_STATUS] = COMBO_ACTION(git_status_combo),
  [GIT_ADD] = COMBO_ACTION(git_add_combo),
  [GIT_CMT] = COMBO_ACTION(git_comment_combo),
  [GIT_PUSH] = COMBO_ACTION(git_push_combo),
  [GIT_SWTCH] = COMBO_ACTION(git_swtch_combo),
  [GIT_BRCH] = COMBO_ACTION(git_brch_combo),
  [GIT_CHKOUT] = COMBO_ACTION(git_chkout_combo),
  [GIT_AMND] = COMBO_ACTION(git_amnd_combo),
  [GIT_REBASE] = COMBO_ACTION(git_rebase_combo),
  [GIT_ADOG] = COMBO_ACTION(git_adog_combo),
  [B_C] = COMBO_ACTION(b_c_combo),
  [B_R] = COMBO_ACTION(b_r_combo),
  [B_C_R] = COMBO_ACTION(b_c_r_combo),
  [B_W_S] = COMBO_ACTION(b_w_s_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case GIT_STATUS:
      if (pressed) {
        SEND_STRING("git status");    
      }
      break;
    case GIT_ADD:
      if (pressed) {
        SEND_STRING("git add ");    
      }
      break;
    case GIT_CMT:
      if (pressed) {
        SEND_STRING("git commit -m \"\""SS_TAP(X_LEFT));    
      }
      break;
    case GIT_PUSH:
      if (pressed) {
        SEND_STRING("git push ");    
      }
      break;
    case GIT_SWTCH:
      if (pressed) {
        SEND_STRING("git switch ");    
      }
      break;
    case GIT_BRCH:
      if (pressed) {
        SEND_STRING("git branch");    
      }
      break;
    case GIT_CHKOUT:
      if (pressed) {
        SEND_STRING("git checkout -b ");    
      }
      break;
    case GIT_AMND:
      if (pressed) {
        SEND_STRING("git commit --amend");    
      }
      break;
    case GIT_REBASE:
      if (pressed) {
        SEND_STRING("git rebase -i ");    
      }
      break;      
    case GIT_ADOG:
      if (pressed) {
        SEND_STRING("git log --all --decorate --oneline --graph");    
      }
      break;                    
    case B_C:
      if (pressed) {
        SEND_STRING(CLEAN_STRING);    
      }
      break;
    case B_R:
      if (pressed) {
        SEND_STRING(RELEASE_STRING);    
      }
      break;
    case B_C_R:
      if (pressed) {
        SEND_STRING(CLEAN_RELEASE_STRING);    
      }
      break;
    case B_W_S:
      if (pressed) {
        SEND_STRING(BWS_STRING);    
      }
      break;  
  }
}



// Leader Key 
LEADER_EXTERNS();
void matrix_scan_user(void) {  
    LEADER_DICTIONARY() {    
        leading = false;    
        leader_end();    
        
    }
}

bool _isLeaderOn = false;

void leader_start(void) {  
    // sequence started
    _isLeaderOn = true;
}
void leader_end(void) {  
    // sequence ended (no success/failure detection)
    _isLeaderOn = false;
}


// Tap Dance Definitions
enum custom_tapdance {
    TD_SLSH_MO,
    TD_HOME_MO,
    TD_LEFT_MO,
    TD_RIGHT_MO,
};

void slsh(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        SEND_STRING(SS_LCTL("/")); // hold
    } else {
        for (uint8_t i = 0; i < state->count; i++) {
            SEND_STRING("/");
        }
    }
}

enum { REST, HOLD1 , HOLD2};
static int Shift1 = REST;
static int Shift2 = REST;
void left(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                register_code(KC_LSFT); // left shift hold
                Shift1 = HOLD1;
            } else {
                tap_code16(S(KC_9)); // ( tap
            }
            break;
        case 2:
            if (state->pressed) {
                tap_code(KC_LBRACKET); // [ gold
            }
            else {
                tap_code16(S(KC_LBRACKET)); // { tap
            }
            break;
        default:
            reset_tap_dance(state);
    }
}

void right(qk_tap_dance_state_t* state, void* user_data) {
    switch (state->count) {
        case 1:
            if (state->pressed) {
                register_code(KC_RSFT); // right shift hold
                Shift2 = HOLD2;
            }
            else {
                tap_code16(S(KC_0)); // ) tap
            }
            break;
        case 2:
            if (state->pressed) {
                tap_code(KC_RBRACKET); // ] hold
            }
            else {
                tap_code16(S(KC_RBRACKET)); // } tap
            }
            break;
        default:
            reset_tap_dance(state);
    }
}

void shift1_reset (qk_tap_dance_state_t* state, void* user_data) {
    switch (Shift1) {
        case HOLD1:
            unregister_code(KC_LSFT);
            break;
    }
    Shift1 = REST;
}

void shift2_reset (qk_tap_dance_state_t* state, void* user_data) {
    switch (Shift2) {
        case HOLD2:
            unregister_code(KC_RSFT);
            break;
    }
    Shift2 = REST;
}


// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLSH_MO] = ACTION_TAP_DANCE_FN(slsh),
    [TD_HOME_MO] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_MNXT),
    [TD_LEFT_MO]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left, shift1_reset),
    [TD_RIGHT_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right, shift2_reset),
};

#define TD_SLSH TD(TD_SLSH_MO)
#define TD_HOME TD(TD_HOME_MO)
#define TD_LEFT TD(TD_LEFT_MO)
#define TD_RIGHT TD(TD_RIGHT_MO)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_FN1 OSL(_FN1)
#define OSM_MO2 OSL(_MO2)
#define OSM_MO3 OSL(_MO3)

bool _isWinKeyDisabled = false;
bool _isLCtlOsmActived = false;
bool _isLAltOsmActived = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del           Rotary(Mute)
    //      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
    //      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
    //      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
    //      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
    //      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,   KC_DEL,           KC_MPLY, 
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,   KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,   KC_BSPC,          TD_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,  KC_BSLS,          KC_PGUP, 
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,  KC_QUOT,           KC_ENT,           KC_PGDN, 
        TD_LEFT,          KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,   TD_SLSH,           TD_RIGHT, KC_UP,  KC_END, 
        OSM_LCTL,KC_LGUI, OSM_LALT,                            KC_SPC,                            OSM_FN1,  OSM_MO2, OSM_MO3,  KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT(
        RESET,   DM_REC1, DM_REC2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, RGB_HUD, RGB_VAI, RGB_HUI, _______, _______, _______, _______, KC_SLCK, KC_PAUS, KC_PSCR, _______, _______, _______,            _______, 
        _______, RGB_SAD, RGB_VAD, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,          _______,            _______,
        _______,          _______, _______, _______, _______, _______, KC_NLCK, _______, _______, _______, _______,          _______, _______,   _______, 
        _______, KC_WINLCK, _______,                             _______,                         _______, _______, _______, _______, _______, _______),

    [_MO2] = LAYOUT(
        _______, DM_PLY1,   DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______, CKC_EMAIL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CKC_DELL,           _______, 
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CKC_PIN,            _______, 
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, CKC_WUP,   _______, 
        CKC_HIBERNATE, _______, _______,                         _______,                           _______, _______, _______, CKC_WLFT,CKC_DWN,   CKC_RGT),

    [_MO3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEAD, _______,          _______,            _______, 
        _______,          _______, _______, CMB_TOG, _______, _______, _______, _______, _______, _______, _______,          _______, _______,   _______, 
        _______, _______, _______,                             _______,                           _______, _______, _______, _______, _______,   _______),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_STA:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_static);
            }
            return false;  // Skip all further processing of this key
        case RGB_GRA:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_gradient);
            }
            return false;  // Skip all further processing of this key
        case RGB_CYC:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_cycle_all);
            }
            return false;  // Skip all further processing of this key
        case RGB_MSK:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_led_mask_0);
            }
            return false;  // Skip all further processing of this key
        case KC_00:
            if (record->event.pressed) {
                // when keycode KC_00 is pressed
                SEND_STRING("00");
            } else {
                // when keycode KC_00 is released
            }
            return false;  // Skip all further processing of this key
        case KC_WINLCK:
            if (record->event.pressed) {
                _isWinKeyDisabled = !_isWinKeyDisabled;  // toggle status
                if (_isWinKeyDisabled) {
                    process_magic(GUI_OFF, record);
                } else {
                    process_magic(GUI_ON, record);
                }
            } else
                unregister_code16(keycode);
            return false;  // Skip all further processing of this key
        case CKC_EMAIL:
            if (record->event.pressed) {
                SEND_STRING(EMAIL_STRING);
            }
            return false;  // Skip all further processing of this key
        case CKC_HIBERNATE:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("x") SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_RGHT) SS_TAP(X_DOWN) SS_TAP(X_ENT));
            }
            return false;  // Skip all further processing of this key
        case CKC_PIN:
            if (record->event.pressed) {
                SEND_STRING(" " SS_DELAY(200) PIN_STRING SS_TAP(X_ENT));
            }
            return false;  // Skip all further processing of this key
        case CKC_WUP:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_UP) SS_UP(X_LGUI));
            }
            return false;  // Skip all further processing of this key
        case CKC_WLFT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LGUI));
            }
            return false;  // Skip all further processing of this key
        case CKC_DWN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_DOWN) SS_UP(X_LGUI));
            }
            return false;  // Skip all further processing of this key
        case CKC_RGT:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_RGHT) SS_UP(X_LGUI));
            }
            return false;  // Skip all further processing of this key
        case CKC_DELL:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_END));
                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT));
                SEND_STRING(SS_TAP(X_BSPC));
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}

void oneshot_mods_changed_user(uint8_t mods) {  
    if (mods & MOD_MASK_CTRL) {
        _isLCtlOsmActived = true;
    }
    if (mods & MOD_MASK_ALT) {
        _isLAltOsmActived = true;
    }
    if (!mods) {
        _isLCtlOsmActived = false;
        _isLAltOsmActived = false;
    }
}
 
enum custom_layers curr_layer = -1;
#ifdef RGB_MATRIX_ENABLE
// Capslock, Scroll lock and Numlock  indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        rgb_matrix_set_color(LED_L1, RGB_GREEN);
        rgb_matrix_set_color(LED_L2, RGB_GREEN);
    }
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {  // on if NUM lock is OFF
        rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
        rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
    }
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
        rgb_matrix_set_color(LED_L8, RGB_RED);
    }
    if (_isWinKeyDisabled) {
        rgb_matrix_set_color(LED_LGUI, RGB_RED);  // light up Win key when disabled
    }

    if (_isLCtlOsmActived) {
        rgb_matrix_set_color(LED_LCTL, RGB_AZURE);
    }

    if (_isLAltOsmActived) {
        rgb_matrix_set_color(LED_LALT, RGB_AZURE);
    }

    if (_isLeaderOn) {
        rgb_matrix_set_color(LED_SCLN, RGB_RED);
    }

    // Layer lights
    if (layer_state_is(_FN1)) {
        if (curr_layer != _FN1) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_led_mask_1);
            curr_layer = _FN1;
        }

        rgb_matrix_set_color(LED_R1, RGB_RED);
        rgb_matrix_set_color(LED_R2, RGB_RED);
        rgb_matrix_set_color(LED_R3, RGB_RED);
        rgb_matrix_set_color(LED_R4, RGB_RED);
        rgb_matrix_set_color(LED_RALT, RGB_RED);
        rgb_matrix_set_color(LED_ESC, RGB_RED);
    } else if (layer_state_is(_MO2)) {
        if (curr_layer != _MO2) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_led_mask_2);
            curr_layer = _MO2;
        }

        rgb_matrix_set_color(LED_R5, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_R6, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_R7, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_R8, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_FN, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_LCTL, RGB_SPRINGGREEN);
        rgb_matrix_set_color(LED_ENT, RGB_SPRINGGREEN);
    } else if (layer_state_is(_MO3)) {
        if (curr_layer != _MO3) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_led_mask_3);
            curr_layer = _MO3;
        }


        rgb_matrix_set_color(LED_R5, RGB_ORANGE);
        rgb_matrix_set_color(LED_R6, RGB_ORANGE);
        rgb_matrix_set_color(LED_R7, RGB_ORANGE);
        rgb_matrix_set_color(LED_R8, RGB_ORANGE);
        rgb_matrix_set_color(LEB_RCTL, RGB_ORANGE);
        rgb_matrix_set_color(LED_SCLN, RGB_ORANGE);

        if (is_combo_enabled()) {
            rgb_matrix_set_color(LED_C, RGB_ORANGE);
        } else {
            rgb_matrix_set_color(LED_C, RGB_AZURE);
        }

    } else {
        if (curr_layer != _BASE) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_led_mask_0);
            curr_layer = _BASE;
        }
    }

    switch (get_highest_layer(layer_state)) {  // special handling per layer
        case _BASE:
        case _FN1:                             // on Fn layer select what the encoder does when pressed
            // Add RGB Timeout Indicator -- shows 0 to 139 using F row and num row;  larger numbers using 16bit code
            // if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_RED);
            // else if (timeout_threshold < 140) {
            //     rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_RED);
            // } else { // >= 140 minutes, just show these 3 lights
            //     rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_RED);
            // }
            break;
        case _MO2:  // Numpad layer
            // for (uint8_t i = 0; i < sizeof(LED_LIST_NUMPAD) / sizeof(LED_LIST_NUMPAD[0]); i++) {
            //     rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_MAGENTA);
            // }
            break;
        case _MO3:
            break;
        default:
            break;
    }
}

void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }
#endif
