// Externals
#pragma once
#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>
#include <time.h>
#include <random>
#include <glfw3.h>
#include <GL/gl.h>
#include <algorithm>
//#define GLFW_EXPOSE_NATIVE_X11
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Internals
#include "Font.hpp"
#include "FontAwesome.cpp"
#include "FontAwesome.h"
#include "../Utils/InputManager.hpp"
#include "Utils/Config.hpp"
#include "../Utils/Features.hpp"

class Overlay
{
private:
    GLFWwindow* OverlayWindow = nullptr;
    const GLFWvidmode* vidMode = nullptr;
    int ScreenWidth;
    int ScreenHeight;
    int ScreenPosX;
    int ScreenPosY;

    void GrabScreenSize() {
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        vidMode = glfwGetVideoMode(primaryMonitor);
        glfwGetMonitorPos(primaryMonitor, &ScreenPosX, &ScreenPosY);
        ScreenWidth = vidMode->width;
        ScreenHeight = vidMode->height;
    }

    static std::string RandomString(std::string::size_type length) {
        static auto& chrs = "0123456789"
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        thread_local static std::mt19937 rg{ std::random_device{}() };
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

        std::string s;

        s.reserve(length);

        while (length--)
            s += chrs[pick(rg)];

        return s;
    }

    static int RandomInt(int min, int max) {
        srand(time(NULL)); //seeding for the first time only!
        return min + rand() % ((max + 1) - min);
    }

    static void GLFWErrorCallback(int error, const char* description) {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    long long CurrentEpochMilliseconds() {
        auto currentTime = std::chrono::system_clock::now();
        auto duration = currentTime.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    static ImWchar* GetFontGlyphRanges() noexcept {
        static ImVector<ImWchar> ranges;
        if (ranges.empty()) {
            ImFontGlyphRangesBuilder builder;
            constexpr ImWchar baseRanges[] = {
                0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
                0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
                0x0600, 0x06FF, // Arabic
                0x0E00, 0x0E7F, // Thai
                0 };
            builder.AddRanges(baseRanges);
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesDefault());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
            builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
            // ★龍王™
            builder.AddChar(u'\u2605'); // ★
            builder.AddChar(u'\u9F8D'); // 龍
            builder.AddChar(u'\u738B'); // 王
            builder.AddChar(u'\u2122'); // ™
            builder.BuildRanges(&ranges);
        }
        return ranges.Data;
    }

public:
    int ProcessingTime;
    long long StartTime;
    int SleepTime;
    int TimeLeftToSleep;

    bool InitializeOverlay() {
        glfwSetErrorCallback(GLFWErrorCallback);
        if (!glfwInit()) {
            return false;
        }

        GrabScreenSize();

        glfwDefaultWindowHints();

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

        OverlayWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, RandomString(RandomInt(10, 20)).c_str(), nullptr, nullptr);

        CaptureInput(true);
        glfwMakeContextCurrent(OverlayWindow);

        glfwSetWindowPos(OverlayWindow, ScreenPosX, ScreenPosY);

        InitializeUI();

        glfwShowWindow(OverlayWindow);
        glfwSwapInterval(0);

        return true;
    }

    // Icons
    ImFont* IconFont = nullptr;

    void InitializeUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImFontConfig cfg;
        /*cfg.OversampleH = cfg.OversampleV = 1;
        cfg.PixelSnapH = true;
        cfg.SizePixels = 13.0f;
        cfg.GlyphOffset = {1.0f, -1.0f};*/
        cfg.OversampleH = cfg.OversampleV = 1;
        cfg.PixelSnapH = false;
        cfg.SizePixels = 13.0f; // 13.0f
        cfg.GlyphOffset = { 0.0f, 0.0f };
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.Fonts->AddFontFromMemoryCompressedTTF(_compressedFontData, _compressedFontSize, cfg.SizePixels, &cfg, GetFontGlyphRanges());

        // Icons
        static const ImWchar icon_ranges[]{ 0xf000, 0xf3ff, 0 };
        ImFontConfig IconConfig;
        IconConfig.MergeMode = true;
        IconConfig.PixelSnapH = false;
        IconConfig.OversampleH = 3;
        IconConfig.OversampleV = 3;
        IconConfig.GlyphOffset = { 0.0f, 4.5f };
        IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 23.1f, &IconConfig, icon_ranges);

        ImGui_ImplGlfw_InitForOpenGL(OverlayWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    static bool AlignedButton(const char* label, float alignment = 0.5f) {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    void DestroyOverlay() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (OverlayWindow != nullptr) {
            glfwDestroyWindow(OverlayWindow);
        }

        glfwTerminate();
    }

    void CaptureInput(bool capture) {
        glfwSetWindowAttrib(OverlayWindow, GLFW_MOUSE_PASSTHROUGH, capture ? GLFW_FALSE : GLFW_TRUE);
    }

    void FocusOverlay() {
        glfwFocusWindow(OverlayWindow);
    }

    void Start(bool (*Update)(), void (*RenderUI)()) {
        while (!glfwWindowShouldClose(OverlayWindow)) {
            StartTime = CurrentEpochMilliseconds();
            glfwPollEvents();
            glViewport(0, 0, ScreenWidth, ScreenHeight);
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, ScreenWidth, ScreenHeight, 0, -1, 1);

            // Update
            if (Update != nullptr) {
                Update();
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Render
            if (RenderUI != nullptr) {
                RenderUI();
            }

            // Render ImGui and swap buffers
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(OverlayWindow);

            ProcessingTime = static_cast<int>(CurrentEpochMilliseconds() - StartTime);
            SleepTime = 1000 / vidMode->refreshRate; // 165 = ~6ms, 144 = ~7ms, 60 = ~16ms
            if (!Features::Settings::FPSCap)
                TimeLeftToSleep = (std::max)(0, SleepTime - ProcessingTime);

            if (Features::Settings::FPSCap)
                TimeLeftToSleep = 1000 / Features::Settings::CappedFPS;

            std::this_thread::sleep_for(std::chrono::milliseconds(TimeLeftToSleep));
        }

        DestroyOverlay();
    }

    void GetScreenResolution(int& Width, int& Height) const {
        Width = ScreenWidth;
        Height = ScreenHeight;
    }

    const std::string currentDateTime(int Option) // 1 for Date And Time, 2 For Date Only, 3 for Time Only
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        if (localtime_s(&tstruct, &now) != 0)
        {
            // 处理错误情况
            return "";
        }

        if (Option == 1) // Date and Time
        {
            strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        } else if (Option == 2) // Date Only
        {
            strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        } else if (Option == 3) // Time Only
        {
            strftime(buf, sizeof(buf), "%X", &tstruct);
        }

        return buf;
    }
};
