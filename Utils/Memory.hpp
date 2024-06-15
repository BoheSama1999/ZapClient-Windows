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

//extern HMODULE hModule;

namespace Memory {
ULONG ApexPid = 0;

ULONG GetPID() {
    if (ApexPid > 0)
        return ApexPid;
    bool status = GetWindowThreadProcessId(FindWindow(L"Respawn001", NULL), &ApexPid);

    if (!ApexPid || ApexPid > 0xfffff) {
            
        	std::cout << "pid 未找到 " << std::endl;
            std::cout << "pid =" << ApexPid << std::endl;
            std::cout << "status =" << status << std::endl;
            return 0;
    }
    return ApexPid;
}

bool IsValidPointer(ULONG64 Pointer) {
    return Pointer > 0x00010000 && Pointer < 0x7FFFFFFEFFFF;
}

bool Read(ULONG64 address, PVOID pBuff, ULONG size) {
    if (size == 0)
        return false;
    ULONG pid = GetPID();
    if (pid == 0)
        return false;
    bool sucess;
    sucess = (!gReadProcessMemory(pid, address, pBuff, size));
    return sucess;
}

bool Write(ULONG64 address, void* pBuff, size_t size) {
    if (size == 0)
        return false;
    ULONG pid = GetPID();
    return (!gWriteProcessMemory(pid, address, pBuff, size));
}

template <class T>
T Read(ULONG64 Address) {
    T buffer;
    //Read(Address, &buffer, sizeof(buffer));
    gReadProcessMemory(GetPID(), Address, &buffer, sizeof(T));
    return buffer;
}

template <class T>
void Write(ULONG64 Address, T Value) {
    bool success = Write(Address, &Value, sizeof(T));
    //if (!success && Config::Home::ErrorLogging) {
    if (!success) {
        ApexPid = 0;
        /*throw std::invalid_argument(
            "Failed to set " + std::to_string(sizeof(T)) + " at: " + std::to_string(Address));*/
    }
}

std::string ReadString(ULONG64 address) {
    const int size = sizeof(std::string);
    char buffer[size] = { 0 };
    bool success = Read(address, &buffer, size);
    /*if (!success && Config::Home::ErrorLogging)
        throw new std::invalid_argument("Failed to read string at address: " + address);*/
    return std::string(buffer);
}

std::string ReadStringSize(ULONG64 address, int size) {
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