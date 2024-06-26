﻿#pragma once

typedef unsigned char byte;
typedef unsigned short int ushort;

enum class InputKeyType : int {
    INPUT_UNKNOWN = 0,
    KEYBOARD_1 = 1,
    KEYBOARD_2 = 2,
    KEYBOARD_3 = 3,
    KEYBOARD_4 = 4,
    KEYBOARD_5 = 5,
    KEYBOARD_6 = 6,
    KEYBOARD_7 = 7,
    KEYBOARD_8 = 8,
    KEYBOARD_9 = 9,
    KEYBOARD_0 = 10,
    KEYBOARD_A = 11,
    KEYBOARD_B = 12,
    KEYBOARD_C = 13,
    KEYBOARD_D = 14,
    KEYBOARD_E = 15,
    KEYBOARD_F = 16,
    KEYBOARD_G = 17,
    KEYBOARD_H = 18,
    KEYBOARD_I = 19,
    KEYBOARD_J = 20,
    KEYBOARD_K = 21,
    KEYBOARD_L = 22,
    KEYBOARD_M = 23,
    KEYBOARD_N = 24,
    KEYBOARD_O = 25,
    KEYBOARD_P = 26,
    KEYBOARD_Q = 27,
    KEYBOARD_R = 28,
    KEYBOARD_S = 29,
    KEYBOARD_T = 30,
    KEYBOARD_U = 31,
    KEYBOARD_V = 32,
    KEYBOARD_W = 33,
    KEYBOARD_X = 34,
    KEYBOARD_Y = 35,
    KEYBOARD_Z = 36,
    KEYBOARD_F1 = 37,
    KEYBOARD_F2 = 38,
    KEYBOARD_F3 = 39,
    KEYBOARD_F4 = 40,
    KEYBOARD_F5 = 41,
    KEYBOARD_F6 = 42,
    KEYBOARD_F7 = 43,
    KEYBOARD_F8 = 44,
    KEYBOARD_F9 = 45,
    KEYBOARD_F10 = 46,
    KEYBOARD_F11 = 47,
    KEYBOARD_F12 = 48,
    KEYBOARD_CAPS_LOCK = 49,
    KEYBOARD_LEFT_SHIFT = 50,
    KEYBOARD_LEFT_CTRL = 51,
    KEYBOARD_LEFT_ALT = 52,
    KEYBOARD_INSERT = 53,
    KEYBOARD_DELETE = 54,
    KEYBOARD_SPACE = 55,
    MOUSE_Left = 56,
    MOUSE_Right = 57,
    MOUSE_Middle = 58,
    MOUSE_X1 = 59,
    MOUSE_X2 = 60,
    INPUT_NONE = 0 //Same as unknown
};


const char* InputKeyTypeNames[] = { "UNKNOWN", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "CAPS_LOCK", "LEFT_SHIFT", "LEFT_CTRL", "LEFT_ALT", "INSERT", "DELETE", "SPACE", "Mouse_Left", "Mouse_Right", "Mouse_Middle", "Mouse_X1", "Mouse_X2", "None" };

