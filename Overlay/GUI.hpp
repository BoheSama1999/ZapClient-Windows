// Externals
#pragma once
#include <chrono>
#include <cstddef>
#include <string>
#include <thread>
#include <glfw3.h>
#include <GL/gl.h>
#include "../imgui/imgui.h"
#include "../imgui/imconfig.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"
#include "FontAwesome.h"
#define IMGUI_DEFINE_MATH_OPERATORS

// Internals
#include "Font.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Features/Legitbot.hpp"
#include "AdvancedGUI.hpp"
#include "Overlay.hpp"
#include "../Core/LocalPlayer.hpp"

struct Menu
{
	bool ShowMenu = true;
	ImVec4 DetailColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	ImVec4 ButtonColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	ImVec4 CheckboxColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	ImVec4 TextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	ImVec4 SelectedColor = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;
	ImGuiColorEditFlags ColorEditFlags = ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs;

	int WindowWidth = 1000; // 1000 // 950 // 1000
	int WindowHeight = 495; // 600 // 450 // 648

	//bool TeamGamemode = true;

	enum MenuTabs
	{
		Legitbot,
		Ragebot,
		Flickbot,
		Triggerbot,
		Glow,
		ESP,
		Misc,
		Settings,
		Config
	};

	int SelectedLegitbotSubTab = 0;	  // 6
	int SelectedRagebotSubTab = 0;	  // 1
	int SelectedFlickbotSubTab = 0;	  // 2
	int SelectedTriggerbotSubTab = 0; // 2
	int SelectedGlowSubTab = 0;		  // 2
	int SelectedESPSubTabLeft = 0;	  // 3
	int SelectedESPSubTabRight = 0;	  // 4
	int SelectedMiscSubTab = 0;		  // 4
	int SelectedSettingsSubTab = 0;	  // 2
	int SelectedConfigSubTab = 0;	  // 1

	MenuTabs CurrentTab = MenuTabs::Legitbot;

	// Icons
	ImFont* IconFont = nullptr;

	LocalPlayer* Myself;
	AdvancedGUI* Advanced;

	Menu(LocalPlayer* Myself, AdvancedGUI* Advanced) {
		this->Myself = Myself;
		this->Advanced = Advanced;
	}

	// Padding between controls
	const void Space(bool NoSeparator = false) {
		ImGui::Spacing();
		if (!NoSeparator) {
			ImGui::Spacing();
			ImGui::Separator();
		}
		ImGui::Spacing();
		ImGui::Spacing();
	}

	// Two Spacings In One! Who Would've Thought!
	const void DoubleSpacing() {
		ImGui::Spacing();
		ImGui::Spacing();
	}

	// Ok, Three Spacings In One Is Pushing It.
	const void TripleSpacing() {
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
	}

	// Help Marker
	const void DrawHelpMarker(const char* desc) {
		ImGui::SameLine(ImGui::GetWindowWidth() - 50);
		ImGui::TextDisabled("[?]");
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	// Help Marker
	static void Helper(const char* desc) {

		ImGui::SameLine(0.f, 5.f);
		ImGui::Text("(?)");
		if (ImGui::IsItemHovered()) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::Text(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
			ImGui::PopStyleVar();
		}
	}

	void ComboBox(const char* label, const char* desc, int* current_item, const char* items_separated_by_zeros, int height_in_items) {
		ImGui::Spacing();
		ImGui::SameLine(15);
		ImGui::TextColored(ImColor(255, 255, 255, 255), label);

		ImGui::Spacing();
		ImGui::SameLine(15);
		ImGui::TextColored(ImColor(97, 97, 97, 255), desc);
		ImGui::ComboBox(label, current_item, items_separated_by_zeros, height_in_items);
		ImGui::Spacing();
	}

	void MultiCombo(const char* label, bool variable[], const char* labels[], int count) {
		ImGuiContext& g = *GImGui;

		std::string preview = "None";

		for (auto i = 0, j = 0; i < count; i++) {
			if (variable[i]) {
				if (j)
					preview += (", ") + (std::string)labels[i];
				else
					preview = labels[i];

				j++;
			}
		}

		if (ImGui::BeginCombo(label, preview.c_str(), count)) // draw start
		{
			for (auto i = 0; i < count; i++)
				ImGui::Selectable(labels[i], &variable[i], ImGuiSelectableFlags_DontClosePopups);
			ImGui::EndCombo();
		}

		preview = ("None"); // reset preview to use later
	}

	bool SubTab(const char* label, bool isSelected, const ImVec2& size) {
		if (isSelected) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button));
		}

		bool pressed = ImGui::Button(label, size);
		ImGui::PopStyleColor(1);

		return pressed;
	}

	// Render GUI Tabs
	void RenderLegitbot(Overlay OverlayWindow) {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("  AIMBOT", 0 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 0;
		ImGui::SameLine();
		if (SubTab("ADVANCED##AIMBOT", 1 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 1;
		ImGui::SameLine();
		if (SubTab(" WEAPONS##AIMBOT", 2 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 2;
		ImGui::SameLine();
		if (SubTab(" VISUALS##AIMBOT", 3 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 3;
		/*ImGui::SameLine();
		// Add Vertical Separator Line
		ImVec2 C = ImGui::GetWindowPos();
		const ImVec2 Point1 = ImVec2(TabSize.x / 1.77 + 6.5f + C.x, 32 + C.y);
		const ImVec2 Point2 = ImVec2(TabSize.x / 1.77 + 6.5f + C.x, C.y);
		ImVec4 SeperatorColor = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImGui::GetWindowDrawList()->AddLine(Point1, Point2, ImGui::ColorConvertFloat4ToU32(SeperatorColor), 1.0f);*/
		ImGui::SameLine();
		if (SubTab(" RCS", 4 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 4;
		ImGui::SameLine();
		if (SubTab("ADVANCED##RCS", 5 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 5;
		ImGui::SameLine();
		if (SubTab(" WEAPONS##RCS", 6 == SelectedLegitbotSubTab, ImVec2(111, 25)))
			SelectedLegitbotSubTab = 6;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedLegitbotSubTab == 0) {
			ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 135), true);
			{
				ImGui::Spacing();
				ImGui::Text("Aimbot");
				ImGui::Checkbox("Enabled", &Features::Aimbot::AimbotEnabled);
				if (Features::Aimbot::AimbotEnabled) {
					const char* AimbotModeIndex[] = { "Cubic Bezier [xap-client]", "Linear [Grinder]", "Cubic Bezier 2 [Nika]" };
					ImGui::ComboBox("Aimbot Method", &Features::Aimbot::AimbotMode, AimbotModeIndex, IM_ARRAYSIZE(AimbotModeIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What Aimbot Method You Would Like.\nYou may find Grinder To Be More Legit/Smooth.");
					const char* InputMethodIndex[] = { "Mouse", "Memory (Controller Supported)" };
					ImGui::ComboBox("Input Method", &Features::Aimbot::InputMethod, InputMethodIndex, IM_ARRAYSIZE(InputMethodIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What Input Method The Aimbot Will Use.\nYou Can Use Controller Method With KBM, But I Recommend Mouse.\nNote: Controller Input Method Requires Low Processing Speed To Work Well (Below 10-15ms).");
				}
				ImGui::EndChildFrame();
			}

			if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2 && !Features::Aimbot::AdvancedAim) {
				ImGui::Columns(2, nullptr, false);
				ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 613, 93), true);
				{
					ImGui::Spacing();
					ImGui::Text("Selected Hitbox");
					ImGui::Checkbox("Closest To Crosshair", &Features::Aimbot::ClosestHitbox);
					if (!Features::Aimbot::ClosestHitbox) {
						const char* HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
						int HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::Hitbox);
						ImGui::ComboBox("Hitbox Type", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Which bone the aimbot will aim at.");
						Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
					}
					ImGui::EndChildFrame();
				}

				ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 613, 190), true);
				{
					ImGui::Spacing();
					const char* BindMethodIndex[] = { "Memory", "Keybinds" };
					ImGui::ComboBox("Aim Bind Method", &Features::Aimbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
					if (!Features::Aimbot::AdvancedAim) {
						if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
							ImGui::Checkbox("On Fire", &Features::Aimbot::OnFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS", &Features::Aimbot::OnADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
							ImGui::ComboBox("Aim Bind##Aimbot", &AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::AimBind = static_cast<InputKeyType>(AimBind);
							int ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);
							ImGui::ComboBox("Extra Bind##Aimbot", &ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ExtraBind = static_cast<InputKeyType>(ExtraBind);
						}
						ImGui::Text("Aim Conditions");
						ImGui::Checkbox("Team Check##Aimbot", &Features::Aimbot::TeamCheck);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
						if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) { // xap-client
							ImGui::SameLine();
							ImGui::Checkbox("Visibility Check", &Features::Aimbot::VisCheck);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Aims At Only Visible Enemies.");
						}

						ImGui::Checkbox("Spectator Check", &Features::Aimbot::SpectatorCheck);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Disables Aimbot When Being Spectated.");
						if (Features::Aimbot::SpectatorCheck) {
							ImGui::SameLine();
							ImGui::Checkbox("Spectator Notifier", &Features::Aimbot::SpectatorNotifier);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Notifies You When You Are Being Spectated & That Aimbot Is Disabled.");
						}

						ImGui::Text("Targeting Options");
						ImGui::Checkbox("Allow Target Switching", &Features::Aimbot::TargetSwitching);
						const char* PriorityIndex[] = { "Closest To Crosshair", "Closest To LocalPlayer", "Both" };
						ImGui::ComboBox("Target Priority", &Features::Aimbot::Priority, PriorityIndex, IM_ARRAYSIZE(PriorityIndex));
						DoubleSpacing();
					}
					ImGui::EndChildFrame();
				}

				if (!Features::Aimbot::AdvancedAim && Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) { // Cubic Bezier [xap-client]
					ImGui::BeginChildFrame(4, ImVec2(WindowWidth - 613, 169), true);
					{
						ImGui::Spacing();
						const char* SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SmoothingMethod, SmoothingMethodIndex, IM_ARRAYSIZE(SmoothingMethodIndex));

						if (Features::Aimbot::InputMethod == 0) // Mouse Only
						{
							ImGui::MainSliderFloat("Speed", &Features::Aimbot::Speed, 1, 100, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Speed of the Aim-Assist\nHigher = Faster");
						}

						if (Features::Aimbot::SmoothingMethod == 0) // Static
						{
							if (Features::Aimbot::AimbotMode == 0) {
								ImGui::MainSliderFloat("Hipfire Smoothing", &Features::Aimbot::HipfireSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("ADS Smoothing", &Features::Aimbot::ADSSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");
							}
							if (Features::Aimbot::AimbotMode == 2) {
								ImGui::MainSliderFloat("Hipfire Smoothing##Test", &Features::Aimbot::MouseHipfireSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("ADS Smoothing##Test", &Features::Aimbot::MouseADSSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");
							}
						}
						if (Features::Aimbot::SmoothingMethod == 1) // Random
						{
							if (Features::Aimbot::AimbotMode == 0) {
								ImGui::MainSliderFloat("Minimum Hipfire Smoothing", &Features::Aimbot::MinHipfireSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("Maximum Hipfire Smoothing", &Features::Aimbot::MaxHipfireSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("Minimum ADS Smoothing", &Features::Aimbot::MinADSSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");

								ImGui::MainSliderFloat("Maximum ADS Smoothing", &Features::Aimbot::MaxADSSmooth, 0, 0.999, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");
							}
							if (Features::Aimbot::AimbotMode == 2) {
								ImGui::MainSliderFloat("Minimum Hipfire Smoothing##Test", &Features::Aimbot::MinMouseHipfireSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("Maximum Hipfire Smoothing##Test", &Features::Aimbot::MaxMouseHipfireSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

								ImGui::MainSliderFloat("Minimum ADS Smoothing##Test", &Features::Aimbot::MinMouseADSSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");

								ImGui::MainSliderFloat("Maximum ADS Smoothing##Test", &Features::Aimbot::MaxMouseADSSmoothing, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");
							}
						}

						if (Features::Aimbot::AimbotMode == 2) {
							ImGui::MainSliderFloat("Distance Smoothing##Test", &Features::Aimbot::MouseExtraSmoothing, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
						}

						if (Features::Aimbot::InputMethod == 0) { // Mouse Only
							ImGui::MainSliderFloat("Deadzone", &Features::Aimbot::Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");
						}

						ImGui::SliderInt("Delay", &Features::Aimbot::Delay, 1, 50);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Delay time for the aimbot smoothing.\n");

						ImGui::EndChildFrame();
					}

					ImGui::NextColumn();

					ImGui::BeginChildFrame(5, ImVec2(WindowWidth - 630, 93), true);
					{
						ImGui::Spacing();
						ImGui::Text("Prediction");
						ImGui::Checkbox("Predict Movement", &Features::Aimbot::PredictMovement);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Predict target's movement");
						ImGui::SameLine();
						ImGui::Checkbox("Predict Bullet Drop", &Features::Aimbot::PredictBulletDrop);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Predict weapon's bullet drop");

						ImGui::EndChildFrame();
					}

					ImGui::BeginChildFrame(6, ImVec2(WindowWidth - 630, 190), true);
					{
						ImGui::Spacing();
						ImGui::MainSliderFloat("FOV", &Features::Aimbot::FOV, 1, 90, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Field of View");
						ImGui::MainSliderFloat("Zoom Scale", &Features::Aimbot::ZoomScale, 0, 5, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Field of View For Scopes");

						ImGui::EndChildFrame();
					}

					ImGui::BeginChildFrame(7, ImVec2(WindowWidth - 630, 169), true);
					{
						ImGui::Spacing();
						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::AdvancedMinDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Min distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::AdvancedMaxDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Max distance for Aim-Assist to work");
						ImGui::EndChildFrame();
					}
					ImGui::Spacing();
				}
			}

			if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimbotMode == 1 && !Features::Aimbot::AdvancedAim && Features::Aimbot::InputMethod == 0) {
				ImGui::Columns(2, nullptr, false);
				ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 613, 217), true);
				{
					ImGui::Spacing();
					const char* BindMethodIndex[] = { "Memory", "Keybinds" };
					ImGui::ComboBox("Aim Bind Method", &Features::Aimbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
					if (!Features::Aimbot::AdvancedAim) {
						if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
							ImGui::Checkbox("On Fire", &Features::Aimbot::OnFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS", &Features::Aimbot::OnADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
							ImGui::ComboBox("Aim Bind##Aimbot", &AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::AimBind = static_cast<InputKeyType>(AimBind);
							int ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);
							ImGui::ComboBox("Extra Bind##Aimbot", &ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ExtraBind = static_cast<InputKeyType>(ExtraBind);
						}
						ImGui::Text("Aim Conditions");
						ImGui::Checkbox("Team Check##Aimbot", &Features::Aimbot::TeamCheck);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
						ImGui::Checkbox("Spectator Check", &Features::Aimbot::SpectatorCheck);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Disables Aimbot When Being Spectated.");
						if (Features::Aimbot::SpectatorCheck) {
							ImGui::SameLine();
							ImGui::Checkbox("Spectator Notifier", &Features::Aimbot::SpectatorNotifier);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Notifies You When You Are Being Spectated & That Aimbot Is Disabled.");
						}
					}
					ImGui::EndChildFrame();
				}

				ImGui::BeginChildFrame(4, ImVec2(WindowWidth - 613, 217), true);
				{
					ImGui::Spacing();

					const char* SmoothingMethodIndex[] = { "Static", "Random" };
					ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SmoothingMethod, SmoothingMethodIndex, IM_ARRAYSIZE(SmoothingMethodIndex));

					if (Features::Aimbot::SmoothingMethod == 0) // Static
					{
						ImGui::MainSliderFloat("Hipfire Smoothing##Grinder", &Features::Aimbot::HipfireSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");
						ImGui::MainSliderFloat("ADS Smoothing##Grinder", &Features::Aimbot::ADSSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Smoothing Of The Aim-Assist Longbow Whilst ADS.\nHigher = Smoother");
					}

					if (Features::Aimbot::SmoothingMethod == 1) // Random
					{
						ImGui::MainSliderFloat("Min Hipfire Smoothing##Grinder", &Features::Aimbot::MinHipfireSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");
						ImGui::MainSliderFloat("Max Hipfire Smoothing##Grinder", &Features::Aimbot::MaxHipfireSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");

						ImGui::MainSliderFloat("Min ADS Smoothing##Grinder", &Features::Aimbot::MinADSSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist Whilst ADS.\nHigher = Smoother");
						ImGui::MainSliderFloat("Max ADS Smoothing##Grinder", &Features::Aimbot::MaxADSSmooth1, 1, 1000, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist Whilst ADS.\nHigher = Smoother");
					}

					ImGui::MainSliderFloat("Extra Smoothing##Grinder", &Features::Aimbot::ExtraSmoothing, 1, 9999, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
					ImGui::MainSliderFloat("Deadzone##Grinder", &Features::Aimbot::Deadzone, 0, 10, "%.03f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				ImGui::BeginChildFrame(6, ImVec2(WindowWidth - 630, 217), true);
				{
					ImGui::Spacing();
					ImGui::MainSliderFloat("FOV##Grinder", &Features::Aimbot::FOV1, 1, 90, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Field of View.");
					ImGui::EndChildFrame();
				}

				ImGui::BeginChildFrame(7, ImVec2(WindowWidth - 630, 217), true);
				{
					ImGui::Spacing();
					ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::AdvancedMinDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Min distance for Aim-Assist to work");
					ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::AdvancedMaxDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Max distance for Aim-Assist to work");
					ImGui::EndChildFrame();
				}
				ImGui::Spacing();
			}

			if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimbotMode == 1 && Features::Aimbot::InputMethod == 1) {
				ImGui::Text("Selected Input Method Is Not Compatible With Selected Aimbot Method, Please Switch Aimbot Method Or Input Method.");
			}

			if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AdvancedAim) {
				ImGui::Text("Advanced Aim Is Enabled, Use The Advanced Tab.");
			}
		}

		if (SelectedLegitbotSubTab == 1) {
			Advanced->AdvancedAimbotTab(Myself->WeaponIndex);
		}

		if (SelectedLegitbotSubTab == 2) {
			if (Features::Aimbot::AimbotEnabled) {
				ImGui::Spacing();
				ImGui::Columns(3, "##aimbotSelection", false);
				if (ImGui::BeginChildFrame(11, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
					ImGui::Checkbox("P2020##Aimbot", &Features::Aimbot::P2020);
					ImGui::Checkbox("RE-45 Auto##Aimbot", &Features::Aimbot::RE45);
					ImGui::Checkbox("Alternator SMG##Aimbot", &Features::Aimbot::Alternator);
					ImGui::Checkbox("R-99 SMG##Aimbot", &Features::Aimbot::R99);
					ImGui::Checkbox("R-301 Carbine##Aimbot", &Features::Aimbot::R301);
					ImGui::Checkbox("M600 Spitfire##Aimbot", &Features::Aimbot::Spitfire);
					ImGui::Checkbox("G7 Scout##Aimbot", &Features::Aimbot::G7);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(12, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
					ImGui::Checkbox("VK-47 Flatline##Aimbot", &Features::Aimbot::Flatline);
					ImGui::Checkbox("Prowler Burst SMG##Aimbot", &Features::Aimbot::Prowler);
					ImGui::Checkbox("Hemlock Burst AR##Aimbot", &Features::Aimbot::Hemlock);
					ImGui::Checkbox("30-30 Repeater##Aimbot", &Features::Aimbot::Repeater);
					ImGui::Checkbox("Rampage LMG##Aimbot", &Features::Aimbot::Rampage);
					ImGui::Checkbox("C.A.R SMG##Aimbot", &Features::Aimbot::CARSMG);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(13, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
					ImGui::Checkbox("Havoc Rifle##Aimbot", &Features::Aimbot::Havoc);
					ImGui::Checkbox("Devotion LMG##Aimbot", &Features::Aimbot::Devotion);
					ImGui::Checkbox("L-Star EMG##Aimbot", &Features::Aimbot::LSTAR);
					ImGui::Checkbox("Triple-Take##Aimbot", &Features::Aimbot::TripleTake);
					ImGui::Checkbox("Volt##Aimbot", &Features::Aimbot::Volt);
					ImGui::Checkbox("Nemesis Burst AR##Aimbot", &Features::Aimbot::Nemesis);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(14, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
					ImGui::Checkbox("Mozambique##Aimbot", &Features::Aimbot::Mozambique);
					ImGui::Checkbox("Peacekeeper##Aimbot", &Features::Aimbot::Peacekeeper);
					ImGui::Checkbox("Mastiff##Aimbot", &Features::Aimbot::Mastiff);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(15, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
					ImGui::Checkbox("Longbow DMR##Aimbot", &Features::Aimbot::Longbow);
					ImGui::Checkbox("Charge Rifle##Aimbot", &Features::Aimbot::ChargeRifle);
					ImGui::Checkbox("Sentinel##Aimbot", &Features::Aimbot::Sentinel);
					ImGui::EndChildFrame();
				}

				if (ImGui::BeginChildFrame(16, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
					ImGui::Checkbox("Wingman##Aimbot", &Features::Aimbot::Wingman);
					ImGui::Checkbox("EVA-8 Auto##Aimbot", &Features::Aimbot::EVA8);
					ImGui::Checkbox("Kraber .50-CAL Sniper##Aimbot", &Features::Aimbot::Kraber);
					ImGui::EndChildFrame();
				}
				ImGui::NextColumn();
			}
			if (!Features::Aimbot::AimbotEnabled) {
				ImGui::Text("Aimbot Is Disabled!");
			}
		}

		if (SelectedLegitbotSubTab == 3) {
			if (Features::Aimbot::AimbotEnabled) {
				ImGui::BeginChildFrame(69, ImVec2(WindowWidth - 220, 130), true);
				{
					ImGui::Spacing();
					if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) {
						ImGui::Text("FOV Circle");
						ImGui::Checkbox("Draw FOV Circle", &Features::Sense::DrawFOVCircle);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Draw A FOV Circle.\nDoes Not Draw If Aimbot Mode == Grinder.");
						ImGui::Checkbox("Draw Filled FOV Circle", &Features::Sense::DrawFilledFOVCircle);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Draw A Filled FOV Circle.\nDoes Not Draw If Aimbot Mode == Grinder.");
						if (Features::Sense::DrawFOVCircle or Features::Sense::DrawFilledFOVCircle) {
							ImGui::MainSliderFloat("FOV Circle Thickness", &Features::Sense::FOVThickness, 1, 10, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Changes the FOV Circle's thickness\n Recomended: 1-2");
							ImGui::MainSliderFloat("Game's FOV", &Features::Sense::GameFOV, 70, 120, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Your current FOV in Settings");
							if (Features::Sense::DrawFOVCircle) {
								ImGui::ColorEdit4("FOV Circle", Features::Colors::FOVColor, ColorEditFlags);
							}
							if (Features::Sense::DrawFilledFOVCircle) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Filled FOV Circle", Features::Colors::FilledFOVColor, ColorEditFlags);
							}
						}
					} else if (Features::Aimbot::AimbotMode == 1) {
						ImGui::Text("Selected Aimbot Mode Does Not Support Aimbot Visuals!");
					}
					ImGui::EndChildFrame();
				}

				if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 2) {
					ImGui::Columns(2, nullptr, false);

					ImGui::BeginChildFrame(420, ImVec2(WindowWidth - 613, WindowHeight - 245), true);
					{
						ImGui::Spacing();
						ImGui::Text("Target Visuals");
						ImGui::Checkbox("Draw Target Line", &Features::Sense::DrawTargetLine);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Draw A Line From The Center Of The Screen To The CurrentTarget.");
						ImGui::Checkbox("Draw Target Dot", &Features::Sense::DrawTargetDot);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Draw A Dot On The CurrentTarget.");
						ImGui::Checkbox("Draw Target Box", &Features::Sense::DrawTargetBox);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Draw A Box On The CurrentTarget.");
						if (Features::Sense::DrawTargetLine or Features::Sense::DrawTargetDot or Features::Sense::DrawTargetBox) {
							const char* TargetVisualsModeIndex[] = { "Current Target", "Best Target" };
							ImGui::ComboBox("Target Mode", &Features::Sense::TargetMode, TargetVisualsModeIndex, IM_ARRAYSIZE(TargetVisualsModeIndex));
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("When The Target Visuals Will Be Drawn.\nCurrent Target = Aimbot Target");

							if ((Features::Sense::DrawTargetBox && Features::Sense::TargetBoxMode == 0) or Features::Sense::DrawTargetLine or Features::Sense::DrawTargetDot) {
								const char* TargetVisualsBoneIndex[] = { "Aimbot Selected Bone", "Custom" };
								ImGui::ComboBox("Target Bone Mode", &Features::Sense::TargetBoneMode, TargetVisualsBoneIndex, IM_ARRAYSIZE(TargetVisualsBoneIndex));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Target Visuals Will Draw To On The Target.");
							}

							if (Features::Sense::TargetBoneMode == 1) {
								const char* HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int HitboxTypeIndex = static_cast<int>(Features::Sense::TargetHitbox);
								ImGui::ComboBox("Selected Bone", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which Bone The Target Line/Dot/Box Will Be Drawn To/On.");
								Features::Sense::TargetHitbox = static_cast<HitboxType>(HitboxTypeIndex);
							}
						}

						if (Features::Sense::DrawTargetLine) {
							ImGui::SliderInt("Target Line Thickness", &Features::Sense::TargetLineThickness, 1, 10);
							ImGui::ColorEdit4("Target Line Color", Features::Colors::TargetLineColor, ColorEditFlags);
							if (Features::Sense::TargetMode == 1) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Target Line Locked Color", Features::Colors::TargetLineLockedColor, ColorEditFlags);
							}
						}

						if (Features::Sense::DrawTargetDot) {
							ImGui::SliderInt("Target Dot Radius", &Features::Sense::TargetDotRadius, 100, 2500);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Size (Radius) Of The Target Dot.\nRecommended: 1000-1500");
							ImGui::ColorEdit4("Target Dot Color", Features::Colors::TargetDotColor, ColorEditFlags);
							if (Features::Sense::TargetMode == 1) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Target Dot Locked Color", Features::Colors::TargetDotLockedColor, ColorEditFlags);
							}
						}

						if (Features::Sense::DrawTargetBox) {
							const char* TargetBoxModeIndex[] = { "Custom Box", "ESP Box" };
							ImGui::ComboBox("Target Box Mode", &Features::Sense::TargetBoxMode, TargetBoxModeIndex, IM_ARRAYSIZE(TargetBoxModeIndex));
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("What Kind Of Box Will Be Drawn.\nESP Box = ESP Box In The ESP Tab");

							if (Features::Sense::TargetBoxMode == 0) {
								ImGui::SliderInt("Target Box Size", &Features::Sense::TargetBoxSize, 1, 20);
								ImGui::SliderInt("Target Box Thickness", &Features::Sense::TargetBoxThickness, 1, 20);
							}

							ImGui::ColorEdit4("Target Box Color", Features::Colors::TargetBoxColor, ColorEditFlags);
							if (Features::Sense::TargetMode == 1) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Target Box Locked Color", Features::Colors::TargetBoxLockedColor, ColorEditFlags);
							}

							if (Features::Sense::TargetBoxMode == 1) {
								ImGui::Text("Go To ESP->Box ESP To Configure The Target Box!");
							}
						}

						ImGui::EndChildFrame();
					}

					ImGui::NextColumn(); // Right

					ImGui::BeginChildFrame(421, ImVec2(WindowWidth - 630, WindowHeight - 245), true);
					{
						ImGui::Spacing();
						ImGui::Text("Target Information");
						ImGui::Checkbox("Draw Target Information", &Features::Sense::DrawTargetInfo);
						if (Features::Sense::DrawTargetInfo) {
							const char* TargetInfoPos[] = { "1", "2", "3", "4", "5" };

							const char* TargetVisualsModeIndex[] = { "Current Target", "Best Target" };
							ImGui::ComboBox("Target Mode", &Features::Sense::TargetMode, TargetVisualsModeIndex, IM_ARRAYSIZE(TargetVisualsModeIndex));
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("When The Target Visuals Will Be Drawn.\nCurrent Target = Aimbot Target");

							ImGui::Checkbox("Draw Target Name", &Features::Sense::DrawTargetInfoName);
							if (Features::Sense::DrawTargetInfoName) {
								ImGui::ComboBox("Target Name Position", &Features::Sense::TargetInfoNamePos, TargetInfoPos, IM_ARRAYSIZE(TargetInfoPos));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Name Text Will Be Drawn.");
							}
							ImGui::Checkbox("Draw Target Legend", &Features::Sense::DrawTargetInfoLegend);
							if (Features::Sense::DrawTargetInfoLegend) {
								ImGui::ComboBox("Target Legend Position", &Features::Sense::TargetInfoLegendPos, TargetInfoPos, IM_ARRAYSIZE(TargetInfoPos));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Legend Text Will Be Drawn.");
							}

							if (Features::Sense::DrawTargetInfoName && Features::Sense::DrawTargetInfoLegend) {
								const char* TargetInfoDisplayMode[] = { "Name First, Legend Second", "Legend First, Name Second" };
								ImGui::ComboBox("Target Display Mode", &Features::Sense::TargetInfoDisplayMode, TargetInfoDisplayMode, IM_ARRAYSIZE(TargetInfoDisplayMode));
							}

							if (Features::Sense::DrawTargetInfoName && Features::Sense::DrawTargetInfoLegend && Features::Sense::TargetInfoDisplayMode == 0) {
								Features::Sense::TargetInfoNamePos = 0;
								Features::Sense::TargetInfoLegendPos = 1;
							}
							if (Features::Sense::DrawTargetInfoName && Features::Sense::DrawTargetInfoLegend && Features::Sense::TargetInfoDisplayMode == 1) {
								Features::Sense::TargetInfoNamePos = 1;
								Features::Sense::TargetInfoLegendPos = 0;
							}

							if (Features::Sense::DrawTargetInfoName or Features::Sense::DrawTargetInfoLegend) {
								ImGui::Checkbox("Draw Target Team ID", &Features::Sense::DrawTargetInfoTeamID);
								ImGui::Checkbox("Draw Target Distance", &Features::Sense::DrawTargetInfoDistance);
							}

							ImGui::Checkbox("Draw Target Weapon", &Features::Sense::DrawTargetInfoWeapon);
							if (Features::Sense::DrawTargetInfoWeapon) {
								ImGui::ComboBox("Target Weapon Position", &Features::Sense::TargetInfoWeaponPos, TargetInfoPos, IM_ARRAYSIZE(TargetInfoPos));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Weapon Text Will Be Drawn.");
							}

							ImGui::Checkbox("Draw Target Health", &Features::Sense::DrawTargetInfoHealth);
							if (Features::Sense::DrawTargetInfoHealth) {
								ImGui::ComboBox("Target Health Position", &Features::Sense::TargetInfoHealthPos, TargetInfoPos, IM_ARRAYSIZE(TargetInfoPos));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Health Text Will Be Drawn.");
							}

							ImGui::Checkbox("Draw Target Shield", &Features::Sense::DrawTargetInfoShield);
							if (Features::Sense::DrawTargetInfoShield) {
								ImGui::ComboBox("Target Shield Position", &Features::Sense::TargetInfoShieldPos, TargetInfoPos, IM_ARRAYSIZE(TargetInfoPos));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Where The Shield Text Will Be Drawn.");
							}

							ImGui::SliderInt("Target Info Offset", &Features::Sense::TargetInfoOffset, 0, 50);

							int ScreenWidth;
							int ScreenHeight;
							OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
							ImGui::SliderInt("Information Window X", &Features::Sense::TargetInfoPosX, 0, ScreenWidth);
							ImGui::SliderInt("Information Window Y", &Features::Sense::TargetInfoPosY, 0, ScreenHeight);
							if (ImGui::Button("Auto Set Position##TargetInfo", ImVec2(125, 25))) {
								int AutoWidth = ScreenWidth / 2;
								int AutoHeight = (ScreenHeight / 2) + 80;
								Features::Sense::TargetInfoPosX = AutoWidth;
								Features::Sense::TargetInfoPosY = AutoHeight;
							}

							const char* TargetInfoColorMode[] = { "Simple", "Advanced" };
							ImGui::ComboBox("Target Info Color Mode", &Features::Sense::TargetInfoColorMode, TargetInfoColorMode, IM_ARRAYSIZE(TargetInfoColorMode));

							ImGui::ColorEdit4("Target Info Color", Features::Colors::TargetInfoColor, ColorEditFlags);
							ImGui::ColorEdit4("Target Info Locked Color", Features::Colors::TargetInfoLockedColor, ColorEditFlags);

							/*static bool multi_num[4] = { true, true, true, false };
							const char* multi_items[4] = { "Body", "Neck", "Spin", "Legs" };
							MultiCombo("Body Overlay", multi_num, multi_items, 4);*/
						}
						DoubleSpacing();

						ImGui::EndChildFrame();
					}
				}
			} else if (!Features::Aimbot::AimbotEnabled) {
				ImGui::Text("Aimbot Is Disabled!");
			}

			ImGui::NextColumn(); //
		}

		if (SelectedLegitbotSubTab == 4) {
			ImGui::BeginChildFrame(17, ImVec2(WindowWidth - 220, 93), true);
			{
				ImGui::Spacing();
				ImGui::Text("RCS - Recoil Control");
				ImGui::Checkbox("Enabled", &Features::RCS::RCSEnabled);
				if (Features::RCS::RCSEnabled) {
					const char* RCSModeIndex[] = { "Standalone", "Combined" };
					ImGui::ComboBox("RCS Method", &Features::RCS::RCSMode, RCSModeIndex, IM_ARRAYSIZE(RCSModeIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What RCS Method You Would Like.\nStandalone Provideds Legit & Customizable Settings.\nCombined Works Alongside Aimbot And Provides Better Recoil Control (Aimbot Must Be Enabled & Aimbot Mode = Cubic Bezier (xap-client)!)\nIf Aimbot Input Method Is Set To Controller, Only Combined Will Work!");
				}
				ImGui::EndChildFrame();
			}

			if (Features::RCS::RCSEnabled && !Features::RCS::AdvancedRCS) {
				ImGui::BeginChildFrame(18, ImVec2(WindowWidth - 220, 131), true);
				{
					ImGui::Spacing();

					if (Features::RCS::RCSMode == 1 && Features::Aimbot::AimbotMode == 1) {
						ImGui::Text("Selected Aimbot Mode Is Incompatible With Combined RCS! Switch To Standalone!");
					}
					if (Features::RCS::RCSMode == 1 && Features::Aimbot::AimbotMode == 2) {
						ImGui::Text("Selected Aimbot Mode Is Incompatible With Combined RCS! Switch To Standalone!");
					}

					else {

						ImGui::Text("Conditions");
						ImGui::Checkbox("On ADS Only?", &Features::RCS::OnADS);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Toggle when the RCS will take control\nEnabled = Only when aiming.\nDisabled = Always.");
						ImGui::Text("Intensity");
						if (Features::RCS::RCSMode == 0) {
							ImGui::MainSliderFloat("Pitch", &Features::RCS::PitchPower, 1, 50, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Pitch Power");
							ImGui::MainSliderFloat("Yaw", &Features::RCS::YawPower, 1, 50, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Yaw Power");
						}

						if (Features::RCS::RCSMode == 1 && Features::Aimbot::AimbotMode == 0) {
							ImGui::MainSliderFloat("Pitch Reduction %", &Features::RCS::PitchReduction, 0, 100, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced.");
							ImGui::MainSliderFloat("Yaw Reduction %", &Features::RCS::YawReduction, 0, 100, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced.");
						}
					}

					ImGui::EndChildFrame();
				}
			}

			if (Features::RCS::RCSEnabled && Features::RCS::AdvancedRCS) {
				ImGui::Text("Advanced RCS Enabled, Use The Advanced RCS Tab.");
			}
		}

		if (SelectedLegitbotSubTab == 5) {
			Advanced->AdvancedRCSTab(Myself->WeaponIndex);
		}

		if (SelectedLegitbotSubTab == 6) {
			if (!Features::RCS::RCSEnabled) {
				ImGui::Spacing();
				ImGui::Columns(3, "##weaponselection", false);
				if (ImGui::BeginChildFrame(7, ImVec2({ 95, 20 }), true)) {
					ImGui::Text("RCS Is Disabled.");
					ImGui::EndChildFrame();
				}
			}
			if (Features::RCS::RCSEnabled) {
				ImGui::Spacing();
				ImGui::Columns(3, "##rcsSelection", false);
				if (ImGui::BeginChildFrame(7, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
					ImGui::Checkbox("P2020##RCS", &Features::RCS::P2020);
					ImGui::Checkbox("RE-45 Auto##RCS", &Features::RCS::RE45);
					ImGui::Checkbox("Alternator SMG##RCS", &Features::RCS::Alternator);
					ImGui::Checkbox("R-99 SMG##RCS", &Features::RCS::R99);
					ImGui::Checkbox("R-301 Carbine##RCS", &Features::RCS::R301);
					ImGui::Checkbox("M600 Spitfire##RCS", &Features::RCS::Spitfire);
					ImGui::Checkbox("G7 Scout##RCS", &Features::RCS::G7);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(8, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
					ImGui::Checkbox("VK-47 Flatline##RCS", &Features::RCS::Flatline);
					ImGui::Checkbox("Prowler Burst SMG##RCS", &Features::RCS::Prowler);
					ImGui::Checkbox("Hemlock Burst AR##RCS", &Features::RCS::Hemlock);
					ImGui::Checkbox("30-30 Repeater##RCS", &Features::RCS::Repeater);
					ImGui::Checkbox("Rampage LMG##RCS", &Features::RCS::Rampage);
					ImGui::Checkbox("C.A.R SMG##RCS", &Features::RCS::CARSMG);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(9, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
					ImGui::Checkbox("Havoc Rifle##RCS", &Features::RCS::Havoc);
					ImGui::Checkbox("Devotion LMG##RCS", &Features::RCS::Devotion);
					ImGui::Checkbox("L-Star EMG##RCS", &Features::RCS::LSTAR);
					ImGui::Checkbox("Triple-Take##RCS", &Features::RCS::TripleTake);
					ImGui::Checkbox("Volt##RCS", &Features::RCS::Volt);
					ImGui::Checkbox("Nemesis Burst AR##RCS", &Features::RCS::Nemesis);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(10, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
					ImGui::Checkbox("Mozambique##RCS", &Features::RCS::Mozambique);
					ImGui::Checkbox("Peacekeeper##RCS", &Features::RCS::Peacekeeper);
					ImGui::Checkbox("Mastiff##RCS", &Features::RCS::Mastiff);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(11, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
					ImGui::Checkbox("Longbow DMR##RCS", &Features::RCS::Longbow);
					ImGui::Checkbox("Charge Rifle##RCS", &Features::RCS::ChargeRifle);
					ImGui::Checkbox("Sentinel##RCS", &Features::RCS::Sentinel);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(12, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
					ImGui::Checkbox("Wingman##RCS", &Features::RCS::Wingman);
					ImGui::Checkbox("EVA-8 Auto##RCS", &Features::RCS::EVA8);
					ImGui::Checkbox("Kraber .50-CAL Sniper##RCS", &Features::RCS::Kraber);
					ImGui::EndChildFrame();
				}
				ImGui::NextColumn();
			}
		}

		ImGui::EndChild();
		ImGui::EndChild();
	}

	void RenderRagebot() {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("RAGE##Rage", 0 == SelectedRagebotSubTab, ImVec2(205, 25)))
			SelectedRagebotSubTab = 0;
		ImGui::SameLine();
		if (SubTab("WEAPONS##Rage", 1 == SelectedRagebotSubTab, ImVec2(205, 25)))
			SelectedRagebotSubTab = 1;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedRagebotSubTab == 0) {
			ImGui::Columns(2, nullptr, false);
			ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 613, WindowHeight - 110), true);
			{
				ImGui::Spacing();
				ImGui::Text("Ragebot");
				ImGui::Checkbox("Enabled##RageAimbot", &Features::Ragebot::RageAimbot);
				if (Features::Ragebot::RageAimbot) {
					const char* AimMethodIndex[] = { "Memory", "Mouse" };
					ImGui::ComboBox("Aim Method##RageAimbot", &Features::Ragebot::AimMethod, AimMethodIndex, IM_ARRAYSIZE(AimMethodIndex));

					ImGui::Text("Selected Hitbox");
					ImGui::Checkbox("Closest To Crosshair##RageAimbot", &Features::Ragebot::ClosestHitbox);
					if (!Features::Ragebot::ClosestHitbox) {
						const char* HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
						int HitboxTypeIndex = static_cast<int>(Features::Ragebot::Hitbox);
						ImGui::ComboBox("Hitbox Type##RageAimbot", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Which bone the aimbot will aim at.");
						Features::Ragebot::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
					}
					const char* BindMethodIndex[] = { "Memory", "Keybinds", "Auto" };
					ImGui::ComboBox("Aim Bind Method##RageAimbot", &Features::Ragebot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
					if (Features::Ragebot::BindMethod == 0) { // OnFire and OnADS
						ImGui::Checkbox("On Fire##RageAimbot", &Features::Ragebot::OnFire);
						ImGui::SameLine();
						ImGui::Checkbox("On ADS##RageAimbot", &Features::Ragebot::OnADS);
					}
					if (Features::Ragebot::BindMethod == 1) { // Keybinds
						int AimBind = static_cast<int>(Features::Ragebot::AimBind);
						ImGui::ComboBox("Aim Bind##RageAimbot", &AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
						Features::Ragebot::AimBind = static_cast<InputKeyType>(AimBind);
						int ExtraBind = static_cast<int>(Features::Ragebot::ExtraBind);
						ImGui::ComboBox("Extra Bind##Aimbot", &ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
						Features::Ragebot::ExtraBind = static_cast<InputKeyType>(ExtraBind);
					}

					ImGui::Text("Aim Conditions");
					ImGui::Checkbox("Team Check##RageAimbot", &Features::Ragebot::TeamCheck);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
					ImGui::SameLine();
					ImGui::Checkbox("Visibility Check##RageAimbot", &Features::Ragebot::VisCheck);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Aims At Only Visible Enemies.");

					ImGui::Text("Priority");
					const char* PriorityIndex[] = { "Closest To Crosshair", "Closest To You" };
					ImGui::ComboBox("Target Priority##RageAimbot", &Features::Ragebot::Priority, PriorityIndex, IM_ARRAYSIZE(PriorityIndex));

					ImGui::Text("Automation");
					ImGui::Checkbox("Auto Shoot", &Features::Ragebot::AutoShoot);

					ImGui::MainSliderFloat("Hipfire Smoothing##RageAimbot", &Features::Ragebot::HipfireSmooth, 0, 0.99, "%.3f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Smoothing for the Aim-Assist whilst hipfiring.\nHigher = Smoother");

					ImGui::MainSliderFloat("ADS Smoothing##RageAimbot", &Features::Ragebot::ADSSmooth, 0, 0.99, "%.3f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Smoothing for the Aim-Assist whilst ADS.\nHigher = Smoother");

					ImGui::SliderInt("Delay##RageAimbot", &Features::Ragebot::Delay, 1, 50);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Delay time for the aimbot smoothing.");

					ImGui::Text("Prediction");
					ImGui::Checkbox("Predict Movement##RageAimbot", &Features::Ragebot::PredictMovement);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Predict target's movement");
					ImGui::SameLine();
					ImGui::Checkbox("Predict Bullet Drop##RageAimbot", &Features::Ragebot::PredictBulletDrop);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Predict weapon's bullet drop");
					ImGui::MainSliderFloat("Preditcion Amount", &Features::Ragebot::PreditcionAmount, 1, 500, "%.0f");

					ImGui::MainSliderFloat("FOV", &Features::Ragebot::FOV, 1, 90, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Field of View");
					ImGui::MainSliderFloat("Zoom Scale", &Features::Ragebot::ZoomScale, 0, 5, "%.1f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Field of View For Scopes");

					ImGui::MainSliderFloat("Hipfire Max Distance", &Features::Ragebot::HipfireDistance, 1, 500, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Maximum Hipfire distance for Aim-Assist to work");
					ImGui::MainSliderFloat("Zoom Max Distance", &Features::Ragebot::ZoomDistance, 1, 500, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Maximum ADS Distance for Aim-Assist to work");
					DoubleSpacing();
				}
				ImGui::EndChildFrame();
			}
			ImGui::NextColumn();
			if (Features::Ragebot::RageAimbot) {
				ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 630, WindowHeight - 110), true);
				{
					ImGui::Spacing();
					ImGui::Text("RCS");
					ImGui::Checkbox("Enabled##RageRCS", &Features::Ragebot::RageRCS);
					if (Features::Ragebot::RageRCS) {
						ImGui::MainSliderFloat("Recoil Reduction##RageRCS", &Features::Ragebot::RecoilRate, 1, 100, "%.1f");
					}

					ImGui::EndChildFrame();
				}
			}
		}

		if (SelectedRagebotSubTab == 1) {
			if (Features::Ragebot::RageAimbot) {
				ImGui::Spacing();
				ImGui::Columns(3, "##ragebotSelection", false);
				if (ImGui::BeginChildFrame(11, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
					ImGui::Checkbox("P2020##Ragebot", &Features::Ragebot::P2020);
					ImGui::Checkbox("RE-45 Auto##Ragebot", &Features::Ragebot::RE45);
					ImGui::Checkbox("Alternator SMG##Ragebot", &Features::Ragebot::Alternator);
					ImGui::Checkbox("R-99 SMG##Ragebot", &Features::Ragebot::R99);
					ImGui::Checkbox("R-301 Carbine##Ragebot", &Features::Ragebot::R301);
					ImGui::Checkbox("M600 Spitfire##Ragebot", &Features::Ragebot::Spitfire);
					ImGui::Checkbox("G7 Scout##Ragebot", &Features::Ragebot::G7);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(12, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
					ImGui::Checkbox("VK-47 Flatline##Ragebot", &Features::Ragebot::Flatline);
					ImGui::Checkbox("Prowler Burst SMG##Ragebot", &Features::Ragebot::Prowler);
					ImGui::Checkbox("Hemlock Burst AR##Ragebot", &Features::Ragebot::Hemlock);
					ImGui::Checkbox("30-30 Repeater##Ragebot", &Features::Ragebot::Repeater);
					ImGui::Checkbox("Rampage LMG##Ragebot", &Features::Ragebot::Rampage);
					ImGui::Checkbox("C.A.R SMG##Ragebot", &Features::Ragebot::CARSMG);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(13, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
					ImGui::Checkbox("Havoc Rifle##Ragebot", &Features::Ragebot::Havoc);
					ImGui::Checkbox("Devotion LMG##Ragebot", &Features::Ragebot::Devotion);
					ImGui::Checkbox("L-Star EMG##Ragebot", &Features::Ragebot::LSTAR);
					ImGui::Checkbox("Triple-Take##Ragebot", &Features::Ragebot::TripleTake);
					ImGui::Checkbox("Volt##Ragebot", &Features::Ragebot::Volt);
					ImGui::Checkbox("Nemesis Burst AR##Ragebot", &Features::Ragebot::Nemesis);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(14, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
					ImGui::Checkbox("Mozambique##Ragebot", &Features::Ragebot::Mozambique);
					ImGui::Checkbox("Peacekeeper##Ragebot", &Features::Ragebot::Peacekeeper);
					ImGui::Checkbox("Mastiff##Ragebot", &Features::Ragebot::Mastiff);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(15, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
					ImGui::Checkbox("Longbow DMR##Ragebot", &Features::Ragebot::Longbow);
					ImGui::Checkbox("Charge Rifle##Ragebot", &Features::Ragebot::ChargeRifle);
					ImGui::Checkbox("Sentinel##Ragebot", &Features::Ragebot::Sentinel);
					ImGui::EndChildFrame();
				}

				if (ImGui::BeginChildFrame(16, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
					ImGui::Checkbox("Wingman##Ragebot", &Features::Ragebot::Wingman);
					ImGui::Checkbox("EVA-8 Auto##Ragebot", &Features::Ragebot::EVA8);
					ImGui::Checkbox("Kraber .50-CAL Sniper##Ragebot", &Features::Ragebot::Kraber);
					ImGui::EndChildFrame();
				}
				ImGui::NextColumn();
			}
			if (!Features::Ragebot::RageAimbot) {
				ImGui::Text("Ragebot Is Disabled!");
			}
		}

		ImGui::EndChild();
		ImGui::EndChild();
	}

	//---------------------------------------------------------------------- Flickbot UI ----------------------------------------------------------------------

	void RenderFlickbot() {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("FLICKBOT##Flickbot", 0 == SelectedFlickbotSubTab, ImVec2(205, 25)))
			SelectedFlickbotSubTab = 0;
		ImGui::SameLine();
		if (SubTab("WEAPONS##Flickbot", 1 == SelectedFlickbotSubTab, ImVec2(205, 25)))
			SelectedFlickbotSubTab = 1;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedFlickbotSubTab == 0) {
			ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, WindowHeight - 110), true);
			{
				ImGui::Spacing();
				ImGui::Text("Flickbot");
				ImGui::Checkbox("Enabled##Flickbot", &Features::Flickbot::Flickbot);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Flick Crosshair To Players.\nHIGHLY recommended to use if you are: \nSemi-rage / Rage Cheating\nClose To The Targeted Player\nUsing A Shotgun");
				if (Features::Flickbot::Flickbot) {
					const char* FlickbotMethodIndex[] = { "Mouse", "Memory" };
					ImGui::ComboBox("Flickbot Method##Flickbot", &Features::Flickbot::FlickbotMethod, FlickbotMethodIndex, IM_ARRAYSIZE(FlickbotMethodIndex));
					ImGui::Text("Selected Hitbox");
					ImGui::Checkbox("Closest To Crosshair##Flickbot", &Features::Flickbot::ClosestHitbox);
					if (!Features::Flickbot::ClosestHitbox) {
						const char* HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
						int HitboxTypeIndex = static_cast<int>(Features::Flickbot::Hitbox);
						ImGui::ComboBox("Hitbox Type##Flickbot", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Which bone the aimbot will aim at.");
						Features::Flickbot::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
					}

					int FlickBind = static_cast<int>(Features::Flickbot::FlickBind);
					ImGui::ComboBox("Flick Bind##Flickbot", &FlickBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
					Features::Flickbot::FlickBind = static_cast<InputKeyType>(FlickBind);

					ImGui::Text("Flickbot Configurator");
					ImGui::Checkbox("Auto Shoot", &Features::Flickbot::AutoShoot);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Automatically Shoots When Flicking Onto Target.\nI Recommend Using Triggerbot Instead Of This.");
					if (Features::Flickbot::AutoShoot) {
						ImGui::SliderInt("Auto Shoot Delay##Flickbot", &Features::Flickbot::AutoShootDelay, 0, 500);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Delay Between Flicking To Target And Shooting.\nLow Value Recommended.");
					}

					if (Features::Flickbot::AutoShoot or Features::Triggerbot::Enabled) {
						ImGui::Checkbox("Flickback", &Features::Flickbot::FlickBack);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("After Flicking To Target, Your Camera Will Flick Back To Your Original Position.\nHIGHLY recommend NOT using this if you are legit cheating or if you have a high FOV set.\nOnly Works If Triggerbot Or Auto Shoot Is Enabled!");
						if (Features::Flickbot::FlickBack) {
							ImGui::SliderInt("Flickback Delay##Flickbot", &Features::Flickbot::FlickBackDelay, 0, 500);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Delay Between Flicking From Target Back To Original Camera Position.");
						}
					}

					ImGui::MainSliderFloat("Hipfire Smoothing##Flickbot", &Features::Flickbot::HipfireSmooth, 0, 0.99, "%.3f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Smoothing for the Flickbot whilst hipfiring.\nHigher = Smoother");

					ImGui::MainSliderFloat("ADS Smoothing##Flickbot", &Features::Flickbot::ADSSmooth, 0, 0.99, "%.3f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Smoothing for the Flickbot whilst ADS.\nHigher = Smoother");

					ImGui::Text("Prediction");
					ImGui::Checkbox("Predict Movement##Flickbot", &Features::Flickbot::PredictMovement);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Predict target's movement");
					ImGui::SameLine();
					ImGui::Checkbox("Predict Bullet Drop##Flickbot", &Features::Flickbot::PredictBulletDrop);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Predict weapon's bullet drop");

					ImGui::MainSliderFloat("FOV##Flickbot", &Features::Flickbot::FOV, 1, 90, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Field of View");
					ImGui::MainSliderFloat("Zoom Scale##Flickbot", &Features::Flickbot::ZoomScale, 0, 5, "%.1f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Field of View For Scopes");

					ImGui::MainSliderFloat("Hipfire Max Distance##Flickbot", &Features::Flickbot::HipfireDistance, 1, 500, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Maximum Hipfire distance for Flickbot to work");
					ImGui::MainSliderFloat("Zoom Max Distance##Flickbot", &Features::Flickbot::ZoomDistance, 1, 500, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Maximum ADS Distance for Flickbot to work");
					DoubleSpacing();
				}
				ImGui::EndChildFrame();
			}
			ImGui::NextColumn();
		}

		if (SelectedFlickbotSubTab == 1) {
			if (!Features::Flickbot::Flickbot) {
				ImGui::Text("Flickbot Is Disabled!");
			}

			if (Features::Flickbot::Flickbot) {
				ImGui::Spacing();
				ImGui::Columns(3, "##FlickbotSelection", false);
				if (ImGui::BeginChildFrame(7, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
					ImGui::Checkbox("P2020##Flickbot", &Features::Flickbot::P2020);
					ImGui::Checkbox("RE-45 Auto##Flickbot", &Features::Flickbot::RE45);
					ImGui::Checkbox("Alternator SMG##Flickbot", &Features::Flickbot::Alternator);
					ImGui::Checkbox("R-99 SMG##Flickbot", &Features::Flickbot::R99);
					ImGui::Checkbox("R-301 Carbine##Flickbot", &Features::Flickbot::R301);
					ImGui::Checkbox("M600 Spitfire##Flickbot", &Features::Flickbot::Spitfire);
					ImGui::Checkbox("G7 Scout##Flickbot", &Features::Flickbot::G7);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(8, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
					ImGui::Checkbox("VK-47 Flatline##Flickbot", &Features::Flickbot::Flatline);
					ImGui::Checkbox("Prowler Burst SMG##Flickbot", &Features::Flickbot::Prowler);
					ImGui::Checkbox("Hemlock Burst AR##Flickbot", &Features::Flickbot::Hemlock);
					ImGui::Checkbox("30-30 Repeater##Flickbot", &Features::Flickbot::Repeater);
					ImGui::Checkbox("Rampage LMG##Flickbot", &Features::Flickbot::Rampage);
					ImGui::Checkbox("C.A.R SMG##Flickbot", &Features::Flickbot::CARSMG);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(9, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
					ImGui::Checkbox("Havoc Rifle##Flickbot", &Features::Flickbot::Havoc);
					ImGui::Checkbox("Devotion LMG##Flickbot", &Features::Flickbot::Devotion);
					ImGui::Checkbox("L-Star EMG##Flickbot", &Features::Flickbot::LSTAR);
					ImGui::Checkbox("Triple-Take##Flickbot", &Features::Flickbot::TripleTake);
					ImGui::Checkbox("Volt##Flickbot", &Features::Flickbot::Volt);
					ImGui::Checkbox("Nemesis Burst AR##Flickbot", &Features::Flickbot::Nemesis);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(10, ImVec2({ 264, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
					ImGui::Checkbox("Mozambique##Flickbot", &Features::Flickbot::Mozambique);
					ImGui::Checkbox("Peacekeeper##Flickbot", &Features::Flickbot::Peacekeeper);
					ImGui::Checkbox("Mastiff##Flickbot", &Features::Flickbot::Mastiff);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(11, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
					ImGui::Checkbox("Longbow DMR##Flickbot", &Features::Flickbot::Longbow);
					ImGui::Checkbox("Charge Rifle##Flickbot", &Features::Flickbot::ChargeRifle);
					ImGui::Checkbox("Sentinel##Flickbot", &Features::Flickbot::Sentinel);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(12, ImVec2({ 237, 188 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
					ImGui::Checkbox("Wingman##Flickbot", &Features::Flickbot::Wingman);
					ImGui::Checkbox("EVA-8 Auto##Flickbot", &Features::Flickbot::EVA8);
					ImGui::Checkbox("Kraber .50-CAL Sniper##Flickbot", &Features::Flickbot::Kraber);
					ImGui::EndChildFrame();
				}
				ImGui::NextColumn();
			}
		}

		ImGui::EndChild();
		ImGui::EndChild();
	}

	//---------------------------------------------------------------------- Triggerbot UI ----------------------------------------------------------------------

	void RenderTriggerbot() {
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("TRIGGERBOT", 0 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
			SelectedTriggerbotSubTab = 0;
		ImGui::SameLine();
		if (SubTab("ADVANCED", 1 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
			SelectedTriggerbotSubTab = 1;
		ImGui::SameLine();
		if (SubTab("WEAPONS", 2 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
			SelectedTriggerbotSubTab = 2;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedTriggerbotSubTab == 0) {
			ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 43), true);
			{
				ImGui::Text("Triggerbot");
				ImGui::Checkbox("Enabled", &Features::Triggerbot::Enabled);
				ImGui::EndChildFrame();
			}

			if (Features::Triggerbot::Enabled && !Features::Triggerbot::AdvancedTriggerbot) {
				ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, 182), true);
				{
					ImGui::Spacing();
					const char* AttackMethodIndex[] = { "Mouse", "Memory" };
					ImGui::ComboBox("Attack Method", &Features::Triggerbot::AttackMethod, AttackMethodIndex, IM_ARRAYSIZE(AttackMethodIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("How Triggerbot Will Input A Click/Attack\nMemory Delay Is More Accurate Than Mouse\nBoth Support Controller");
					const char* BindMethodIndex[] = { "Memory", "Keybind" };
					ImGui::ComboBox("Bind Method", &Features::Triggerbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
					if (Features::Triggerbot::BindMethod == 0) {
						ImGui::Checkbox("On ADS Only?", &Features::Triggerbot::OnADS);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Fire only when ADS");
						if (Features::Triggerbot::OnADS) {
							ImGui::SameLine();
							ImGui::Checkbox("Always On For Shotguns", &Features::Triggerbot::HipfireShotguns);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Overrides The Triggerbot Condition (OnADS?) For Shotguns Only.\nSimple Terms: Other Guns Require ADS, Shotguns Will Not.");
						}
					}

					if (Features::Triggerbot::BindMethod == 1) {
						int TriggerBind = static_cast<int>(Features::Triggerbot::TriggerBind);
						ImGui::ComboBox("Triggerbot Bind", &TriggerBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
						Features::Triggerbot::TriggerBind = static_cast<InputKeyType>(TriggerBind);
					}

					ImGui::SliderInt("Triggerbot Delay", &Features::Triggerbot::Delay, 0, 150);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Triggerbot's Delay Time\nNote: Not Perfect!\nProcessing Time Affects This, Don't Test Settings In The Firing Range!");
					ImGui::MainSliderFloat("Triggerbot Range", &Features::Triggerbot::Range, 0, 1000, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Triggerbot's activation range");
					ImGui::Spacing();
					ImGui::EndChildFrame();
				}
			}

			if (Features::Triggerbot::Enabled && Features::Triggerbot::AdvancedTriggerbot) {
				ImGui::Text("Advanced Triggerbot Is Enabled!");
			}
		}

		if (SelectedTriggerbotSubTab == 1) {
			Advanced->AdvancedTriggerbotTab(Myself->WeaponIndex);
		}

		if (SelectedTriggerbotSubTab == 2) {
			if (!Features::Triggerbot::Enabled) {
				ImGui::Text("Triggerbot Is Disabled!");
			}

			if (Features::Triggerbot::Enabled) {
				ImGui::Spacing();
				ImGui::Columns(3, "##triggerbotSelection", false);
				if (ImGui::BeginChildFrame(7, ImVec2({ 264, 240 }), true)) {
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
					ImGui::Checkbox("P2020##Triggerbot", &Features::Triggerbot::P2020);
					ImGui::Checkbox("RE-45 Auto##Triggerbot", &Features::Triggerbot::RE45);
					ImGui::Checkbox("Alternator SMG##Triggerbot", &Features::Triggerbot::Alternator);
					ImGui::Checkbox("R-99 SMG##Triggerbot", &Features::Triggerbot::R99);
					ImGui::Checkbox("R-301 Carbine##Triggerbot", &Features::Triggerbot::R301);
					ImGui::Checkbox("M600 Spitfire##Triggerbot", &Features::Triggerbot::Spitfire);
					ImGui::Checkbox("G7 Scout##Triggerbot", &Features::Triggerbot::G7);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(8, ImVec2({ 264, 240 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
					ImGui::Checkbox("VK-47 Flatline##Triggerbot", &Features::Triggerbot::Flatline);
					ImGui::Checkbox("Prowler Burst SMG##Triggerbot", &Features::Triggerbot::Prowler);
					ImGui::Checkbox("Hemlock Burst AR##Triggerbot", &Features::Triggerbot::Hemlock);
					ImGui::Checkbox("30-30 Repeater##Triggerbot", &Features::Triggerbot::Repeater);
					ImGui::Checkbox("Rampage LMG##Triggerbot", &Features::Triggerbot::Rampage);
					ImGui::Checkbox("C.A.R SMG##Triggerbot", &Features::Triggerbot::CARSMG);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(9, ImVec2({ 264, 240 }), true)) {
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
					ImGui::Checkbox("Havoc Rifle##Triggerbot", &Features::Triggerbot::Havoc);
					ImGui::Checkbox("Devotion LMG##Triggerbot", &Features::Triggerbot::Devotion);
					ImGui::Checkbox("L-Star EMG##Triggerbot", &Features::Triggerbot::LSTAR);
					ImGui::Checkbox("Triple-Take##Triggerbot", &Features::Triggerbot::TripleTake);
					ImGui::Checkbox("Volt##Triggerbot", &Features::Triggerbot::Volt);
					ImGui::Checkbox("Nemesis Burst AR##Triggerbot", &Features::Triggerbot::Nemesis);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(10, ImVec2({ 264, 240 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
					ImGui::Checkbox("Mozambique##Triggerbot", &Features::Triggerbot::Mozambique);
					ImGui::Checkbox("Peacekeeper##Triggerbot", &Features::Triggerbot::Peacekeeper);
					ImGui::Checkbox("Mastiff##Triggerbot", &Features::Triggerbot::Mastiff);
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn();

				if (ImGui::BeginChildFrame(11, ImVec2({ 237, 240 }), true)) {
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
					ImGui::Checkbox("Longbow DMR##Triggerbot", &Features::Triggerbot::Longbow);
					ImGui::Checkbox("Charge Rifle##Triggerbot", &Features::Triggerbot::ChargeRifle);
					ImGui::Checkbox("Sentinel##Triggerbot", &Features::Triggerbot::Sentinel);
					ImGui::EndChildFrame();
				}
				if (ImGui::BeginChildFrame(12, ImVec2({ 237, 240 }), true)) {
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
					ImGui::Checkbox("Wingman##Triggerbot", &Features::Triggerbot::Wingman);
					ImGui::Checkbox("EVA-8 Auto##Triggerbot", &Features::Triggerbot::EVA8);
					ImGui::Checkbox("Kraber .50-CAL Sniper##Triggerbot", &Features::Triggerbot::Kraber);
					ImGui::EndChildFrame();
				}
				ImGui::NextColumn();
			}
		}
		ImGui::EndChild();
		ImGui::EndChild();
	}

	//---------------------------------------------------------------------- Glow UI ----------------------------------------------------------------------

	void RenderGlow() {
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("PLAYER", 0 == SelectedGlowSubTab, ImVec2(205, 25)))
			SelectedGlowSubTab = 0;
		ImGui::SameLine();
		if (SubTab("ITEM", 1 == SelectedGlowSubTab, ImVec2(205, 25)))
			SelectedGlowSubTab = 1;
		ImGui::SameLine();
		if (SubTab("VIEWMODEl", 2 == SelectedGlowSubTab, ImVec2(205, 25)))
			SelectedGlowSubTab = 2;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedGlowSubTab == 0) {
			ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 83), true);
			{
				ImGui::Spacing();
				ImGui::Text("Glow");
				ImGui::Checkbox("Player Glow", &Features::Glow::NewGlow);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle Player Glow.");
				if (Features::Glow::NewGlow) {
					ImGui::SameLine();
					ImGui::Checkbox("Knocked Check", &Features::Glow::KnockedCheck);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Will Also Glow Knocked Players");
					ImGui::MainSliderFloat("Glow Max Distance", &Features::Glow::GlowMaxDistance, 0, 1000, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Only those in range will glow");
				}
				ImGui::EndChildFrame();
			}

			if (Features::Glow::NewGlow) {
				ImGui::Columns(2, "Player Glow Column", false);
				ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 613, WindowHeight - 198), true);
				{
					ImGui::Spacing();
					ImGui::Text("Settings");
					ImGui::SliderInt("Border Thickness##Glow", &Features::Glow::GlowRadius, 32, 200);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("How Thick The Border Is Around A Player.");

					const char* GlowBodyStyleIndex[] = { "None", "Pink", "Pink Visible Only", "Pulsing 1", "Pulsing Line Invisible Only", "Dark Pulsing Line", "Sharp Pulsing Visible", "Sharp Pulsing", "Pulsing Red Line", "Fast Pulsing Invisible Only", "Pulsing Up Visible Only", "Solid Pulsing", "Solid Pulsing 2", "Bright", "Bright 2", "Light", "Light Solid", "Red Pulsing Visible Only", "Wave", "Shaded Visible", "Wireframe", "Wireframe Visible Only", "Black", "Black Visible Only" };
					ImGui::ComboBox("Body Style", &Features::Glow::BodyStyle, GlowBodyStyleIndex, IM_ARRAYSIZE(GlowBodyStyleIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Changes The Player's Body Style.");

					const char* GlowOutlineStyleIndex[] = { "None", "Bright", "Bright Invisible Only", "Dark", "Pink", "White", "Gold Flashing", "Gold", "Brown", "Wave", "Red Visible Only", "Red Bright", "Heartbeat Visible Only", "Green Invisible Only", "Visible Only", "Bright Orange", "Red 2" };
					ImGui::ComboBox("Outline Style", &Features::Glow::OutlineStyle, GlowOutlineStyleIndex, IM_ARRAYSIZE(GlowOutlineStyleIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Changes The Player's Outline Style.");
					ImGui::EndChildFrame();
				}

				ImGui::NextColumn(); // Right

				ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 630, WindowHeight - 198), true);
				{
					ImGui::Spacing();
					const char* GlowColorModeIndex[] = { "Shield Based", "Custom Color" };
					ImGui::ComboBox("Color Mode", &Features::Glow::GlowColorMode, GlowColorModeIndex, IM_ARRAYSIZE(GlowColorModeIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What Color The Glow Will Be.\nShield Based = What Shield The Player Has\nCustom Color = Whatever Color You Want.");

					if (Features::Glow::GlowColorMode == 0) {
						const char* GlowShieldModeIndex[] = { "Current Shield", "Max Shield" };
						ImGui::ComboBox("Shield Mode", &Features::Glow::GlowColorShieldMode, GlowShieldModeIndex, IM_ARRAYSIZE(GlowShieldModeIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("What Color The Glow Will Change To\nCurrent Shield = Player's Current Shield Points\nMax Shield = Player's Max Shield Points.");
						ImGui::ColorEdit3("Red Shield##GlowColor", Features::Colors::Enemy::RedShieldColor, ColorEditFlags);
						ImGui::SameLine();
						ImGui::ColorEdit3("Purple Shield##GlowColor", Features::Colors::Enemy::PurpleShieldColor, ColorEditFlags);
						ImGui::SameLine();
						ImGui::ColorEdit3("Blue Shield##GlowColor", Features::Colors::Enemy::BlueShieldColor, ColorEditFlags);
						ImGui::ColorEdit3("Grey Shield##GlowColor", Features::Colors::Enemy::GreyShieldColor, ColorEditFlags);
						ImGui::SameLine();
					}

					if (Features::Glow::GlowColorMode == 0) {
						ImGui::ColorEdit3("Low HP Color##GlowColor", Features::Colors::Enemy::LowGlowColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("What Color The Glow Will Change To When The Player Has No Shield.");
						ImGui::SameLine();
					}

					if (Features::Glow::GlowColorMode == 1) {
						ImGui::ColorEdit3("Invisible Color##GlowColor", Features::Colors::Enemy::InvisibleGlowColor, ColorEditFlags);
						ImGui::SameLine();
					}

					ImGui::ColorEdit3("Visible Color##GlowColor", Features::Colors::Enemy::VisibleGlowColor, ColorEditFlags);
					if (!Features::Glow::KnockedCheck) {
						if (Features::Glow::GlowColorMode == 1) {
							ImGui::SameLine();
						}
						ImGui::ColorEdit3("Knocked Color##GlowColor", Features::Colors::Enemy::KnockedGlowColor, ColorEditFlags);
					}
					ImGui::EndChildFrame();
				}
			}
		}

		if (SelectedGlowSubTab == 1) {
			ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, WindowHeight - 110), true);
			{
				ImGui::Spacing();
				ImGui::Text("Item Glow");
				ImGui::Checkbox("Enabled##Item", &Features::Glow::Item::ItemGlow);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Items Will Glow Through Walls.\nIncludes Deathboxes.");
				if (Features::Glow::Item::ItemGlow) {
					const char* ItemGlowBodyStyleIndex[] = { "Clear", "Light", "Solid", "Light To Dark Fade" };
					ImGui::ComboBox("Inside Style", &Features::Glow::Item::SelectedInsideStyle, ItemGlowBodyStyleIndex, IM_ARRAYSIZE(ItemGlowBodyStyleIndex));
					const char* ItemGlowOutlineIndex[] = { "None", "Light 1", "Light 2", "Solid", "Gold", "Orange", "Pulsing", "Light Red (Visible Only)", "Red", "Fading (Visible Only)", "Soft", "Visible Only" };
					ImGui::ComboBox("Outline Style", &Features::Glow::Item::SelectedOutlineStyle, ItemGlowOutlineIndex, IM_ARRAYSIZE(ItemGlowOutlineIndex));
					ImGui::SliderInt("Glow Thickness", &Features::Glow::Item::ItemGlowThickness, 0, 250);
				}

				ImGui::EndChildFrame();
			}
		}

		if (SelectedGlowSubTab == 2) {
			ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, WindowHeight - 110), true);
			{
				ImGui::Spacing();
				ImGui::Text("Viewmodel Glow");
				ImGui::Checkbox("Enabled", &Features::Glow::ViewModelGlow);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle ViewModel Glow.");
				if (Features::Glow::ViewModelGlow) {
					const char* ViewmodelGlowIndex[] = { "Cyan Outline", "Light Red Outline", "White Outline", "Orange Outline", "Yellow Outline", "Solid Green", "Solid Orange", "Solid Yellow", "Solid Yellow Pulsing", "Solid Purple", "Solid Light Blue", "Solid Light Grey", "Solid White", "Solid Cyan", "Solid Hot Pink", "Solid Light Yellow", "Solid Light Orange", "Solid Light Green", "Solid Black", "Chrome" };
					ImGui::ComboBox("Selected Color", &Features::Glow::ViewModelGlowCombo, ViewmodelGlowIndex, IM_ARRAYSIZE(ViewmodelGlowIndex));
				}

				ImGui::EndChildFrame();
			}
		}
		ImGui::EndChild();
		ImGui::EndChild();
	}

	//---------------------------------------------------------------------- ESP UI ----------------------------------------------------------------------

	void RenderESP(Overlay OverlayWindow) {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("PLAYER", 0 == SelectedESPSubTabLeft, ImVec2(135, 25)))
			SelectedESPSubTabLeft = 0;
		ImGui::SameLine();
		if (SubTab("TEAM", 1 == SelectedESPSubTabLeft, ImVec2(135, 25)))
			SelectedESPSubTabLeft = 1;
		ImGui::SameLine();
		if (SubTab("SETTINGS", 2 == SelectedESPSubTabLeft, ImVec2(135, 25)))
			SelectedESPSubTabLeft = 2;
		ImGui::SameLine();
		if (SubTab("COLORS", 0 == SelectedESPSubTabRight, ImVec2(92, 25)))
			SelectedESPSubTabRight = 0;
		ImGui::SameLine();
		if (SubTab("RADAR", 1 == SelectedESPSubTabRight, ImVec2(92, 25)))
			SelectedESPSubTabRight = 1;
		ImGui::SameLine();
		if (SubTab("CROSSHAIR", 2 == SelectedESPSubTabRight, ImVec2(92, 25)))
			SelectedESPSubTabRight = 2;
		ImGui::SameLine();
		if (SubTab("OTHER", 3 == SelectedESPSubTabRight, ImVec2(92, 25)))
			SelectedESPSubTabRight = 3;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();
		ImGui::Columns(2, "ESP Columns", false);
		ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 613, WindowHeight - 110), true);
		{
			ImGui::Spacing();
			if (SelectedESPSubTabLeft == 0) {
				ImGui::Text("Player ESP");
				ImGui::Checkbox("Draw Players", &Features::Sense::Enemy::DrawEnemy);

				if (Features::Sense::Enemy::DrawEnemy) {
					ImGui::Text("Boxes");
					ImGui::Checkbox("Draw Boxes", &Features::Sense::Enemy::DrawBoxes);
					if (Features::Sense::Enemy::DrawBoxes) {
						ImGui::SameLine();
						ImGui::Checkbox("Box Outline", &Features::Sense::Enemy::BoxOutline);
						const char* BoxTypeIndex[] = { "2D", "2D Filled", "2D Corners" };
						ImGui::ComboBox("Box Type", &Features::Sense::Enemy::BoxType, BoxTypeIndex, IM_ARRAYSIZE(BoxTypeIndex));

						ImGui::MainSliderFloat("Box Thickness", &Features::Sense::Enemy::BoxThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the boxes");
					}

					ImGui::Text("Tracers");
					ImGui::Checkbox("Draw Tracers", &Features::Sense::Enemy::DrawTracers);
					if (Features::Sense::Enemy::DrawTracers) {
						const char* TracerPos[] = { "Top", "Crosshair", "Bottom" };
						ImGui::ComboBox("Tracer Position", &Features::Sense::Enemy::TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Where tracers will be drawn from.");
						const char* TracerBones[] = { "Top", "Bottom" };
						ImGui::ComboBox("Tracer Bone", &Features::Sense::Enemy::TracerBone, TracerBones, IM_ARRAYSIZE(TracerBones));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Where tracers will be drawn to.");
						ImGui::MainSliderFloat("Tracer Thickness", &Features::Sense::Enemy::TracerThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the tracers");
					}

					ImGui::Text("Skeleton");
					ImGui::Checkbox("Draw Skeleton", &Features::Sense::Enemy::DrawSkeleton);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw the enemies skeletons (Spooky)");
					if (Features::Sense::Enemy::DrawSkeleton) {
						ImGui::SameLine();
						ImGui::Checkbox("Skeleton Outline", &Features::Sense::Enemy::SkeletonOutline);
						const char* SkeletonDetail[] = { "Detailed", "Simple" };
						ImGui::ComboBox("Skeleton Detail", &Features::Sense::Enemy::SkeletonDetail, SkeletonDetail, IM_ARRAYSIZE(SkeletonDetail));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("How Detailed The Skeleton Is.");
						ImGui::MainSliderFloat("Skeleton Thickness", &Features::Sense::Enemy::SkeletonThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the bones");
					}

					ImGui::Text("Head Circle");
					ImGui::Checkbox("Draw Head Circle", &Features::Sense::Enemy::DrawHeadCircle);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw the enemies Head");
					if (Features::Sense::Enemy::DrawHeadCircle) {
						ImGui::SameLine();
						ImGui::Checkbox("Head Circle Outline", &Features::Sense::Enemy::HeadCircleOutline);
						ImGui::MainSliderFloat("Head Circle Thickness", &Features::Sense::Enemy::HeadCircleThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the Circle");
					}

					ImGui::Text("Info Bars");
					ImGui::Checkbox("Draw Bars", &Features::Sense::Enemy::DrawBars);
					if (Features::Sense::Enemy::DrawBars) {
						const char* BarStyleIndex[] = { "Side", "Top", "Seer" };
						ImGui::ComboBox("Bar Style", &Features::Sense::Enemy::BarStyle, BarStyleIndex, IM_ARRAYSIZE(BarStyleIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("What Style Of Health + Shield Bar Will Be.\nSeer = Seer's Ability.");

						if (!Features::Sense::Enemy::BarStyle == 2) {
							Features::Sense::Enemy::DrawSeer = false;
						}

						if (Features::Sense::Enemy::BarStyle == 0 or Features::Sense::Enemy::BarStyle == 1) {
							ImGui::Checkbox("Draw Health Bar", &Features::Sense::Enemy::HealthBar);
							ImGui::SameLine();
							ImGui::Checkbox("Draw Shield Bar", &Features::Sense::Enemy::ShieldBar);
						}

						/*if (Features::Sense::Enemy::BarStyle == 0 or Features::Sense::Enemy::BarStyle == 1) {
							const char* BarModeIndex[] = { "Health Only", "Shield Only", "Health & Shield" };
							ImGui::ComboBox("Bar Mode", &Features::Sense::Enemy::BarMode, BarModeIndex, IM_ARRAYSIZE(BarModeIndex));
						}*/

						if (Features::Sense::Enemy::BarStyle == 2) { // Seer
							ImGui::Checkbox("Draw Seer", &Features::Sense::Enemy::DrawSeer);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
						}

						if (Features::Sense::Enemy::BarStyle == 1) { // Top
							ImGui::MainSliderFloat("Bar Height", &Features::Sense::Enemy::BarHeight, 5, 20, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Height of the enemy bar");
							ImGui::MainSliderFloat("Bar Width", &Features::Sense::Enemy::BarWidth, 10, 125, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Width of the enemy bar");
						}

						if (Features::Sense::Enemy::BarStyle == 1) { // Top
							ImGui::MainSliderFloat("Bar Thickness", &Features::Sense::Enemy::BarThickness, 1, 10, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Thickness of the health/shield bar");
						}
					}

					ImGui::Text("Player Info");
					ImGui::Checkbox("Draw Names", &Features::Sense::Enemy::DrawNames);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show enemies names.");

					ImGui::Checkbox("Draw Distance", &Features::Sense::Enemy::DrawDistance);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show how far away the enemies are");

					ImGui::Checkbox("Draw Legend", &Features::Sense::Enemy::DrawLegend);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show What Legend The Enemy Is Playing As.");

					ImGui::Checkbox("Draw Weapon", &Features::Sense::Enemy::DrawWeapon);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show what weapon an enemy is currently holding.");

					ImGui::Checkbox("Draw Status", &Features::Sense::Enemy::DrawStatus);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw enemies current health and armor");
					if (Features::Sense::Enemy::DrawStatus) {
						ImGui::SameLine();
						ImGui::Checkbox("Show Max Values", &Features::Sense::Enemy::ShowMaxStatusValues);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Adds their max health and max armor at the end.");
					}

					DoubleSpacing();
				}
			}

			if (SelectedESPSubTabLeft == 1) {
				ImGui::Text("Team ESP");
				ImGui::Checkbox("Draw Teammates", &Features::Sense::Teammate::DrawTeam);

				if (Features::Sense::Teammate::DrawTeam) {
					ImGui::Text("Boxes");
					ImGui::Checkbox("Draw Boxes", &Features::Sense::Teammate::DrawBoxes);
					if (Features::Sense::Teammate::DrawBoxes) {
						ImGui::SameLine();
						ImGui::Checkbox("Box Outline", &Features::Sense::Teammate::BoxOutline);
						const char* BoxTypeIndex[] = { "2D", "2D Filled", "2D Corners" };
						ImGui::ComboBox("Box Type", &Features::Sense::Teammate::BoxType, BoxTypeIndex, IM_ARRAYSIZE(BoxTypeIndex));

						ImGui::MainSliderFloat("Box Thickness", &Features::Sense::Teammate::BoxThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the boxes");
					}

					ImGui::Text("Tracers");
					ImGui::Checkbox("Draw Tracers", &Features::Sense::Teammate::DrawTracers);
					if (Features::Sense::Teammate::DrawTracers) {
						const char* TracerPos[] = { "Top", "Crosshair", "Bottom" };
						ImGui::ComboBox("Tracer Position", &Features::Sense::Teammate::TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Where tracers will be drawn from.");
						const char* TracerBones[] = { "Top", "Bottom" };
						ImGui::ComboBox("Tracer Bone", &Features::Sense::Teammate::TracerBone, TracerBones, IM_ARRAYSIZE(TracerBones));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Where tracers will be drawn to.");
						ImGui::MainSliderFloat("Tracer Thickness", &Features::Sense::Teammate::TracerThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the tracers");
					}

					ImGui::Text("Skeleton");
					ImGui::Checkbox("Draw Skeleton", &Features::Sense::Teammate::DrawSkeleton);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw the teammates skeletons (Spooky)");
					if (Features::Sense::Teammate::DrawSkeleton) {
						ImGui::SameLine();
						ImGui::Checkbox("Skeleton Outline", &Features::Sense::Teammate::SkeletonOutline);
						ImGui::MainSliderFloat("Skeleton Thickness", &Features::Sense::Teammate::SkeletonThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the bones");
					}

					ImGui::Text("Head Circle");
					ImGui::Checkbox("Draw Head Circle", &Features::Sense::Teammate::DrawHeadCircle);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw the enemies Head");
					if (Features::Sense::Teammate::DrawHeadCircle) {
						ImGui::SameLine();
						ImGui::Checkbox("Head Circle Outline", &Features::Sense::Teammate::HeadCircleOutline);
						ImGui::MainSliderFloat("Head Circle Thickness", &Features::Sense::Teammate::HeadCircleThickness, 1, 10, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes the thickness of the Circle");
					}

					ImGui::Text("Info Bars");
					ImGui::Checkbox("Draw Bars", &Features::Sense::Teammate::DrawBars);
					if (Features::Sense::Teammate::DrawBars) {
						const char* BarStyleIndex[] = { "Side", "Top", "Seer" };
						ImGui::ComboBox("Bar Style", &Features::Sense::Teammate::BarStyle, BarStyleIndex, IM_ARRAYSIZE(BarStyleIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Where AND What Style Of Health + Shield Bar Will Be.\nSeer = Seer's Ability.");

						if (!Features::Sense::Teammate::BarStyle == 2) {
							Features::Sense::Teammate::DrawSeer = false;
						}

						if (Features::Sense::Teammate::BarStyle == 0 or Features::Sense::Teammate::BarStyle == 1) {
							const char* BarModeIndex[] = { "Health Only", "Shield Only", "Health & Shield" };
							ImGui::ComboBox("Bar Mode", &Features::Sense::Teammate::BarMode, BarModeIndex, IM_ARRAYSIZE(BarModeIndex));
						}

						if (Features::Sense::Teammate::BarStyle == 2) { // Seer
							ImGui::Checkbox("Draw Seer", &Features::Sense::Teammate::DrawSeer);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
						}

						if (Features::Sense::Teammate::BarStyle == 1) { // Top
							ImGui::MainSliderFloat("Bar Height", &Features::Sense::Teammate::BarHeight, 5, 20, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Height of the Teammate bar");
							ImGui::MainSliderFloat("Bar Width", &Features::Sense::Teammate::BarWidth, 10, 125, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Width of the Teammate bar");
						}

						if (Features::Sense::Teammate::BarStyle == 1) { // Top
							ImGui::MainSliderFloat("Bar Thickness", &Features::Sense::Teammate::BarThickness, 1, 10, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Thickness of the health/shield bar");
						}
					}

					ImGui::Text("Player Info");
					ImGui::Checkbox("Draw Names", &Features::Sense::Teammate::DrawNames);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show enemies names.");

					ImGui::Checkbox("Draw Distance", &Features::Sense::Teammate::DrawDistance);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show how far away the enemies are");

					ImGui::Checkbox("Draw Legend", &Features::Sense::Teammate::DrawLegend);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show What Legend The Teammate Is Playing As.");

					ImGui::Checkbox("Draw Weapon", &Features::Sense::Teammate::DrawWeapon);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Show what weapon an Teammate is currently holding.");

					ImGui::Checkbox("Draw Status", &Features::Sense::Teammate::DrawStatus);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw enemies current health and armor");
					if (Features::Sense::Teammate::DrawStatus) {
						ImGui::SameLine();
						ImGui::Checkbox("Show Max Values", &Features::Sense::Teammate::ShowMaxStatusValues);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Adds their max health and max armor at the end.");
					}

					DoubleSpacing();
				}
			}

			if (SelectedESPSubTabLeft == 2) {
				ImGui::Spacing();
				ImGui::Text("Settings");
				ImGui::Checkbox("Knocked Check", &Features::Sense::KnockedCheck);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Draw's ESP On Knocked Players");
				ImGui::SameLine();
				ImGui::Checkbox("Visibility Check", &Features::Sense::VisibilityCheck);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Draw's ESP ONLY On Visible Players");

				ImGui::MainSliderFloat("ESP Max Distance", &Features::Sense::ESPMaxDistance, 0, 1000, "%.0f");
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Only those in range will be shown.");
				ImGui::Checkbox("Text Outline", &Features::Sense::TextOutline);

				ImGui::Text("Position Changer");
				const char* PositionIndex[] = { "Top 1", "Top 2", "Bottom 1", "Bottom 2", "Bottom 3" };
				ImGui::ComboBox("Name Position", &Features::Sense::Positions::NamePosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
				ImGui::ComboBox("Distance Position", &Features::Sense::Positions::DistancePosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
				ImGui::ComboBox("Legend Position", &Features::Sense::Positions::LegendPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
				ImGui::ComboBox("Weapon Position", &Features::Sense::Positions::WeaponPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
				ImGui::ComboBox("Status Position", &Features::Sense::Positions::StatusPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
			}

			ImGui::EndChildFrame();
		}

		ImGui::NextColumn();

		ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 630, WindowHeight - 110), true);
		{
			if (SelectedESPSubTabRight == 0) {
				ImGui::Spacing();
				if (SelectedESPSubTabLeft == 0 or SelectedESPSubTabLeft == 2) {
					ImGui::Text("Colors - Players");
					if (Features::Sense::Enemy::DrawBoxes) {
						ImGui::Text("Boxes");
						ImGui::ColorEdit4("Visible##EnemyBoxColor", Features::Colors::Enemy::VisibleBoxColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Box Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyBoxColor", Features::Colors::Enemy::InvisibleBoxColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Box Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyBoxColor", Features::Colors::Enemy::KnockedBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Box Knocked Color");
						}

						if (Features::Sense::Enemy::BoxType == 1) {
							//ImGui::SameLine();
							ImGui::ColorEdit4("Filled Visible##Enemy", Features::Colors::Enemy::VisibleFilledBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Filled Box Visible Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Filled Invisible##Enemy", Features::Colors::Enemy::InvisibleFilledBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Filled Box Invisible Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Filled Knocked##Enemy", Features::Colors::Enemy::KnockedFilledBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Filled Box Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawTracers) {
						ImGui::Text("Tracers");
						ImGui::ColorEdit4("Visible##EnemyTracer", Features::Colors::Enemy::VisibleTracerColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Tracer Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyTracer", Features::Colors::Enemy::InvisibleTracerColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Tracer Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyTracer", Features::Colors::Enemy::KnockedTracerColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Tracer Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawSkeleton) {
						ImGui::Text("Skeleton");
						ImGui::ColorEdit4("Visible##EnemySkeletonColor", Features::Colors::Enemy::VisibleSkeletonColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Skeleton Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemySkeletonColor", Features::Colors::Enemy::InvisibleSkeletonColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Skeleton Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemySkeletonColor", Features::Colors::Enemy::KnockedSkeletonColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Skeleton Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawHeadCircle) {
						ImGui::Text("Head Circle");
						ImGui::ColorEdit4("Visible##EnemyHeadCircleColor", Features::Colors::Enemy::VisibleHeadCircleColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Head Circle Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyHeadCircleColor", Features::Colors::Enemy::InvisibleHeadCircleColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Head Circle Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyHeadCircleColor", Features::Colors::Enemy::KnockedHeadCircleColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Head Circle Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawBars) {
						if (Features::Sense::Enemy::BarMode == 0 or Features::Sense::Enemy::BarMode == 1) {
							ImGui::Text("Info Bars");
							const char* BarColorModeIndex[] = { "Max Shield", "Current Shield" };
							ImGui::ComboBox("Bar Color", &Features::Sense::Enemy::BarColorMode, BarColorModeIndex, IM_ARRAYSIZE(BarColorModeIndex));
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("What Color The Shield Bar Will Be.");
						}
					}

					if (Features::Sense::Enemy::DrawNames) {
						ImGui::Text("Names");
						ImGui::ColorEdit4("Visible##EnemyNameColor", Features::Colors::Enemy::VisibleNameColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Name Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyNameColor", Features::Colors::Enemy::InvisibleNameColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Name Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyNameColor", Features::Colors::Enemy::KnockedNameColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Name Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawDistance) {
						ImGui::Text("Distance");
						ImGui::ColorEdit4("Visible##EnemyDistanceColor", Features::Colors::Enemy::VisibleDistanceColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Distance Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyDistanceColor", Features::Colors::Enemy::InvisibleDistanceColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Distance Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyDistanceColor", Features::Colors::Enemy::KnockedDistanceColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Distance Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawLegend) {
						ImGui::Text("Legend");
						ImGui::ColorEdit4("Visible##EnemyLegendColor", Features::Colors::Enemy::VisibleLegendColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Legend Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##EnemyLegendColor", Features::Colors::Enemy::InvisibleLegendColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Legend Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##EnemyLegendColor", Features::Colors::Enemy::KnockedLegendColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Legend Knocked Color");
						}
					}

					if (Features::Sense::Enemy::DrawWeapon) {
						ImGui::Text("Weapon");
						const char* WeaponColorModeIndex[] = { "Single Color", "Multiple Colors" };
						ImGui::ComboBox("Weapon Color Mode", &Features::Colors::WeaponColorMode, WeaponColorModeIndex, IM_ARRAYSIZE(WeaponColorModeIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes The Weapon Text Color To The Ammo Type Of The Weapon.");

						if (Features::Colors::WeaponColorMode == 0) {
							ImGui::ColorEdit4("Visible##EnemyWeaponColor", Features::Colors::Enemy::VisibleWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Weapon Visible Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Invisible##EnemyWeaponColor", Features::Colors::Enemy::InvisibleWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Weapon Invisible Color");
							if (!Features::Sense::KnockedCheck) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Knocked##EnemyWeaponColor", Features::Colors::Enemy::KnockedWeaponColor, ColorEditFlags);
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Weapon Knocked Color");
							}
						}

						if (Features::Colors::WeaponColorMode == 1) {
							ImGui::ColorEdit4("Light##ESPEnemyWeaponColor", Features::Colors::Enemy::LightWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Light Weapon Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Heavy##ESPEnemyWeaponColor", Features::Colors::Enemy::HeavyWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Heavy Weapon Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Energy##ESPEnemyWeaponColor", Features::Colors::Enemy::EnergyWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Energy Weapon Color");

							ImGui::ColorEdit4("Shotguns##ESPEnemyWeaponColor", Features::Colors::Enemy::ShotgunWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Shotgun Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Snipers##ESPEnemyWeaponColor", Features::Colors::Enemy::SniperWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Sniper Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Legendary##ESPEnemyWeaponColor", Features::Colors::Enemy::LegendaryWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Legendary Weapon Color");

							ImGui::ColorEdit4("Throwables##ESPEnemyWeapon", Features::Colors::Enemy::ThrowableWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Throwable Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Melee##ESPEnemyWeapon", Features::Colors::Enemy::MeleeWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Melee Color");
						}
					}
				}

				if (SelectedESPSubTabLeft == 1) {
					ImGui::Text("Colors - Teammates");
					if (Features::Sense::Teammate::DrawBoxes) {
						ImGui::Text("Boxes");
						ImGui::ColorEdit4("Visible##TeammateBoxColor", Features::Colors::Teammate::VisibleBoxColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Box Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateBoxColor", Features::Colors::Teammate::InvisibleBoxColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Box Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateBoxColor", Features::Colors::Teammate::KnockedBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Box Knocked Color");
						}

						if (Features::Sense::Teammate::BoxType == 1) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Filled Visible##Teammate", Features::Colors::Teammate::VisibleFilledBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Filled Box Visible Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Filled Invisible##Teammate", Features::Colors::Teammate::InvisibleFilledBoxColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Filled Box Invisible Color");
							if (!Features::Sense::KnockedCheck) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Filled Knocked##Teammate", Features::Colors::Teammate::KnockedFilledBoxColor, ColorEditFlags);
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Filled Box Knocked Color");
							}
						}
					}

					if (Features::Sense::Teammate::DrawTracers) {
						ImGui::Text("Tracers");
						ImGui::ColorEdit4("Visible##TeammateTracer", Features::Colors::Teammate::VisibleTracerColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Tracer Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateTracer", Features::Colors::Teammate::InvisibleTracerColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Tracer Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateTracer", Features::Colors::Teammate::KnockedTracerColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Tracer Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawSkeleton) {
						ImGui::Text("Skeleton");
						ImGui::ColorEdit4("Visible##TeammateSkeletonColor", Features::Colors::Teammate::VisibleSkeletonColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Skeleton Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateSkeletonColor", Features::Colors::Teammate::InvisibleSkeletonColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Skeleton Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateSkeletonColor", Features::Colors::Teammate::KnockedSkeletonColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Skeleton Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawHeadCircle) {
						ImGui::Text("Head Circle");
						ImGui::ColorEdit4("Visible##TeammateHeadCircleColor", Features::Colors::Teammate::VisibleHeadCircleColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Head Circle Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateHeadCircleColor", Features::Colors::Teammate::InvisibleHeadCircleColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Head Circle Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateHeadCircleColor", Features::Colors::Teammate::KnockedHeadCircleColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Head Circle Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawBars) {
						if (Features::Sense::Teammate::BarMode == 0 or Features::Sense::Teammate::BarMode == 1) {
							ImGui::Text("Info Bars");
							const char* BarColorModeIndex[] = { "Max Shield", "Current Shield" };
							ImGui::ComboBox("Bar Color", &Features::Sense::Teammate::BarColorMode, BarColorModeIndex, IM_ARRAYSIZE(BarColorModeIndex));
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("What Color The Shield Bar Will Be.");
						}
					}

					if (Features::Sense::Teammate::DrawNames) {
						ImGui::Text("Names");
						ImGui::ColorEdit4("Visible##TeammateNameColor", Features::Colors::Teammate::VisibleNameColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Name Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateNameColor", Features::Colors::Teammate::InvisibleNameColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Name Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateNameColor", Features::Colors::Teammate::KnockedNameColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Name Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawDistance) {
						ImGui::Text("Distance");
						ImGui::ColorEdit4("Visible##TeammateDistanceColor", Features::Colors::Teammate::VisibleDistanceColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Distance Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateDistanceColor", Features::Colors::Teammate::InvisibleDistanceColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Distance Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateDistanceColor", Features::Colors::Teammate::KnockedDistanceColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Distance Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawLegend) {
						ImGui::Text("Legend");
						ImGui::ColorEdit4("Visible##TeammateLegendColor", Features::Colors::Teammate::VisibleLegendColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Legend Visible Color");
						ImGui::SameLine();
						ImGui::ColorEdit4("Invisible##TeammateLegendColor", Features::Colors::Teammate::InvisibleLegendColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Legend Invisible Color");
						if (!Features::Sense::KnockedCheck) {
							ImGui::SameLine();
							ImGui::ColorEdit4("Knocked##TeammateLegendColor", Features::Colors::Teammate::KnockedLegendColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Legend Knocked Color");
						}
					}

					if (Features::Sense::Teammate::DrawWeapon) {
						ImGui::Text("Weapon");
						const char* WeaponColorModeIndex[] = { "Single Color", "Multiple Colors" };
						ImGui::ComboBox("Weapon Color Mode", &Features::Colors::WeaponColorMode, WeaponColorModeIndex, IM_ARRAYSIZE(WeaponColorModeIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Changes The Weapon Text Color To The Ammo Type Of The Weapon.");

						if (Features::Colors::WeaponColorMode == 0) {
							ImGui::ColorEdit4("Visible##TeammateWeaponColor", Features::Colors::Teammate::VisibleWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Weapon Visible Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Invisible##TeammateWeaponColor", Features::Colors::Teammate::InvisibleWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Weapon Invisible Color");
							if (!Features::Sense::KnockedCheck) {
								ImGui::SameLine();
								ImGui::ColorEdit4("Knocked##TeammateWeaponColor", Features::Colors::Teammate::KnockedWeaponColor, ColorEditFlags);
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Weapon Knocked Color");
							}
						}

						if (Features::Colors::WeaponColorMode == 1) {
							ImGui::ColorEdit4("Light##ESPTeammateWeaponColor", Features::Colors::Teammate::LightWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Light Weapon Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Heavy##ESPTeammateWeaponColor", Features::Colors::Teammate::HeavyWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Heavy Weapon Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Energy##ESPTeammateWeaponColor", Features::Colors::Teammate::EnergyWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Energy Weapon Color");

							ImGui::ColorEdit4("Shotguns##ESPTeammateWeaponColor", Features::Colors::Teammate::ShotgunWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Shotgun Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Snipers##ESPTeammateWeaponColor", Features::Colors::Teammate::SniperWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Sniper Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Legendary##ESPTeammateWeaponColor", Features::Colors::Teammate::LegendaryWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Legendary Weapon Color");

							ImGui::ColorEdit4("Throwables##ESPTeammateWeapon", Features::Colors::Teammate::ThrowableWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Throwable Color");
							ImGui::SameLine();
							ImGui::ColorEdit4("Melee##ESPTeammateWeapon", Features::Colors::Teammate::MeleeWeaponColor, ColorEditFlags);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Melee Color");
						}
					}
				}
			}

			if (SelectedESPSubTabRight == 1) {
				ImGui::Spacing();
				ImGui::Text("Mini Map");
				ImGui::Checkbox("Enabled##MiniMap", &Features::Radar::MiniMap);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle a mini map radar");
				if (Features::Radar::MiniMap) {
					ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "May not be on-point.");
					ImGui::Separator();
					ImGui::Text("Range");
					ImGui::MainSliderFloat("Mini Map Radar Range", &Features::Radar::MiniMapRange, 1, 200, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Mini Map range from 0 to 200.");

					ImGui::Text("Radar Settings");
					ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Turn on Mini Map Guides and allign with your player's arrow on the in-game minimap.");
					ImGui::SliderInt("Mini Map Width", &Features::Radar::MiniMapScaleX, 0, 2560);
					ImGui::SliderInt("Mini Map Height", &Features::Radar::MiniMapScaleY, 0, 1440);
					ImGui::Checkbox("Mini Map Guides", &Features::Radar::MiniMapGuides);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Toggle the mini map guides.");
					ImGui::MainSliderFloat("Radar Window Rounding", &Features::Radar::RadarRounding, 0, 30, "%0.1f");

					ImGui::Text("Enemy Identifier");
					const char* EnemyIdentifierIndex[] = { "Arrowhead", "Circle" };
					ImGui::ComboBox("Selected Enemy Identifier", &Features::Radar::EnemyIdentifier, EnemyIdentifierIndex, IM_ARRAYSIZE(EnemyIdentifierIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What Shape The Enemy Will Be On The Radar");
					ImGui::SliderInt("Enemy Identifier Size", &Features::Radar::IdentifierSize, 0, 10);
					ImGui::Checkbox("Draw Enemy View Angles", &Features::Radar::EnemyViewAngles);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Draw A Line Showing The Direction (View Angle) The Enemy Is Looking");
					if (Features::Radar::EnemyViewAngles) {
						ImGui::MainSliderFloat("Enemy View Angles Length", &Features::Radar::EnemyViewAnglesLength, 1, 100, "%0.f");
						ImGui::ColorEdit4("View Angle Line Color##Radar", Features::Radar::EnemyViewAnglesColor, ColorEditFlags);
					}
					ImGui::ColorEdit4("Background Color##Radar", Features::Radar::BackgroundColor, ColorEditFlags);
				}

				ImGui::Text("ALGS Style Map");
				ImGui::Checkbox("Enabled##BigMap", &Features::Radar::BigMap);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle the ALGS Style Map.");
				if (Features::Radar::BigMap) {
					int BigMapBind = static_cast<int>(Features::Radar::BigMapBind);
					ImGui::ComboBox("Bind##BigMap", &BigMapBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Bind For ALGS Map");
					Features::Radar::BigMapBind = static_cast<InputKeyType>(BigMapBind);
					ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Make sure to close out of the in-game map before activating or you will crash!");
				}
			}

			if (SelectedESPSubTabRight == 2) {
				ImGui::Spacing();
				ImGui::Text("Crosshair");
				ImGui::Checkbox("Draw Crosshair", &Features::Sense::DrawCrosshair);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Draws a crosshair");
				if (Features::Sense::DrawCrosshair) {
					ImGui::MainSliderFloat("Crosshair Size", &Features::Sense::CrosshairSize, 0, 1000, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Changes the size of the crosshair");
					ImGui::MainSliderFloat("Crosshair Thickness", &Features::Sense::CrosshairThickness, 1, 50, "%.0f");
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Changes the Crosshair's thickness");
					ImGui::ColorEdit4("Crosshair Color", Features::Colors::CrosshairColor, ColorEditFlags);
				}
			}
			if (SelectedESPSubTabRight == 3) {
				ImGui::Spacing();
				ImGui::Text("Spectator List");
				ImGui::Checkbox("Draw Spectator List", &Features::Sense::ShowSpectators);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Show Spectators");

				ImGui::Text("Watermark");
				ImGui::Checkbox("Draw Watermark", &Features::Watermark::Watermark);
				if (Features::Watermark::Watermark) {
					ImGui::Text("Watermark Settings");
					ImGui::Checkbox("Display Name", &Features::Watermark::Name);
					if (Features::Watermark::Name) {
						ImGui::ColorEdit4("Name Color", Features::Watermark::NameColor, ColorEditFlags);
					}
					ImGui::Checkbox("Display Spectators Number", &Features::Watermark::Spectators);
					ImGui::Checkbox("Display Processing Speed", &Features::Watermark::ProcessingSpeed);
					ImGui::Checkbox("Display Game FPS", &Features::Watermark::GameFPS);
				}

				ImGui::Text("Warning Text");
				ImGui::Checkbox("Draw Spectator Warning", &Features::Sense::DrawSpectatorWarning);
				ImGui::Checkbox("Draw Visible Warning", &Features::Sense::DrawVisibleWarning);
				if (Features::Sense::DrawSpectatorWarning or Features::Sense::DrawVisibleWarning) {
					ImGui::Checkbox("Warning Text Outline", &Features::Sense::WarningTextOutline);
					int ScreenWidth;
					int ScreenHeight;
					OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
					ImGui::SliderInt("Warning Text Position X", &Features::Sense::WarningTextX, 0, ScreenWidth);
					ImGui::SliderInt("Warning Text Position Y", &Features::Sense::WarningTextY, 0, ScreenHeight);
					if (ImGui::Button("Auto Set Position", ImVec2(125, 25))) {
						int AutoWidth = ScreenWidth / 2;
						int AutoHeight = (ScreenHeight / 2) + 80;
						Features::Sense::WarningTextX = AutoWidth;
						Features::Sense::WarningTextY = AutoHeight;
					}

					if (Features::Sense::DrawSpectatorWarning) {
						ImGui::ColorEdit4("Spectator Warning", Features::Colors::SpectatorWarningColor, ColorEditFlags);
						ImGui::SameLine();
					}

					if (Features::Sense::DrawVisibleWarning) {
						ImGui::ColorEdit4("Visible Warning", Features::Colors::VisibleWarningColor, ColorEditFlags);
					}
				}
			}
			ImGui::EndChildFrame();
		}
		ImGui::EndChild();
		ImGui::EndChild();
	}

	void RenderMisc() {
		ImGui::SetCursorPos(ImVec2(15, 15));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::Spacing();
		ImGui::SameLine();

		ImGui::Columns(2, nullptr, false);
		ImGui::Text("Movement");
		ImGui::BeginChildFrame(1, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2), true);
		{
			ImGui::Spacing();
			ImGui::Text("Movement");
			ImGui::Checkbox("SuperGlide", &Features::Misc::SuperGlide);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Hold spacebar whilst climbing over a wall/object to gain extra speed\nNote: Will Not Always Succeed!");
			if (Features::Misc::SuperGlide) {
				const char* SuperGlideModeIndex[] = { "Manual", "Automatic" };
				ImGui::ComboBox("SuperGlide Mode", &Features::Misc::SuperGlideMode, SuperGlideModeIndex, IM_ARRAYSIZE(SuperGlideModeIndex));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("SuperGlide Mode.\nManual: Requires Space To Be Held Down (Keyboard Only)\nAutomatic: Automatically SuperGlides Over Any Wall/Surface (Supports Controller)");

				const char* SuperGlideFPSIndex[] = { "75", "144", "240" };
				ImGui::ComboBox("SuperGlide FPS", &Features::Misc::SuperGlideFPS, SuperGlideFPSIndex, IM_ARRAYSIZE(SuperGlideFPSIndex));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Set this to your average in-game FPS to make SuperGlide more accurate!");
			}

			ImGui::Checkbox("BHop", &Features::Misc::BHop);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Bouncy!\nActivates Whilst Holding A Selected Keybind & Space.");
			if (Features::Misc::BHop) {
				int BHopBind = static_cast<int>(Features::Misc::BHopBind);
				ImGui::ComboBox("Bind##BHop", &BHopBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Bind For BHop.\nHold The Selected Key To Toggle BHop, You Will Still Need To Hold Space.");
				Features::Misc::BHopBind = static_cast<InputKeyType>(BHopBind);
				ImGui::SliderInt("BHop Delay", &Features::Misc::BHopDelay, 1, 200);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Delay Between Inputting Space.");
			}

			ImGui::Checkbox("Auto Wall Jump", &Features::Misc::WallJump);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Automatically Jump From A Wall Using A Key Bind.");
			if (Features::Misc::WallJump) {
				int WallJumpBind = static_cast<int>(Features::Misc::WallJumpBind);
				ImGui::ComboBox("Wall Jump Bind", &WallJumpBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Bind For Auto Wall Jump.\nYou Must Let Go Of Forward (W) Before Pressing!.");
				Features::Misc::WallJumpBind = static_cast<InputKeyType>(WallJumpBind);
			}
			
			ImGui::Checkbox("Auto Tap Strafe", &Features::Misc::AutoTapStrafe);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Automatic Tap Strafe.\nUseful In The Air/For Superglides");

			DoubleSpacing();

			ImGui::EndChildFrame();
		}

		ImGui::Text("Camera");
		ImGui::BeginChildFrame(2, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2), true);
		{
			ImGui::Spacing();
			ImGui::Text("Camera");
			ImGui::Checkbox("Quick Turn", &Features::Misc::QuickTurn);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Quickly Turn Your Camera.\nDoes Not Have Smoothing!");
			if (Features::Misc::QuickTurn) {
				int QuickTurnBind = static_cast<int>(Features::Misc::QuickTurnBind);
				ImGui::ComboBox("QuickTurn Bind", &QuickTurnBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
				Features::Misc::QuickTurnBind = static_cast<InputKeyType>(QuickTurnBind);
				ImGui::SliderInt("QuickTurn Angle", &Features::Misc::QuickTurnAngle, 1, 360);
			}

			ImGui::EndChildFrame();
		}

		ImGui::NextColumn();

		ImGui::Text("Weapon");
		ImGui::BeginChildFrame(3, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2), true);
		{
			ImGui::Spacing();
			ImGui::Text("Rapid Fire");
			ImGui::Checkbox("Enable Rapid Fire", &Features::Misc::RapidFire);
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("Turns Semi-Automatic + Slow Firing Weapons Automatic.");
			if (Features::Misc::RapidFire) {
				ImGui::SliderInt("Rapid Fire Delay", &Features::Misc::RapidFireDelay, 25, 200);
				int RapidFireBind = static_cast<int>(Features::Misc::RapidFireBind);
				ImGui::ComboBox("Rapid Fire Bind", &RapidFireBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
				Features::Misc::RapidFireBind = static_cast<InputKeyType>(RapidFireBind);

				ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
				ImGui::Checkbox("P2020##Misc", &Features::Misc::RapidP2020);
				ImGui::SameLine();
				ImGui::Checkbox("R-301 Carbine##Misc", &Features::Misc::RapidR301);
				ImGui::SameLine();
				ImGui::Checkbox("G7 Scout##Misc", &Features::Misc::RapidG7);

				ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
				ImGui::Checkbox("VK-47 Flatline##Misc", &Features::Misc::RapidFlatline);
				ImGui::SameLine();
				ImGui::Checkbox("Prowler Burst SMG##Misc", &Features::Misc::RapidProwler);
				ImGui::SameLine();
				ImGui::Checkbox("Hemlock Burst AR##Misc", &Features::Misc::RapidHemlock);

				ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
				ImGui::Checkbox("Nemesis Burst AR##Misc", &Features::Misc::RapidNemesis);

				ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
				ImGui::Checkbox("Mozambique##Misc", &Features::Misc::RapidMozambique);

				ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
				ImGui::Checkbox("Wingman##Misc", &Features::Misc::RapidWingman);
				ImGui::SameLine();
				ImGui::Checkbox("EVA-8 Auto##Misc", &Features::Misc::RapidEVA8);
			}
			DoubleSpacing();
			ImGui::EndChildFrame();
		}

		ImGui::Text("Skin Changer");
		ImGui::BeginChildFrame(5, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2), true);
		{
			ImGui::Spacing();
			ImGui::Text("Skin Changer");
			ImGui::Checkbox("Enabled", &Features::Misc::SkinChanger);
			if (Features::Misc::SkinChanger) {
				ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
				ImGui::SliderInt("P2020", &Features::Misc::SkinP2020, 0, 10);
				ImGui::SliderInt("RE-45 Auto", &Features::Misc::SkinRE45, 0, 16);
				ImGui::SliderInt("Alternator SMG", &Features::Misc::SkinALTERNATOR, 0, 16);
				ImGui::SliderInt("R-99 SMG", &Features::Misc::SkinR99, 0, 16);
				ImGui::SliderInt("R-301 Carbine", &Features::Misc::SkinR301, 0, 18);
				ImGui::SliderInt("M600 Spitfire", &Features::Misc::SkinSPITFIRE, 0, 16);
				ImGui::SliderInt("G7 Scout", &Features::Misc::SkinG7, 0, 21);

				ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
				ImGui::SliderInt("VK-47 Flatline", &Features::Misc::SkinFLATLINE, 0, 20);
				ImGui::SliderInt("Hemlock Burst AR", &Features::Misc::SkinHEMLOCK, 0, 18);
				ImGui::SliderInt("Prowler Burst SMG", &Features::Misc::SkinPROWLER, 0, 11);
				ImGui::SliderInt("30-30 Repeater", &Features::Misc::SkinREPEATER, 0, 11);
				ImGui::SliderInt("Rampage LMG", &Features::Misc::SkinRAMPAGE, 0, 11);
				ImGui::SliderInt("C.A.R SMG", &Features::Misc::SkinCAR, 0, 11);

				ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
				ImGui::SliderInt("Havoc Rifle", &Features::Misc::SkinHAVOC, 0, 14);
				ImGui::SliderInt("L-Star EMG", &Features::Misc::SkinLSTAR, 0, 11);
				ImGui::SliderInt("Triple-Take", &Features::Misc::SkinTRIPLETAKE, 0, 11);
				ImGui::SliderInt("Volt", &Features::Misc::SkinVOLT, 0, 14);
				ImGui::SliderInt("Nemesis Burst AR", &Features::Misc::SkinNEMESIS, 0, 9);

				ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
				ImGui::SliderInt("Mozambique", &Features::Misc::SkinMOZAMBIQUE, 0, 11);
				ImGui::SliderInt("Peacekeeper", &Features::Misc::SkinPEACEKEEPER, 0, 16);
				ImGui::SliderInt("Mastiff", &Features::Misc::SkinMASTIFF, 0, 11);

				ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
				ImGui::SliderInt("Wingman", &Features::Misc::SkinWINGMAN, 0, 11);
				ImGui::SliderInt("Longbow DMR", &Features::Misc::SkinLONGBOW, 0, 11);
				ImGui::SliderInt("Charge Rifle", &Features::Misc::SkinCHARGE_RIFLE, 0, 11);
				ImGui::SliderInt("Sentinel", &Features::Misc::SkinSENTINEL, 0, 10);

				ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
				ImGui::SliderInt("EVA-8 Auto", &Features::Misc::SkinEVA8, 0, 11);
				ImGui::SliderInt("Devotion LMG", &Features::Misc::SkinDEVOTION, 0, 11);
				ImGui::SliderInt("Bocek Compound Bow", &Features::Misc::SkinBOCEK, 0, 11);
				ImGui::SliderInt("Kraber .50-CAL Sniper", &Features::Misc::SkinKRABER, 0, 11);

				DoubleSpacing();
			}

			ImGui::EndChildFrame();
		}

		ImGui::EndChild();
	}

	void RenderSettings() {
		ImVec2 TabSize;
		TabSize = ImGui::GetWindowSize();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginGroup();
		ImGui::Spacing();
		ImGui::SameLine();
		if (SubTab("SETTINGS", 0 == SelectedSettingsSubTab, ImVec2(205, 25)))
			SelectedSettingsSubTab = 0;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15, 35 });

		ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

		ImGui::Separator();
		DoubleSpacing();

		if (SelectedSettingsSubTab == 0) {
			ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, WindowHeight - 110), true);
			{
				ImGui::Spacing();
				ImGui::Text("Menu Settings");

				int MenuBind = static_cast<int>(Features::Settings::MenuBind);
				ImGui::ComboBox("Menu Bind", &MenuBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Key Bind For Opening The Menu");
				Features::Settings::MenuBind = static_cast<InputKeyType>(MenuBind);

				ImGui::Text("Overlay Settings");
				ImGui::Checkbox("Enable Overlay", &Features::Settings::OverlayEnabled);

				if (Features::Settings::OverlayEnabled) {
					ImGui::Checkbox("Enable ESP", &Features::Settings::ESPEnabled);
					ImGui::Checkbox("Anti Aliased Lines", &Features::Settings::AntiAliasedLines);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("Smoothes Out ESP Features\nDisabled Looks More Pixelated Than Enabled");
					ImGui::Checkbox("Draw Keybind Notifier", &Features::Settings::ShowKeybinds);
					if (Features::Settings::ShowKeybinds) {
						ImGui::ColorEdit4("Keybind Color", Features::Settings::KeybindColor, ColorEditFlags);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("The Color Of The Text Indicating When A Key Is Active");
					}
				}

				/*ImGui::Checkbox("Dead Check", &Features::Settings::DeadCheck);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Displays Glow & ESP If You Are Dead/Spectating");*/

				ImGui::Checkbox("FPS Cap", &Features::Settings::FPSCap);
				if (Features::Settings::FPSCap) {
					ImGui::SliderInt("Max FPS", &Features::Settings::CappedFPS, 30, 999);
				}

				/*if (ImGui::Button("Close Cheat", ImVec2(100, 20))) {
					std::cout << "Closing Cheat!" << std::endl;
					exit(0);
				}*/
				// Removed this since it doesn't delete the temp binary if the run.sh script is executed

				// Dev
				Space();
				ImGui::Text("Dev Options");
				ImGui::Checkbox("Enable Dev Options", &Features::Dev::Enabled);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("For Experimenting/Development/Updating");
				if (Features::Dev::Enabled) {
					ImGui::Checkbox("Draw Local Player Weapon IDs", &Features::Dev::LocalWeapon);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("For Updating Weapons.hpp");
					ImGui::Checkbox("Draw Player Weapon IDs", &Features::Dev::EnemyWeapon);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("For Updating/Testing Weapons.hpp");
					ImGui::Checkbox("Draw Player Bone Ids", &Features::Dev::SkeletonIDs);
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("For Finding Bone IDs\nHitboxType.hpp\nNOTE: ID VARIES DEPENDING ON THE MODEL/LEGEND");
					if (Features::Dev::SkeletonIDs) {
						ImGui::SliderInt("Bone Index Range", &Features::Dev::BoneRange, 0, 250);
					}
				}

				ImGui::EndChildFrame();
			}
		}

		ImGui::EndChild();
		ImGui::EndChild();
	}

	const void SetStyle() { // Testing - duplicated for some reason....
		// Style
		float Alpha = 1.0f;
		float DisabledAlpha = 1.0f;
		float TabMinWidthForCloseButton = 0.0f;
		float ColumnsMinSpacing = 6.0f;
		ImVec2 WindowPadding = ImVec2(8.00f, 8.00f);
		ImVec2 FramePadding = ImVec2(5.00f, 2.00f);
		ImVec2 CellPadding = ImVec2(6.00f, 6.00f);
		ImVec2 ItemSpacing = ImVec2(6.00f, 6.00f);
		ImVec2 ItemInnerSpacing = ImVec2(6.00f, 6.00f);
		ImVec2 TouchExtraPadding = ImVec2(0.00f, 0.00f);
		ImVec2 SelectableTextAlign = ImVec2(0.0f, 0.0f);
		ImVec2 ButtonTextAlign = ImVec2(0.5f, 0.5f);
		ImVec2 WindowTitleAlign = ImVec2(0.5f, 0.5f);
		ImVec2 WindowMinSize = ImVec2(20.0f, 20.0f);
		int IndentSpacing = 25;
		int ScrollbarSize = 0;
		int GrabMinSize = 10;
		int WindowBorderSize = 1;
		int ChildBorderSize = 1;
		int PopupBorderSize = 1;
		int FrameBorderSize = 1;
		int TabBorderSize = 1;
		int WindowRounding = 7;
		int ChildRounding = 4;
		int FrameRounding = 4;
		int PopupRounding = 4;
		int ScrollbarRounding = 9;
		int GrabRounding = 3;
		int LogSliderDeadzone = 4;
		int TabRounding = 4;

		WindowPadding = ImVec2(12.0f, 12.0f);
		WindowRounding = 11.5f;
		WindowBorderSize = 0.0f;
		WindowMinSize = ImVec2(20.0f, 20.0f);
		WindowTitleAlign = ImVec2(0.5f, 0.5f);
		ChildRounding = 11.0f;
		ChildBorderSize = 1.0f;
		PopupRounding = 0.0f;
		PopupBorderSize = 1.0f;
		FramePadding = ImVec2(12.0f, 3.0f);
		FrameRounding = 11.89999961853027f;
		FrameBorderSize = 1.0f;
		ItemSpacing = ImVec2(4.300000223734863f, 5.5f);
		ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
		CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
		IndentSpacing = 0.0f;
		ColumnsMinSpacing = 4.900000095367432f;
		ScrollbarSize = 11.60000038146973f;
		ScrollbarRounding = 0.0f;
		GrabMinSize = 3.700000047683716f;
		GrabRounding = 20.0f;
		TabRounding = 0.0f;
		TabBorderSize = 0.0f;
		TabMinWidthForCloseButton = 0.0f;

		// Colors
		ImVec4 Text = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		ImVec4 TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		ImVec4 WindowBg = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		ImVec4 ChildBg = ImVec4(0.19f, 0.19f, 0.19f, 0.20);
		ImVec4 PopupBg = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		ImVec4 Border = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 BorderShadow = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		ImVec4 FrameBg = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		ImVec4 FrameBgHovered = ImVec4(0.19f, 0.19f, 0.19f, 0.20);
		ImVec4 FrameBgActive = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		ImVec4 TitleBg = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 TitleBgActive = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		ImVec4 TitleBgCollapsed = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 MenuBarBg = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		ImVec4 ScrollbarBg = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
		ImVec4 ScrollbarGrab = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		ImVec4 ScrollbarGrabHovered = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		ImVec4 ScrollbarGrabActive = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		ImVec4 CheckMark = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		ImVec4 SliderGrab = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		ImVec4 SliderGrabActive = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		ImVec4 Button = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		ImVec4 ButtonHovered = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		ImVec4 ButtonActive = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		ImVec4 Header = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		ImVec4 HeaderHovered = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		ImVec4 HeaderActive = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		ImVec4 Separator = ImVec4(0.03f, 0.66f, 0.90f, 1.00f);
		ImVec4 SeparatorHovered = ImVec4(0.03f, 0.66f, 0.90f, 1.00f);
		ImVec4 SeparatorActive = ImVec4(0.03f, 0.66f, 0.90f, 1.00f);
		ImVec4 ResizeGrip = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		ImVec4 ResizeGripHovered = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		ImVec4 ResizeGripActive = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		ImVec4 Tab = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		ImVec4 TabHovered = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		ImVec4 TabActive = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		ImVec4 TabUnfocused = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		ImVec4 TabUnfocusedActive = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		ImVec4 PlotLines = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 PlotLinesHovered = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 PlotHistogram = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 PlotHistogramHovered = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 TableHeaderBg = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		ImVec4 TableBorderStrong = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		ImVec4 TableBorderLight = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		ImVec4 TableRowBg = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		ImVec4 TableRowBgAlt = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		ImVec4 TextSelectedBg = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		ImVec4 DragDropTarget = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		ImVec4 NavHighlight = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ImVec4 NavWindowingHighlight = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		ImVec4 NavWindowingDimBg = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		ImVec4 ModalWindowDimBg = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

		Text = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		TextDisabled = ImVec4(0.27f, 0.31f, 0.45f, 1.0f);
		WindowBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		ChildBg = ImVec4(0.09f, 0.10f, 0.11f, 1.0f);
		PopupBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		Border = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		BorderShadow = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		FrameBg = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		FrameBgHovered = ImVec4(0.09f, 0.10f, 0.11f, 1.0f);
		FrameBgActive = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		TitleBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
		TitleBgActive = ImVec4(0.047f, 0.05f, 0.07f, 1.0f);
		TitleBgCollapsed = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		MenuBarBg = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
		ScrollbarBg = ImVec4(0.04f, 0.05f, 0.07f, 0.0f);
		ScrollbarGrab = ImVec4(0.11f, 0.13f, 0.14f, 0.0f);
		ScrollbarGrabHovered = ImVec4(0.15f, 0.16f, 0.19f, 0.0f);
		ScrollbarGrabActive = ImVec4(0.11f, 0.13f, 0.14f, 0.0f);
		CheckMark = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		SliderGrab = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
		SliderGrabActive = ImVec4(1.0f, 0.79f, 0.49f, 1.0f);
		Button = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
		ButtonHovered = ImVec4(0.18f, 0.18f, 0.19f, 1.0f);
		ButtonActive = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		Header = ImVec4(0.14f, 0.16f, 0.20f, 1.0f);
		HeaderHovered = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
		HeaderActive = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		Separator = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		SeparatorHovered = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		SeparatorActive = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		ResizeGrip = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
		ResizeGripHovered = ImVec4(0.97f, 1.0f, 0.49f, 1.0f);
		ResizeGripActive = ImVec4(0.99f, 1.0f, 0.99f, 1.0f);
		Tab = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		TabHovered = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
		TabActive = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
		TabUnfocused = ImVec4(0.07f, 0.08f, 0.10f, 1.0f);
		TabUnfocusedActive = ImVec4(0.12f, 0.27f, 0.57f, 1.0f);
		PlotLines = ImVec4(0.52f, 0.60f, 0.70f, 1.0f);
		PlotLinesHovered = ImVec4(0.03f, 0.98f, 0.98f, 1.0f);
		PlotHistogram = ImVec4(0.88f, 0.79f, 0.56f, 1.0f);
		PlotHistogramHovered = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
		TableHeaderBg = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
		TableBorderStrong = ImVec4(0.04f, 0.05f, 0.07f, 1.0f);
		TableBorderLight = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		TableRowBg = ImVec4(0.11f, 0.13f, 0.14f, 1.0f);
		TableRowBgAlt = ImVec4(0.09f, 0.10f, 0.12f, 1.0f);
		TextSelectedBg = ImVec4(0.93f, 0.93f, 0.93f, 1.0f);
		DragDropTarget = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
		NavHighlight = ImVec4(0.26f, 0.28f, 1.0f, 1.0f);
		NavWindowingHighlight = ImVec4(0.49f, 0.51f, 1.0f, 1.0f);
		NavWindowingDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);
		ModalWindowDimBg = ImVec4(0.19f, 0.17f, 0.54f, 0.50f);

		ImGuiStyle& style = ImGui::GetStyle();
		//style.SliderThickness = 0.2f;
		//style.SliderContrast = 0.5f;
		//style.SliderValuePos = ImVec2(0.5f, 0.5f); not exist
		style.FramePadding = ImVec2(4.0f, 12.0f); // 改变滑动条的厚度
		style.GrabMinSize = 20.0f;                // 改变滑动条抓取手柄的尺寸
		style.WindowPadding = ImVec2(0.000000f, 0.000000f);
		style.FramePadding = ImVec2(0.000000f, 3.000000f);
		style.ItemSpacing = ImVec2(8.000000f, 4.000000f);
		style.ItemInnerSpacing = ImVec2(4.000000f, 4.000000f);
		style.IndentSpacing = 21.000000f;
		style.ScrollbarSize = 0.000000f;
		style.GrabMinSize = 5.000000f;
		style.WindowBorderSize = 5.000000f;
		style.ChildBorderSize = 5.000000f;
		style.PopupBorderSize = 5.000000f;
		style.FrameBorderSize = 5.000000f;
		style.WindowRounding = 11.000000f;
		style.ChildRounding = 11.000000f;
		style.FrameRounding = 11.000000f;
		style.PopupRounding = 0.000000f;
		style.ScrollbarRounding = 0.000000f;
		style.WindowTitleAlign = ImVec2(0.000000f, 0.500000f);
		style.ButtonTextAlign = ImVec2(0.500000f, 0.500000f);
		style.SelectableTextAlign = ImVec2(0.500000f, 0.500000f);

		style.Alpha = Alpha;
		style.DisabledAlpha = DisabledAlpha;
		style.WindowMinSize = WindowMinSize;
		style.WindowTitleAlign = WindowTitleAlign;
		style.WindowPadding = WindowPadding;
		style.FramePadding = FramePadding;
		style.CellPadding = CellPadding;
		style.ItemSpacing = ItemSpacing;
		style.ItemInnerSpacing = ItemInnerSpacing;
		style.TouchExtraPadding = TouchExtraPadding;
		style.IndentSpacing = IndentSpacing;
		style.ScrollbarSize = ScrollbarSize;
		style.GrabMinSize = GrabMinSize;
		style.WindowBorderSize = WindowBorderSize;
		style.ChildBorderSize = ChildBorderSize;
		style.PopupBorderSize = PopupBorderSize;
		style.FrameBorderSize = FrameBorderSize;
		style.TabBorderSize = TabBorderSize;
		style.WindowRounding = WindowRounding;
		style.ChildRounding = ChildRounding;
		style.FrameRounding = FrameRounding;
		style.PopupRounding = PopupRounding;
		style.ScrollbarRounding = ScrollbarRounding;
		style.GrabRounding = GrabRounding;
		style.LogSliderDeadzone = LogSliderDeadzone;
		style.TabRounding = TabRounding;
		style.TabMinWidthForCloseButton = TabMinWidthForCloseButton;
		style.ButtonTextAlign = ButtonTextAlign;
		// style.AntiAliasedLines = false;

		style.Colors[ImGuiCol_Text] = Text;
		style.Colors[ImGuiCol_TextDisabled] = TextDisabled;
		style.Colors[ImGuiCol_WindowBg] = WindowBg;
		style.Colors[ImGuiCol_ChildBg] = ChildBg;
		style.Colors[ImGuiCol_PopupBg] = PopupBg;
		style.Colors[ImGuiCol_Border] = Border;
		style.Colors[ImGuiCol_BorderShadow] = BorderShadow;
		style.Colors[ImGuiCol_FrameBg] = FrameBg;
		style.Colors[ImGuiCol_FrameBgHovered] = FrameBgHovered;
		style.Colors[ImGuiCol_FrameBgActive] = FrameBgActive;
		style.Colors[ImGuiCol_TitleBg] = TitleBg;
		style.Colors[ImGuiCol_TitleBgActive] = TitleBgActive;
		style.Colors[ImGuiCol_TitleBgCollapsed] = TitleBgCollapsed;
		style.Colors[ImGuiCol_MenuBarBg] = MenuBarBg;
		style.Colors[ImGuiCol_ScrollbarBg] = ScrollbarBg;
		style.Colors[ImGuiCol_ScrollbarGrab] = ScrollbarGrab;
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ScrollbarGrabHovered;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ScrollbarGrabActive;
		style.Colors[ImGuiCol_CheckMark] = CheckMark;
		style.Colors[ImGuiCol_SliderGrab] = SliderGrab;
		style.Colors[ImGuiCol_SliderGrabActive] = SliderGrabActive;
		style.Colors[ImGuiCol_Button] = Button;
		style.Colors[ImGuiCol_ButtonHovered] = ButtonHovered;
		style.Colors[ImGuiCol_ButtonActive] = ButtonActive;
		style.Colors[ImGuiCol_Header] = Header;
		style.Colors[ImGuiCol_HeaderHovered] = HeaderHovered;
		style.Colors[ImGuiCol_HeaderActive] = HeaderActive;
		style.Colors[ImGuiCol_Separator] = Separator;
		style.Colors[ImGuiCol_SeparatorHovered] = SeparatorHovered;
		style.Colors[ImGuiCol_SeparatorActive] = SeparatorActive;
		style.Colors[ImGuiCol_ResizeGrip] = ResizeGrip;
		style.Colors[ImGuiCol_ResizeGripHovered] = ResizeGripHovered;
		style.Colors[ImGuiCol_ResizeGripActive] = ResizeGripActive;
		style.Colors[ImGuiCol_Tab] = Tab;
		style.Colors[ImGuiCol_TabHovered] = TabHovered;
		style.Colors[ImGuiCol_TabActive] = TabActive;
		style.Colors[ImGuiCol_TabUnfocused] = TabUnfocused;
		style.Colors[ImGuiCol_TabUnfocusedActive] = TabUnfocusedActive;
		style.Colors[ImGuiCol_PlotLines] = PlotLines;
		style.Colors[ImGuiCol_PlotLinesHovered] = PlotLinesHovered;
		style.Colors[ImGuiCol_PlotHistogram] = PlotHistogram;
		style.Colors[ImGuiCol_PlotHistogramHovered] = PlotHistogramHovered;
		style.Colors[ImGuiCol_TableHeaderBg] = TableHeaderBg;
		style.Colors[ImGuiCol_TableBorderStrong] = TableBorderStrong;
		style.Colors[ImGuiCol_TableBorderLight] = TableBorderLight;
		style.Colors[ImGuiCol_TableRowBg] = TableRowBg;
		style.Colors[ImGuiCol_TableRowBgAlt] = TableRowBgAlt;
		style.Colors[ImGuiCol_TextSelectedBg] = TextSelectedBg;
		style.Colors[ImGuiCol_DragDropTarget] = DragDropTarget;
		style.Colors[ImGuiCol_NavHighlight] = NavHighlight;
		style.Colors[ImGuiCol_NavWindowingHighlight] = NavWindowingHighlight;
		style.Colors[ImGuiCol_NavWindowingDimBg] = NavWindowingDimBg;
		style.Colors[ImGuiCol_ModalWindowDimBg] = ModalWindowDimBg;
	}
};
