#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
//#include <sys/uio.h> linux
#include <io.h> //windows
#include <math.h>
#include "Config.hpp"
#include "Features.hpp"
#include "Driver.hpp"
namespace fs = std::filesystem;

extern HMODULE hModule;

namespace Memory {
ULONG ApexPid = 0;

ULONG GetPID() {
    if (ApexPid > 0)
        return ApexPid;
    bool status = GetWindowThreadProcessId(FindWindow(L"Respawn001", NULL), &ApexPid);

    if (!ApexPid || ApexPid > 0xfffff) {
            
        	std::cout << "pid Î´ÕÒµ½ " << std::endl;
            std::cout << "pid =" << ApexPid << std::endl;
            std::cout << "status =" << status << std::endl;
            return 0;
    }
    return ApexPid;
}

bool IsValidPointer(long Pointer) {
    return Pointer > 0x00010000 && Pointer < 0x7FFFFFFEFFFF;
}

bool Read(long address, void* pBuff, size_t size) {
    if (size == 0)
        return false;
    ULONG pid = GetPID();
    if (pid == 0)
        return 0;
    if (!gReadProcessMemory(pid, address, pBuff, size)){ // 0 = yes , 1 = failed
        return true;
    }
    else {
        return false;
    }
}

bool Write(long address, void* pBuff, size_t size) {
    if (size == 0)
        return false;
    ULONG pid = GetPID();
    if (!gWriteProcessMemory(pid, address, pBuff, size)) {
        return true;
    }
    else {
        return false;
    }
}

template <class T>
T Read(long Address) {
    T buffer;
    bool success;
    if (Address)
    success = (!gReadProcessMemory(GetPID(), Address, &buffer, sizeof(T)));
    if (!success)
        std::cout << "error when reading" << std::endl;
    return buffer;
}

template <class T>
void Write(long Address, T Value) {
    bool success = Write(Address, &Value, sizeof(T));
    //if (!success && Config::Home::ErrorLogging) {
    if (!success) {
        ApexPid = 0;
        /*throw std::invalid_argument(
            "Failed to set " + std::to_string(sizeof(T)) + " at: " + std::to_string(Address));*/
    }
}

std::string ReadString(long address) {
    const int size = sizeof(std::string);
    char buffer[size] = { 0 };
    bool success = Read(address, &buffer, size);
    /*if (!success && Config::Home::ErrorLogging)
        throw new std::invalid_argument("Failed to read string at address: " + address);*/
    return std::string(buffer);
}

std::string ReadStringSize(long address, int size) {
    //char buffer[size] = { 0 }; idk how it works on linux :( lets fix it on windows
    const int Ssize = sizeof(std::string);
    char buffer[Ssize] = { 0 };

    bool success = Read(address, &buffer, Ssize);
    /*if (!success && Config::Home::ErrorLogging)
        throw std::invalid_argument("Failed to read Legend String at address: " + address);*/
    
    return std::string(buffer, size);// get how long string we need
}

std::string ConvertPointerToHexString(long pointer) {
    std::stringstream stream;
    stream << "0x" << std::hex << pointer;
    std::string result(stream.str());
    return result;
}

void WriteAttack() { // For Triggerbot
    std::this_thread::sleep_for(std::chrono::milliseconds(Features::Triggerbot::Delay));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

}