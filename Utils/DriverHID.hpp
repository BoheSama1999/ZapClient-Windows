#pragma once

#include <windows.h>
#include <iostream>

#include "Driver.hpp"

extern HMODULE hModule;
struct DriverHID {
private:
    

public:
    bool KeyDown(int VK) {
        if (!gKeyboardButton(VK, 0)) // 0 = make/down, 1= break/up
            return true;
        return false;
    }

    void MouseClickLeft() {
        gMouseRughtButton(1); // 1=left, 2=right
    }

    void MoveMouse(int pitchMovement, int yawMovement) {
        gMouseMove(pitchMovement, yawMovement, 0); // 0 = relative, 1 = absolute 
    }
}; 