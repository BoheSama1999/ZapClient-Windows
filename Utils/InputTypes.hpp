#pragma once

//#include <linux/input.h> linux 


//#define InputKeyTypeCount 61

typedef unsigned char byte;
typedef unsigned short int ushort;

enum class InputKeyType : int {
    INPUT_UNKNOWN = 0,
    KEYBOARD_1 = 0x31,          // ¼ü 1
    KEYBOARD_2 = 0x32,          // ¼ü 2
    KEYBOARD_3 = 0x33,          // ¼ü 3
    KEYBOARD_4 = 0x34,          // ¼ü 4
    KEYBOARD_5 = 0x35,          // ¼ü 5
    KEYBOARD_6 = 0x36,          // ¼ü 6
    KEYBOARD_7 = 0x37,          // ¼ü 7
    KEYBOARD_8 = 0x38,          // ¼ü 8
    KEYBOARD_9 = 0x39,          // ¼ü 9
    KEYBOARD_0 = 0x30,          // ¼ü 0
    KEYBOARD_A = 0x41,          // ¼ü A
    KEYBOARD_B = 0x42,          // ¼ü B
    KEYBOARD_C = 0x43,          // ¼ü C
    KEYBOARD_D = 0x44,          // ¼ü D
    KEYBOARD_E = 0x45,          // ¼ü E
    KEYBOARD_F = 0x46,          // ¼ü F
    KEYBOARD_G = 0x47,          // ¼ü G
    KEYBOARD_H = 0x48,          // ¼ü H
    KEYBOARD_I = 0x49,          // ¼ü I
    KEYBOARD_J = 0x4A,          // ¼ü J
    KEYBOARD_K = 0x4B,          // ¼ü K
    KEYBOARD_L = 0x4C,          // ¼ü L
    KEYBOARD_M = 0x4D,          // ¼ü M
    KEYBOARD_N = 0x4E,          // ¼ü N
    KEYBOARD_O = 0x4F,          // ¼ü O
    KEYBOARD_P = 0x50,          // ¼ü P
    KEYBOARD_Q = 0x51,          // ¼ü Q
    KEYBOARD_R = 0x52,          // ¼ü R
    KEYBOARD_S = 0x53,          // ¼ü S
    KEYBOARD_T = 0x54,          // ¼ü T
    KEYBOARD_U = 0x55,          // ¼ü U
    KEYBOARD_V = 0x56,          // ¼ü V
    KEYBOARD_W = 0x57,          // ¼ü W
    KEYBOARD_X = 0x58,          // ¼ü X
    KEYBOARD_Y = 0x59,          // ¼ü Y
    KEYBOARD_Z = 0x5A,          // ¼ü Z
    KEYBOARD_F1 = 0x70,         // F1 ¼ü
    KEYBOARD_F2 = 0x71,         // F2 ¼ü
    KEYBOARD_F3 = 0x72,         // F3 ¼ü
    KEYBOARD_F4 = 0x73,         // F4 ¼ü
    KEYBOARD_F5 = 0x74,         // F5 ¼ü
    KEYBOARD_F6 = 0x75,         // F6 ¼ü
    KEYBOARD_F7 = 0x76,         // F7 ¼ü
    KEYBOARD_F8 = 0x77,         // F8 ¼ü
    KEYBOARD_F9 = 0x78,         // F9 ¼ü
    KEYBOARD_F10 = 0x79,        // F10 ¼ü
    KEYBOARD_F11 = 0x7A,        // F11 ¼ü
    KEYBOARD_F12 = 0x7B,        // F12 ¼ü
    KEYBOARD_CAPS_LOCK = 0x14,  // CAPS LOCK ¼ü
    KEYBOARD_LEFT_SHIFT = 0xA0, // ×ó SHIFT ¼ü
    KEYBOARD_LEFT_CTRL = 0xA2,  // ×ó Ctrl ¼ü
    KEYBOARD_LEFT_ALT = 0xA4,   // ×ó ALT ¼ü
    KEYBOARD_INSERT = 0x2D,     // INS ¼ü
    KEYBOARD_DELETE = 0x2E,     // DEL ¼ü
    KEYBOARD_SPACE = 0x20,      // ¿Õ¸ñ¼ü
    MOUSE_Left = 0x01,          // Êó±ê×ó¼ü
    MOUSE_Right = 0x02,         // Êó±êÓÒ¼ü
    MOUSE_Middle = 0x04,        // Êó±êÖÐ¼ü
    MOUSE_X1 = 0x05,            // X1 Êó±ê°´Å¥
    MOUSE_X2 = 0x06,            // X2 Êó±ê°´Å¥
    INPUT_NONE = 0              // Same as unknown
};


const char* InputKeyTypeNames[] = { "UNKNOWN", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "CAPS_LOCK", "LEFT_SHIFT", "LEFT_CTRL", "LEFT_ALT", "INSERT", "DELETE", "SPACE", "Mouse_Left", "Mouse_Right", "Mouse_Middle", "Mouse_X1", "Mouse_X2", "None" };
    
//
//InputKeyType mapMouseButtonType(ushort code) {
//    switch (code)
//    {
//        case BTN_LEFT://272:
//            return InputKeyType::MOUSE_Left;
//        case BTN_RIGHT://273:
//            return InputKeyType::MOUSE_Right;
//        case BTN_MIDDLE://274
//            return InputKeyType::MOUSE_X1;
//        case BTN_EXTRA://276:
//            return InputKeyType::MOUSE_X2;
//        default:
//            return InputKeyType::INPUT_UNKNOWN;
//        none:
//            return InputKeyType::INPUT_NONE;
//    }
//
//    return InputKeyType::INPUT_UNKNOWN;
//}
//
//InputKeyType mapKeyboardKeyType(int keyCode) {
//    switch (keyCode) {
//        case KEY_1: return InputKeyType::KEYBOARD_1;
//        case KEY_2: return InputKeyType::KEYBOARD_2;
//        case KEY_3: return InputKeyType::KEYBOARD_3;
//        case KEY_4: return InputKeyType::KEYBOARD_4;
//        case KEY_5: return InputKeyType::KEYBOARD_5;
//        case KEY_6: return InputKeyType::KEYBOARD_6;
//        case KEY_7: return InputKeyType::KEYBOARD_7;
//        case KEY_8: return InputKeyType::KEYBOARD_8;
//        case KEY_9: return InputKeyType::KEYBOARD_9;
//        case KEY_0: return InputKeyType::KEYBOARD_0;
//        case KEY_A: return InputKeyType::KEYBOARD_A;
//        case KEY_B: return InputKeyType::KEYBOARD_B;
//        case KEY_C: return InputKeyType::KEYBOARD_C;
//        case KEY_D: return InputKeyType::KEYBOARD_D;
//        case KEY_E: return InputKeyType::KEYBOARD_E;
//        case KEY_F: return InputKeyType::KEYBOARD_F;
//        case KEY_G: return InputKeyType::KEYBOARD_G;
//        case KEY_H: return InputKeyType::KEYBOARD_H;
//        case KEY_I: return InputKeyType::KEYBOARD_I;
//        case KEY_J: return InputKeyType::KEYBOARD_J;
//        case KEY_K: return InputKeyType::KEYBOARD_K;
//        case KEY_L: return InputKeyType::KEYBOARD_L;
//        case KEY_M: return InputKeyType::KEYBOARD_M;
//        case KEY_N: return InputKeyType::KEYBOARD_N;
//        case KEY_O: return InputKeyType::KEYBOARD_O;
//        case KEY_P: return InputKeyType::KEYBOARD_P;
//        case KEY_Q: return InputKeyType::KEYBOARD_Q;
//        case KEY_R: return InputKeyType::KEYBOARD_R;
//        case KEY_S: return InputKeyType::KEYBOARD_S;
//        case KEY_T: return InputKeyType::KEYBOARD_T;
//        case KEY_U: return InputKeyType::KEYBOARD_U;
//        case KEY_V: return InputKeyType::KEYBOARD_V;
//        case KEY_W: return InputKeyType::KEYBOARD_W;
//        case KEY_X: return InputKeyType::KEYBOARD_X;
//        case KEY_Y: return InputKeyType::KEYBOARD_Y;
//        case KEY_Z: return InputKeyType::KEYBOARD_Z;
//        case KEY_F1: return InputKeyType::KEYBOARD_F1;
//        case KEY_F2: return InputKeyType::KEYBOARD_F2;
//        case KEY_F3: return InputKeyType::KEYBOARD_F3;
//        case KEY_F4: return InputKeyType::KEYBOARD_F4;
//        case KEY_F5: return InputKeyType::KEYBOARD_F5;
//        case KEY_F6: return InputKeyType::KEYBOARD_F6;
//        case KEY_F7: return InputKeyType::KEYBOARD_F7;
//        case KEY_F8: return InputKeyType::KEYBOARD_F8;
//        case KEY_F9: return InputKeyType::KEYBOARD_F9;
//        case KEY_F10: return InputKeyType::KEYBOARD_F10;
//        case KEY_F11: return InputKeyType::KEYBOARD_F11;
//        case KEY_F12: return InputKeyType::KEYBOARD_F12;
//        case KEY_CAPSLOCK: return InputKeyType::KEYBOARD_CAPS_LOCK;
//        case KEY_LEFTSHIFT: return InputKeyType::KEYBOARD_LEFT_SHIFT;
//        case KEY_LEFTCTRL: return InputKeyType::KEYBOARD_LEFT_CTRL;
//        case KEY_LEFTALT: return InputKeyType::KEYBOARD_LEFT_ALT;
//        case KEY_INSERT: return InputKeyType::KEYBOARD_INSERT;
//        case KEY_SPACE: return InputKeyType::KEYBOARD_SPACE;
//        default: return InputKeyType::INPUT_UNKNOWN;
//        none: return InputKeyType::INPUT_NONE;
//    }
//}
