#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>
#include <fcntl.h>
//#include <linux/input.h> linux, input code
#include <WinUser.h> //windows
#include <cstring>
//#include <libudev.h> linux, for usb device
//#include <unistd.h> linux
#include <cstdio>
#include <stdlib.h>
#include <string.h>

#include "InputTypes.hpp"


class InputManager {
public:
    static bool isKeyDownOrPress(InputKeyType key) {
        return GetAsyncKeyState(static_cast<int>(key)) & 0x8000;
    }

    static bool isKeyDown(InputKeyType key) {  
        std::cout << "Debug: " << static_cast<int>(key)<< std::endl;
        std::cout << "Debug: Should:" << static_cast<int>(InputKeyType::KEYBOARD_INSERT) << std::endl;
        bool isDown = GetAsyncKeyState(static_cast<int>(key)) & 0x8000;
        return isDown;
    }

    static bool isKeyPress(InputKeyType key) {
        static std::unordered_map<int, bool> keyState; // 记录按键状态

        bool isDown = GetAsyncKeyState(static_cast<int>(key)) & 0x8000; // 获取当前按键状态
        bool wasDown = keyState[static_cast<int>(key)]; // 获取上次的按键状态

        keyState[static_cast<int>(key)] = isDown; // 更新按键状态

        return isDown && !wasDown; // 检查是否按下
    }

    static bool isKeyUp(InputKeyType key) {
        return !(GetAsyncKeyState(static_cast<int>(key)) & 0x8000);
    }
};
