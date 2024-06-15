#pragma once

typedef unsigned char byte;
typedef unsigned short int ushort;

enum class InputKeyType : int {
    INPUT_UNKNOWN = 0,
    KEYBOARD_1 = 0x31,          // 键 1
    KEYBOARD_2 = 0x32,          // 键 2
    KEYBOARD_3 = 0x33,          // 键 3
    KEYBOARD_4 = 0x34,          // 键 4
    KEYBOARD_5 = 0x35,          // 键 5
    KEYBOARD_6 = 0x36,          // 键 6
    KEYBOARD_7 = 0x37,          // 键 7
    KEYBOARD_8 = 0x38,          // 键 8
    KEYBOARD_9 = 0x39,          // 键 9
    KEYBOARD_0 = 0x30,          // 键 0
    KEYBOARD_A = 0x41,          // 键 A
    KEYBOARD_B = 0x42,          // 键 B
    KEYBOARD_C = 0x43,          // 键 C
    KEYBOARD_D = 0x44,          // 键 D
    KEYBOARD_E = 0x45,          // 键 E
    KEYBOARD_F = 0x46,          // 键 F
    KEYBOARD_G = 0x47,          // 键 G
    KEYBOARD_H = 0x48,          // 键 H
    KEYBOARD_I = 0x49,          // 键 I
    KEYBOARD_J = 0x4A,          // 键 J
    KEYBOARD_K = 0x4B,          // 键 K
    KEYBOARD_L = 0x4C,          // 键 L
    KEYBOARD_M = 0x4D,          // 键 M
    KEYBOARD_N = 0x4E,          // 键 N
    KEYBOARD_O = 0x4F,          // 键 O
    KEYBOARD_P = 0x50,          // 键 P
    KEYBOARD_Q = 0x51,          // 键 Q
    KEYBOARD_R = 0x52,          // 键 R
    KEYBOARD_S = 0x53,          // 键 S
    KEYBOARD_T = 0x54,          // 键 T
    KEYBOARD_U = 0x55,          // 键 U
    KEYBOARD_V = 0x56,          // 键 V
    KEYBOARD_W = 0x57,          // 键 W
    KEYBOARD_X = 0x58,          // 键 X
    KEYBOARD_Y = 0x59,          // 键 Y
    KEYBOARD_Z = 0x5A,          // 键 Z
    KEYBOARD_F1 = 0x70,         // F1 键
    KEYBOARD_F2 = 0x71,         // F2 键
    KEYBOARD_F3 = 0x72,         // F3 键
    KEYBOARD_F4 = 0x73,         // F4 键
    KEYBOARD_F5 = 0x74,         // F5 键
    KEYBOARD_F6 = 0x75,         // F6 键
    KEYBOARD_F7 = 0x76,         // F7 键
    KEYBOARD_F8 = 0x77,         // F8 键
    KEYBOARD_F9 = 0x78,         // F9 键
    KEYBOARD_F10 = 0x79,        // F10 键
    KEYBOARD_F11 = 0x7A,        // F11 键
    KEYBOARD_F12 = 0x7B,        // F12 键
    KEYBOARD_CAPS_LOCK = 0x14,  // CAPS LOCK 键
    KEYBOARD_LEFT_SHIFT = 0xA0, // 左 SHIFT 键
    KEYBOARD_LEFT_CTRL = 0xA2,  // 左 Ctrl 键
    KEYBOARD_LEFT_ALT = 0xA4,   // 左 ALT 键
    KEYBOARD_INSERT = 0x2D,     // INS 键
    KEYBOARD_DELETE = 0x2E,     // DEL 键
    KEYBOARD_SPACE = 0x20,      // 空格键
    MOUSE_Left = 0x01,          // 鼠标左键
    MOUSE_Right = 0x02,         // 鼠标右键
    MOUSE_Middle = 0x04,        // 鼠标中键
    MOUSE_X1 = 0x05,            // X1 鼠标按钮
    MOUSE_X2 = 0x06,            // X2 鼠标按钮
    INPUT_NONE = 0              // Same as unknown
};


const char* InputKeyTypeNames[] = { "UNKNOWN", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "CAPS_LOCK", "LEFT_SHIFT", "LEFT_CTRL", "LEFT_ALT", "INSERT", "DELETE", "SPACE", "Mouse_Left", "Mouse_Right", "Mouse_Middle", "Mouse_X1", "Mouse_X2", "None" };

