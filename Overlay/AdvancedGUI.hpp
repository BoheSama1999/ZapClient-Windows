// Externals
#pragma once
#include <chrono>
#include <string>
#include <thread>
#include <glfw3.h>
#include <GL/gl.h>
#include "../imgui/imgui.h"
#include "../imgui/imconfig.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

// Internals
#include "Font.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Weapons.hpp"
#include "GUI.hpp"

// Name changed :(
#define ComboBox Combo
#define MainSliderFloat SliderFloat

struct AdvancedGUI
{
	bool ShowMenu = true;
	ImVec4 DetailColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	ImVec4 ButtonColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	ImVec4 TextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;
	ImGuiColorEditFlags ColorEditFlags = ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel;

	int WindowWidth = 1000; // 1000 // 950 // 1000
	int WindowHeight = 495; // 600 // 450 // 1000 (?)

	int ColumnOffsetTest = 250;

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

	// Render Tabs

	// Advanced Aimbot
	void AdvancedAimbotTab(int WeaponID) {
		if (Features::Aimbot::AimbotEnabled) {
			ImGui::BeginChildFrame(8, ImVec2(WindowWidth - 220, 150), true);
			{
				ImGui::Spacing();
				ImGui::Text("Advanced Aimbot");
				ImGui::Checkbox("Enabled", &Features::Aimbot::AdvancedAim);
				if (Features::Aimbot::AdvancedAim) {
					const char* AimbotModeIndex[] = { "Cubic Bezier [xap-client]", "Grinder", "[New] Cubic Bezier [Testing]" };
					ImGui::ComboBox("Aimbot Method", &Features::Aimbot::AimbotMode, AimbotModeIndex, IM_ARRAYSIZE(AimbotModeIndex));
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						ImGui::SetTooltip("What Aimbot Method You Would Like.\nYou may find Grinder To Be More Legit/Smooth.");
					if (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 1) {
						const char* InputMethodIndex[] = { "Mouse", "Controller" };
						ImGui::ComboBox("Input Method", &Features::Aimbot::InputMethod, InputMethodIndex, IM_ARRAYSIZE(InputMethodIndex));
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("What Input Method The Aimbot Will Use.\nYou Can Use Controller Method With KBM, But I Recommend Mouse.");

						const char* BindMethodIndex[] = { "Memory", "Keybinds" };
						ImGui::ComboBox("Aim Bind Method", &Features::Aimbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
						ImGui::Text("Aim Conditions");
						ImGui::Checkbox("Team Check##Aimbot", &Features::Aimbot::TeamCheck);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
						if (Features::Aimbot::AimbotMode == 0) { // xap-client
							ImGui::SameLine();
							ImGui::Checkbox("Visibility Check", &Features::Aimbot::VisCheck);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Aims At Only Visible Enemies.");

							ImGui::Text("Prediction");
							ImGui::Checkbox("Predict Movement", &Features::Aimbot::PredictMovement);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Predict target's movement");
							ImGui::SameLine();
							ImGui::Checkbox("Predict Bullet Drop", &Features::Aimbot::PredictBulletDrop);
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Predict weapon's bullet drop");

							ImGui::Text("Targeting Options");
							ImGui::Checkbox("Allow Target Switching", &Features::Aimbot::TargetSwitching);
							const char* PriorityIndex[] = { "Closest To Crosshair", "Closest To LocalPlayer", "Both" };
							ImGui::ComboBox("Target Priority", &Features::Aimbot::Priority, PriorityIndex, IM_ARRAYSIZE(PriorityIndex));
							ImGui::Spacing();
						}
					}
					if (Features::Aimbot::AimbotMode == 2) {
						ImGui::Text("Selected Aimbot Mode Is Not Avaliable For Advanced Aim Currently (Not Setup Yet). Please Switch Aimbot Mode!");
					}
				}
				ImGui::EndChildFrame();
			}
		} else if (!Features::Aimbot::AimbotEnabled) {
			ImGui::Text("Aimbot Is Disabled!");
		}

		if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AdvancedAim && (Features::Aimbot::AimbotMode == 0 or Features::Aimbot::AimbotMode == 1)) {

			// Actual Advanced Aimbot Stuff
			ImGui::Spacing();

			const char* WeaponsComboBox[] = { "-------- Light --------", "P2020", "RE-45", "Alternator", "R-99", "R-301", "Spitfire", "G7 Scout", "-------- Heavy --------", "Flatline", "Hemlock", "Prowler", "30-30 Repeater", "Rampage", "C.A.R SMG", "-------- Energy --------", "Havoc", "Devotion", "L-STAR", "Triple-Take", "Volt", "Nemesis", "-------- Shotguns --------", "Mozambique", "Peacekeeper", "Mastiff", "-------- Snipers --------", "Longbow", "Charge Rifle", "Sentinel", "-------- Legendary --------", "Wingman", "EVA-8 Auto", "Bocek", "Kraber", "Throwing Knife" };
			static int WeaponsComboBoxCurrent = 5;

			ImGui::BeginChildFrame(25, ImVec2(WindowWidth - 220, WindowHeight - 268), true);
			{
				ImGui::Spacing();
				ImGui::ComboBox("Selected Weapon", &WeaponsComboBoxCurrent, WeaponsComboBox, IM_ARRAYSIZE(WeaponsComboBox));

				if (WeaponsComboBoxCurrent == 1) // P2020
				{
					if (Features::Aimbot::P2020) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##P2020Aimbot", &Features::Aimbot::P2020Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##P2020Aimbot", &Features::Aimbot::P2020ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int P2020AimBind = static_cast<int>(Features::AimbotBinds::P2020AimBind);
							ImGui::ComboBox("Aim Bind##P2020Aimbot", &P2020AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::P2020AimBind = static_cast<InputKeyType>(P2020AimBind);
							int P2020ExtraBind = static_cast<int>(Features::AimbotBinds::P2020ExtraBind);
							ImGui::ComboBox("Extra Bind##P2020Aimbot", &P2020ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::P2020ExtraBind = static_cast<InputKeyType>(P2020ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##P2020AdvancedHitbox", &Features::Aimbot::P2020ClosestHitbox);
							if (!Features::Aimbot::P2020ClosestHitbox) {
								const char* P2020HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int P2020HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::P2020Hitbox);
								ImGui::ComboBox("Hitbox Type##P2020AdvancedHitbox", &P2020HitboxTypeIndex, P2020HitboxTypes, IM_ARRAYSIZE(P2020HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::P2020Hitbox = static_cast<HitboxType>(P2020HitboxTypeIndex);
							}
						}

						const char* P2020SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::P2020SmoothingMethod, P2020SmoothingMethodIndex, IM_ARRAYSIZE(P2020SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedP2020", &Features::Aimbot::P2020Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The P2020\nHigher = Faster");
							}

							if (Features::Aimbot::P2020SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedP2020", &Features::Aimbot::P2020HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedP2020", &Features::Aimbot::P2020ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::P2020SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedP2020", &Features::Aimbot::P2020MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedP2020", &Features::Aimbot::P2020MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedP2020", &Features::Aimbot::P2020MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedP2020", &Features::Aimbot::P2020MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##P2020", &Features::Aimbot::P2020FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##P2020", &Features::Aimbot::P2020ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::P2020SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedP2020", &Features::Aimbot::P2020HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedP2020", &Features::Aimbot::P2020ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::P2020SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedP2020", &Features::Aimbot::P2020MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedP2020", &Features::Aimbot::P2020MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The P2020 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedP2020", &Features::Aimbot::P2020MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedP2020", &Features::Aimbot::P2020MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The P2020 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedP2020", &Features::Aimbot::P2020ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedP2020", &Features::Aimbot::P2020Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::P2020FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::P2020MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::P2020MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 2) // RE45
				{
					if (Features::Aimbot::RE45) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##RE45Aimbot", &Features::Aimbot::RE45Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##RE45Aimbot", &Features::Aimbot::RE45ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int RE45AimBind = static_cast<int>(Features::AimbotBinds::RE45AimBind);
							ImGui::ComboBox("Aim Bind##RE45Aimbot", &RE45AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RE45AimBind = static_cast<InputKeyType>(RE45AimBind);
							int RE45ExtraBind = static_cast<int>(Features::AimbotBinds::RE45ExtraBind);
							ImGui::ComboBox("Extra Bind##RE45Aimbot", &RE45ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RE45ExtraBind = static_cast<InputKeyType>(RE45ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##RE45AdvancedHitbox", &Features::Aimbot::RE45ClosestHitbox);
							if (!Features::Aimbot::RE45ClosestHitbox) {
								const char* RE45HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int RE45HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::RE45Hitbox);
								ImGui::ComboBox("Hitbox Type##RE45AdvancedHitbox", &RE45HitboxTypeIndex, RE45HitboxTypes, IM_ARRAYSIZE(RE45HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::RE45Hitbox = static_cast<HitboxType>(RE45HitboxTypeIndex);
							}
						}

						const char* RE45SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::RE45SmoothingMethod, RE45SmoothingMethodIndex, IM_ARRAYSIZE(RE45SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedRE45", &Features::Aimbot::RE45Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The RE45\nHigher = Faster");
							}

							if (Features::Aimbot::RE45SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedRE45", &Features::Aimbot::RE45HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedRE45", &Features::Aimbot::RE45ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RE45SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedRE45", &Features::Aimbot::RE45MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedRE45", &Features::Aimbot::RE45MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedRE45", &Features::Aimbot::RE45MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedRE45", &Features::Aimbot::RE45MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##RE45", &Features::Aimbot::RE45FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##RE45", &Features::Aimbot::RE45ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::RE45SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedRE45", &Features::Aimbot::RE45HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedRE45", &Features::Aimbot::RE45ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RE45SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedRE45", &Features::Aimbot::RE45MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedRE45", &Features::Aimbot::RE45MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The RE45 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedRE45", &Features::Aimbot::RE45MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedRE45", &Features::Aimbot::RE45MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The RE45 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedRE45", &Features::Aimbot::RE45ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedRE45", &Features::Aimbot::RE45Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::RE45FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::RE45MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::RE45MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 3) // Alternator
				{
					if (Features::Aimbot::Alternator) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##AlternatorAimbot", &Features::Aimbot::AlternatorFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##AlternatorAimbot", &Features::Aimbot::AlternatorADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int AlternatorAimBind = static_cast<int>(Features::AimbotBinds::AlternatorAimBind);
							ImGui::ComboBox("Aim Bind##AlternatorAimbot", &AlternatorAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::AlternatorAimBind = static_cast<InputKeyType>(AlternatorAimBind);
							int AlternatorExtraBind = static_cast<int>(Features::AimbotBinds::AlternatorExtraBind);
							ImGui::ComboBox("Extra Bind##AlternatorAimbot", &AlternatorExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::AlternatorExtraBind = static_cast<InputKeyType>(AlternatorExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##AlternatorAdvancedHitbox", &Features::Aimbot::AlternatorClosestHitbox);
							if (!Features::Aimbot::AlternatorClosestHitbox) {
								const char* AlternatorHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int AlternatorHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::AlternatorHitbox);
								ImGui::ComboBox("Hitbox Type##AlternatorAdvancedHitbox", &AlternatorHitboxTypeIndex, AlternatorHitboxTypes, IM_ARRAYSIZE(AlternatorHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::AlternatorHitbox = static_cast<HitboxType>(AlternatorHitboxTypeIndex);
							}
						}

						const char* AlternatorSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::AlternatorSmoothingMethod, AlternatorSmoothingMethodIndex, IM_ARRAYSIZE(AlternatorSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedAlternator", &Features::Aimbot::AlternatorSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Alternator\nHigher = Faster");
							}

							if (Features::Aimbot::AlternatorSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::AlternatorSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedAlternator", &Features::Aimbot::AlternatorMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Alternator", &Features::Aimbot::AlternatorFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Alternator", &Features::Aimbot::AlternatorZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::AlternatorSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::AlternatorSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Alternator Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Alternator Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedAlternator", &Features::Aimbot::AlternatorExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedAlternator", &Features::Aimbot::AlternatorDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::AlternatorFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::AlternatorMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::AlternatorMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 4) // R99
				{
					if (Features::Aimbot::R99) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##R99Aimbot", &Features::Aimbot::R99Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##R99Aimbot", &Features::Aimbot::R99ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int R99AimBind = static_cast<int>(Features::AimbotBinds::R99AimBind);
							ImGui::ComboBox("Aim Bind##R99Aimbot", &R99AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::R99AimBind = static_cast<InputKeyType>(R99AimBind);
							int R99ExtraBind = static_cast<int>(Features::AimbotBinds::R99ExtraBind);
							ImGui::ComboBox("Extra Bind##R99Aimbot", &R99ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::R99ExtraBind = static_cast<InputKeyType>(R99ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##R99AdvancedHitbox", &Features::Aimbot::R99ClosestHitbox);
							if (!Features::Aimbot::R99ClosestHitbox) {
								const char* R99HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int R99HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::R99Hitbox);
								ImGui::ComboBox("Hitbox Type##R99AdvancedHitbox", &R99HitboxTypeIndex, R99HitboxTypes, IM_ARRAYSIZE(R99HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::R99Hitbox = static_cast<HitboxType>(R99HitboxTypeIndex);
							}
						}

						const char* R99SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::R99SmoothingMethod, R99SmoothingMethodIndex, IM_ARRAYSIZE(R99SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedR99", &Features::Aimbot::R99Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The R99\nHigher = Faster");
							}

							if (Features::Aimbot::R99SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedR99", &Features::Aimbot::R99HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedR99", &Features::Aimbot::R99ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::R99SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedR99", &Features::Aimbot::R99MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedR99", &Features::Aimbot::R99MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedR99", &Features::Aimbot::R99MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedR99", &Features::Aimbot::R99MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##R99", &Features::Aimbot::R99FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##R99", &Features::Aimbot::R99ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::R99SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedR99", &Features::Aimbot::R99HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedR99", &Features::Aimbot::R99ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::R99SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedR99", &Features::Aimbot::R99MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedR99", &Features::Aimbot::R99MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R99 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedR99", &Features::Aimbot::R99MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedR99", &Features::Aimbot::R99MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R99 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedR99", &Features::Aimbot::R99ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedR99", &Features::Aimbot::R99Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::R99FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::R99MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::R99MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 5) // R301
				{
					if (Features::Aimbot::R301) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##R301Aimbot", &Features::Aimbot::R301Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##R301Aimbot", &Features::Aimbot::R301ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int R301AimBind = static_cast<int>(Features::AimbotBinds::R301AimBind);
							ImGui::ComboBox("Aim Bind##R301Aimbot", &R301AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::R301AimBind = static_cast<InputKeyType>(R301AimBind);
							int R301ExtraBind = static_cast<int>(Features::AimbotBinds::R301ExtraBind);
							ImGui::ComboBox("Extra Bind##R301Aimbot", &R301ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::R301ExtraBind = static_cast<InputKeyType>(R301ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##R301AdvancedHitbox", &Features::Aimbot::R301ClosestHitbox);
							if (!Features::Aimbot::R301ClosestHitbox) {
								const char* R301HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int R301HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::R301Hitbox);
								ImGui::ComboBox("Hitbox Type##R301AdvancedHitbox", &R301HitboxTypeIndex, R301HitboxTypes, IM_ARRAYSIZE(R301HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::R301Hitbox = static_cast<HitboxType>(R301HitboxTypeIndex);
							}
						}

						const char* R301SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::R301SmoothingMethod, R301SmoothingMethodIndex, IM_ARRAYSIZE(R301SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedR301", &Features::Aimbot::R301Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The R301\nHigher = Faster");
							}

							if (Features::Aimbot::R301SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedR301", &Features::Aimbot::R301HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedR301", &Features::Aimbot::R301ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::R301SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedR301", &Features::Aimbot::R301MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedR301", &Features::Aimbot::R301MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedR301", &Features::Aimbot::R301MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedR301", &Features::Aimbot::R301MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##R301", &Features::Aimbot::R301FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##R301", &Features::Aimbot::R301ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::R301SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedR301", &Features::Aimbot::R301HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedR301", &Features::Aimbot::R301ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::R301SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedR301", &Features::Aimbot::R301MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedR301", &Features::Aimbot::R301MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R301 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedR301", &Features::Aimbot::R301MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedR301", &Features::Aimbot::R301MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The R301 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedR301", &Features::Aimbot::R301ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedR301", &Features::Aimbot::R301Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::R301FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::R301MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::R301MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 6) // Spitfire
				{
					if (Features::Aimbot::Spitfire) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##SpitfireAimbot", &Features::Aimbot::SpitfireFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##SpitfireAimbot", &Features::Aimbot::SpitfireADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int SpitfireAimBind = static_cast<int>(Features::AimbotBinds::SpitfireAimBind);
							ImGui::ComboBox("Aim Bind##SpitfireAimbot", &SpitfireAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::SpitfireAimBind = static_cast<InputKeyType>(SpitfireAimBind);
							int SpitfireExtraBind = static_cast<int>(Features::AimbotBinds::SpitfireExtraBind);
							ImGui::ComboBox("Extra Bind##SpitfireAimbot", &SpitfireExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::SpitfireExtraBind = static_cast<InputKeyType>(SpitfireExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##SpitfireAdvancedHitbox", &Features::Aimbot::SpitfireClosestHitbox);
							if (!Features::Aimbot::SpitfireClosestHitbox) {
								const char* SpitfireHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int SpitfireHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::SpitfireHitbox);
								ImGui::ComboBox("Hitbox Type##SpitfireAdvancedHitbox", &SpitfireHitboxTypeIndex, SpitfireHitboxTypes, IM_ARRAYSIZE(SpitfireHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::SpitfireHitbox = static_cast<HitboxType>(SpitfireHitboxTypeIndex);
							}
						}

						const char* SpitfireSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SpitfireSmoothingMethod, SpitfireSmoothingMethodIndex, IM_ARRAYSIZE(SpitfireSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedSpitfire", &Features::Aimbot::SpitfireSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Spitfire\nHigher = Faster");
							}

							if (Features::Aimbot::SpitfireSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::SpitfireSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedSpitfire", &Features::Aimbot::SpitfireMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Spitfire", &Features::Aimbot::SpitfireFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Spitfire", &Features::Aimbot::SpitfireZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::SpitfireSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::SpitfireSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Spitfire Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Spitfire Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedSpitfire", &Features::Aimbot::SpitfireExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedSpitfire", &Features::Aimbot::SpitfireDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::SpitfireFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::SpitfireMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::SpitfireMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 7) // G7
				{
					if (Features::Aimbot::G7) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##G7Aimbot", &Features::Aimbot::G7Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##G7Aimbot", &Features::Aimbot::G7ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int G7AimBind = static_cast<int>(Features::AimbotBinds::G7AimBind);
							ImGui::ComboBox("Aim Bind##G7Aimbot", &G7AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::G7AimBind = static_cast<InputKeyType>(G7AimBind);
							int G7ExtraBind = static_cast<int>(Features::AimbotBinds::G7ExtraBind);
							ImGui::ComboBox("Extra Bind##G7Aimbot", &G7ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::G7ExtraBind = static_cast<InputKeyType>(G7ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##G7AdvancedHitbox", &Features::Aimbot::G7ClosestHitbox);
							if (!Features::Aimbot::G7ClosestHitbox) {
								const char* G7HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int G7HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::G7Hitbox);
								ImGui::ComboBox("Hitbox Type##G7AdvancedHitbox", &G7HitboxTypeIndex, G7HitboxTypes, IM_ARRAYSIZE(G7HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::G7Hitbox = static_cast<HitboxType>(G7HitboxTypeIndex);
							}
						}

						const char* G7SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::G7SmoothingMethod, G7SmoothingMethodIndex, IM_ARRAYSIZE(G7SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedG7", &Features::Aimbot::G7Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The G7\nHigher = Faster");
							}

							if (Features::Aimbot::G7SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedG7", &Features::Aimbot::G7HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedG7", &Features::Aimbot::G7ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::G7SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedG7", &Features::Aimbot::G7MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedG7", &Features::Aimbot::G7MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedG7", &Features::Aimbot::G7MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedG7", &Features::Aimbot::G7MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##G7", &Features::Aimbot::G7FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##G7", &Features::Aimbot::G7ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::G7SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedG7", &Features::Aimbot::G7HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedG7", &Features::Aimbot::G7ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::G7SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedG7", &Features::Aimbot::G7MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedG7", &Features::Aimbot::G7MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The G7 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedG7", &Features::Aimbot::G7MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedG7", &Features::Aimbot::G7MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The G7 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedG7", &Features::Aimbot::G7ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedG7", &Features::Aimbot::G7Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::G7FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::G7MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::G7MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 9) // Flatline
				{
					if (Features::Aimbot::Flatline) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##FlatlineAimbot", &Features::Aimbot::FlatlineFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##FlatlineAimbot", &Features::Aimbot::FlatlineADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int FlatlineAimBind = static_cast<int>(Features::AimbotBinds::FlatlineAimBind);
							ImGui::ComboBox("Aim Bind##FlatlineAimbot", &FlatlineAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::FlatlineAimBind = static_cast<InputKeyType>(FlatlineAimBind);
							int FlatlineExtraBind = static_cast<int>(Features::AimbotBinds::FlatlineExtraBind);
							ImGui::ComboBox("Extra Bind##FlatlineAimbot", &FlatlineExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::FlatlineExtraBind = static_cast<InputKeyType>(FlatlineExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##FlatlineAdvancedHitbox", &Features::Aimbot::FlatlineClosestHitbox);
							if (!Features::Aimbot::FlatlineClosestHitbox) {
								const char* FlatlineHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int FlatlineHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::FlatlineHitbox);
								ImGui::ComboBox("Hitbox Type##FlatlineAdvancedHitbox", &FlatlineHitboxTypeIndex, FlatlineHitboxTypes, IM_ARRAYSIZE(FlatlineHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::FlatlineHitbox = static_cast<HitboxType>(FlatlineHitboxTypeIndex);
							}
						}

						const char* FlatlineSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::FlatlineSmoothingMethod, FlatlineSmoothingMethodIndex, IM_ARRAYSIZE(FlatlineSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedFlatline", &Features::Aimbot::FlatlineSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Flatline\nHigher = Faster");
							}

							if (Features::Aimbot::FlatlineSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::FlatlineSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedFlatline", &Features::Aimbot::FlatlineMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Flatline", &Features::Aimbot::FlatlineFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Flatline", &Features::Aimbot::FlatlineZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::FlatlineSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::FlatlineSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Flatline Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Flatline Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedFlatline", &Features::Aimbot::FlatlineExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedFlatline", &Features::Aimbot::FlatlineDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::FlatlineFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::FlatlineMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::FlatlineMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 10) // Hemlock
				{
					if (Features::Aimbot::Hemlock) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##HemlockAimbot", &Features::Aimbot::HemlockFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##HemlockAimbot", &Features::Aimbot::HemlockADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int HemlockAimBind = static_cast<int>(Features::AimbotBinds::HemlockAimBind);
							ImGui::ComboBox("Aim Bind##HemlockAimbot", &HemlockAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::HemlockAimBind = static_cast<InputKeyType>(HemlockAimBind);
							int HemlockExtraBind = static_cast<int>(Features::AimbotBinds::HemlockExtraBind);
							ImGui::ComboBox("Extra Bind##HemlockAimbot", &HemlockExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::HemlockExtraBind = static_cast<InputKeyType>(HemlockExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##HemlockAdvancedHitbox", &Features::Aimbot::HemlockClosestHitbox);
							if (!Features::Aimbot::HemlockClosestHitbox) {
								const char* HemlockHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int HemlockHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::HemlockHitbox);
								ImGui::ComboBox("Hitbox Type##HemlockAdvancedHitbox", &HemlockHitboxTypeIndex, HemlockHitboxTypes, IM_ARRAYSIZE(HemlockHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::HemlockHitbox = static_cast<HitboxType>(HemlockHitboxTypeIndex);
							}
						}

						const char* HemlockSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::HemlockSmoothingMethod, HemlockSmoothingMethodIndex, IM_ARRAYSIZE(HemlockSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedHemlock", &Features::Aimbot::HemlockSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Hemlock\nHigher = Faster");
							}

							if (Features::Aimbot::HemlockSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::HemlockSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedHemlock", &Features::Aimbot::HemlockMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Hemlock", &Features::Aimbot::HemlockFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Hemlock", &Features::Aimbot::HemlockZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::HemlockSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::HemlockSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Hemlock Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Hemlock Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedHemlock", &Features::Aimbot::HemlockExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedHemlock", &Features::Aimbot::HemlockDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::HemlockFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::HemlockMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::HemlockMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 11) // Prowler
				{
					if (Features::Aimbot::Prowler) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##ProwlerAimbot", &Features::Aimbot::ProwlerFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##ProwlerAimbot", &Features::Aimbot::ProwlerADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int ProwlerAimBind = static_cast<int>(Features::AimbotBinds::ProwlerAimBind);
							ImGui::ComboBox("Aim Bind##ProwlerAimbot", &ProwlerAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ProwlerAimBind = static_cast<InputKeyType>(ProwlerAimBind);
							int ProwlerExtraBind = static_cast<int>(Features::AimbotBinds::ProwlerExtraBind);
							ImGui::ComboBox("Extra Bind##ProwlerAimbot", &ProwlerExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ProwlerExtraBind = static_cast<InputKeyType>(ProwlerExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##ProwlerAdvancedHitbox", &Features::Aimbot::ProwlerClosestHitbox);
							if (!Features::Aimbot::ProwlerClosestHitbox) {
								const char* ProwlerHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int ProwlerHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::ProwlerHitbox);
								ImGui::ComboBox("Hitbox Type##ProwlerAdvancedHitbox", &ProwlerHitboxTypeIndex, ProwlerHitboxTypes, IM_ARRAYSIZE(ProwlerHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::ProwlerHitbox = static_cast<HitboxType>(ProwlerHitboxTypeIndex);
							}
						}

						const char* ProwlerSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::ProwlerSmoothingMethod, ProwlerSmoothingMethodIndex, IM_ARRAYSIZE(ProwlerSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedProwler", &Features::Aimbot::ProwlerSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Prowler\nHigher = Faster");
							}

							if (Features::Aimbot::ProwlerSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ProwlerSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedProwler", &Features::Aimbot::ProwlerMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Prowler", &Features::Aimbot::ProwlerFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Prowler", &Features::Aimbot::ProwlerZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::ProwlerSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ProwlerSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Prowler Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Prowler Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedProwler", &Features::Aimbot::ProwlerExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedProwler", &Features::Aimbot::ProwlerDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::ProwlerFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::ProwlerMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::ProwlerMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 12) // Repeater
				{
					if (Features::Aimbot::Repeater) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##RepeaterAimbot", &Features::Aimbot::RepeaterFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##RepeaterAimbot", &Features::Aimbot::RepeaterADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int RepeaterAimBind = static_cast<int>(Features::AimbotBinds::RepeaterAimBind);
							ImGui::ComboBox("Aim Bind##RepeaterAimbot", &RepeaterAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RepeaterAimBind = static_cast<InputKeyType>(RepeaterAimBind);
							int RepeaterExtraBind = static_cast<int>(Features::AimbotBinds::RepeaterExtraBind);
							ImGui::ComboBox("Extra Bind##RepeaterAimbot", &RepeaterExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RepeaterExtraBind = static_cast<InputKeyType>(RepeaterExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##RepeaterAdvancedHitbox", &Features::Aimbot::RepeaterClosestHitbox);
							if (!Features::Aimbot::RepeaterClosestHitbox) {
								const char* RepeaterHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int RepeaterHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::RepeaterHitbox);
								ImGui::ComboBox("Hitbox Type##RepeaterAdvancedHitbox", &RepeaterHitboxTypeIndex, RepeaterHitboxTypes, IM_ARRAYSIZE(RepeaterHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::RepeaterHitbox = static_cast<HitboxType>(RepeaterHitboxTypeIndex);
							}
						}

						const char* RepeaterSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::RepeaterSmoothingMethod, RepeaterSmoothingMethodIndex, IM_ARRAYSIZE(RepeaterSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedRepeater", &Features::Aimbot::RepeaterSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Repeater\nHigher = Faster");
							}

							if (Features::Aimbot::RepeaterSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RepeaterSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedRepeater", &Features::Aimbot::RepeaterMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Repeater", &Features::Aimbot::RepeaterFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Repeater", &Features::Aimbot::RepeaterZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::RepeaterSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RepeaterSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Repeater Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Repeater Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedRepeater", &Features::Aimbot::RepeaterExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedRepeater", &Features::Aimbot::RepeaterDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::RepeaterFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::RepeaterMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::RepeaterMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 13) // Rampage
				{
					if (Features::Aimbot::Rampage) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##RampageAimbot", &Features::Aimbot::RampageFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##RampageAimbot", &Features::Aimbot::RampageADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int RampageAimBind = static_cast<int>(Features::AimbotBinds::RampageAimBind);
							ImGui::ComboBox("Aim Bind##RampageAimbot", &RampageAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RampageAimBind = static_cast<InputKeyType>(RampageAimBind);
							int RampageExtraBind = static_cast<int>(Features::AimbotBinds::RampageExtraBind);
							ImGui::ComboBox("Extra Bind##RampageAimbot", &RampageExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::RampageExtraBind = static_cast<InputKeyType>(RampageExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##RampageAdvancedHitbox", &Features::Aimbot::RampageClosestHitbox);
							if (!Features::Aimbot::RampageClosestHitbox) {
								const char* RampageHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int RampageHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::RampageHitbox);
								ImGui::ComboBox("Hitbox Type##RampageAdvancedHitbox", &RampageHitboxTypeIndex, RampageHitboxTypes, IM_ARRAYSIZE(RampageHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::RampageHitbox = static_cast<HitboxType>(RampageHitboxTypeIndex);
							}
						}

						const char* RampageSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::RampageSmoothingMethod, RampageSmoothingMethodIndex, IM_ARRAYSIZE(RampageSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedRampage", &Features::Aimbot::RampageSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Rampage\nHigher = Faster");
							}

							if (Features::Aimbot::RampageSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedRampage", &Features::Aimbot::RampageHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedRampage", &Features::Aimbot::RampageADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RampageSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedRampage", &Features::Aimbot::RampageMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedRampage", &Features::Aimbot::RampageMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedRampage", &Features::Aimbot::RampageMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedRampage", &Features::Aimbot::RampageMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Rampage", &Features::Aimbot::RampageFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Rampage", &Features::Aimbot::RampageZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::RampageSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedRampage", &Features::Aimbot::RampageHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedRampage", &Features::Aimbot::RampageADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::RampageSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedRampage", &Features::Aimbot::RampageMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedRampage", &Features::Aimbot::RampageMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Rampage Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedRampage", &Features::Aimbot::RampageMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedRampage", &Features::Aimbot::RampageMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Rampage Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedRampage", &Features::Aimbot::RampageExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedRampage", &Features::Aimbot::RampageDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::RampageFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::RampageMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::RampageMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 14) // CARSMG
				{
					if (Features::Aimbot::CARSMG) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##CARSMGAimbot", &Features::Aimbot::CARSMGFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##CARSMGAimbot", &Features::Aimbot::CARSMGADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int CARSMGAimBind = static_cast<int>(Features::AimbotBinds::CARSMGAimBind);
							ImGui::ComboBox("Aim Bind##CARSMGAimbot", &CARSMGAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::CARSMGAimBind = static_cast<InputKeyType>(CARSMGAimBind);
							int CARSMGExtraBind = static_cast<int>(Features::AimbotBinds::CARSMGExtraBind);
							ImGui::ComboBox("Extra Bind##CARSMGAimbot", &CARSMGExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::CARSMGExtraBind = static_cast<InputKeyType>(CARSMGExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##CARSMGAdvancedHitbox", &Features::Aimbot::CARSMGClosestHitbox);
							if (!Features::Aimbot::CARSMGClosestHitbox) {
								const char* CARSMGHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int CARSMGHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::CARSMGHitbox);
								ImGui::ComboBox("Hitbox Type##CARSMGAdvancedHitbox", &CARSMGHitboxTypeIndex, CARSMGHitboxTypes, IM_ARRAYSIZE(CARSMGHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::CARSMGHitbox = static_cast<HitboxType>(CARSMGHitboxTypeIndex);
							}
						}

						const char* CARSMGSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::CARSMGSmoothingMethod, CARSMGSmoothingMethodIndex, IM_ARRAYSIZE(CARSMGSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedCARSMG", &Features::Aimbot::CARSMGSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The CARSMG\nHigher = Faster");
							}

							if (Features::Aimbot::CARSMGSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::CARSMGSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedCARSMG", &Features::Aimbot::CARSMGMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##CARSMG", &Features::Aimbot::CARSMGFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##CARSMG", &Features::Aimbot::CARSMGZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::CARSMGSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::CARSMGSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The CARSMG Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The CARSMG Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedCARSMG", &Features::Aimbot::CARSMGExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedCARSMG", &Features::Aimbot::CARSMGDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::CARSMGFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::CARSMGMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::CARSMGMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 16) // Havoc
				{
					if (Features::Aimbot::Havoc) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##HavocAimbot", &Features::Aimbot::HavocFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##HavocAimbot", &Features::Aimbot::HavocADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int HavocAimBind = static_cast<int>(Features::AimbotBinds::HavocAimBind);
							ImGui::ComboBox("Aim Bind##HavocAimbot", &HavocAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::HavocAimBind = static_cast<InputKeyType>(HavocAimBind);
							int HavocExtraBind = static_cast<int>(Features::AimbotBinds::HavocExtraBind);
							ImGui::ComboBox("Extra Bind##HavocAimbot", &HavocExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::HavocExtraBind = static_cast<InputKeyType>(HavocExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##HavocAdvancedHitbox", &Features::Aimbot::HavocClosestHitbox);
							if (!Features::Aimbot::HavocClosestHitbox) {
								const char* HavocHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int HavocHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::HavocHitbox);
								ImGui::ComboBox("Hitbox Type##HavocAdvancedHitbox", &HavocHitboxTypeIndex, HavocHitboxTypes, IM_ARRAYSIZE(HavocHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::HavocHitbox = static_cast<HitboxType>(HavocHitboxTypeIndex);
							}
						}

						const char* HavocSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::HavocSmoothingMethod, HavocSmoothingMethodIndex, IM_ARRAYSIZE(HavocSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedHavoc", &Features::Aimbot::HavocSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Havoc\nHigher = Faster");
							}

							if (Features::Aimbot::HavocSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedHavoc", &Features::Aimbot::HavocHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedHavoc", &Features::Aimbot::HavocADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::HavocSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedHavoc", &Features::Aimbot::HavocMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedHavoc", &Features::Aimbot::HavocMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedHavoc", &Features::Aimbot::HavocMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedHavoc", &Features::Aimbot::HavocMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Havoc", &Features::Aimbot::HavocFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Havoc", &Features::Aimbot::HavocZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::HavocSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::HavocSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Havoc Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Havoc Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedHavoc", &Features::Aimbot::HavocExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedHavoc", &Features::Aimbot::HavocDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::HavocFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::HavocMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::HavocMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 17) // Devotion
				{
					if (Features::Aimbot::Devotion) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##DevotionAimbot", &Features::Aimbot::DevotionFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##DevotionAimbot", &Features::Aimbot::DevotionADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int DevotionAimBind = static_cast<int>(Features::AimbotBinds::DevotionAimBind);
							ImGui::ComboBox("Aim Bind##DevotionAimbot", &DevotionAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::DevotionAimBind = static_cast<InputKeyType>(DevotionAimBind);
							int DevotionExtraBind = static_cast<int>(Features::AimbotBinds::DevotionExtraBind);
							ImGui::ComboBox("Extra Bind##DevotionAimbot", &DevotionExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::DevotionExtraBind = static_cast<InputKeyType>(DevotionExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##DevotionAdvancedHitbox", &Features::Aimbot::DevotionClosestHitbox);
							if (!Features::Aimbot::DevotionClosestHitbox) {
								const char* DevotionHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int DevotionHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::DevotionHitbox);
								ImGui::ComboBox("Hitbox Type##DevotionAdvancedHitbox", &DevotionHitboxTypeIndex, DevotionHitboxTypes, IM_ARRAYSIZE(DevotionHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::DevotionHitbox = static_cast<HitboxType>(DevotionHitboxTypeIndex);
							}
						}

						const char* DevotionSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::DevotionSmoothingMethod, DevotionSmoothingMethodIndex, IM_ARRAYSIZE(DevotionSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedDevotion", &Features::Aimbot::DevotionSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Devotion\nHigher = Faster");
							}

							if (Features::Aimbot::DevotionSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::DevotionSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedDevotion", &Features::Aimbot::DevotionMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Devotion", &Features::Aimbot::DevotionFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Devotion", &Features::Aimbot::DevotionZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::DevotionSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::DevotionSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Devotion Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Devotion Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedDevotion", &Features::Aimbot::DevotionExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedDevotion", &Features::Aimbot::DevotionDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::DevotionFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::DevotionMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::DevotionMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 18) // LSTAR
				{
					if (Features::Aimbot::LSTAR) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##LSTARAimbot", &Features::Aimbot::LSTARFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##LSTARAimbot", &Features::Aimbot::LSTARADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int LSTARAimBind = static_cast<int>(Features::AimbotBinds::LSTARAimBind);
							ImGui::ComboBox("Aim Bind##LSTARAimbot", &LSTARAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::LSTARAimBind = static_cast<InputKeyType>(LSTARAimBind);
							int LSTARExtraBind = static_cast<int>(Features::AimbotBinds::LSTARExtraBind);
							ImGui::ComboBox("Extra Bind##LSTARAimbot", &LSTARExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::LSTARExtraBind = static_cast<InputKeyType>(LSTARExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##LSTARAdvancedHitbox", &Features::Aimbot::LSTARClosestHitbox);
							if (!Features::Aimbot::LSTARClosestHitbox) {
								const char* LSTARHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int LSTARHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::LSTARHitbox);
								ImGui::ComboBox("Hitbox Type##LSTARAdvancedHitbox", &LSTARHitboxTypeIndex, LSTARHitboxTypes, IM_ARRAYSIZE(LSTARHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::LSTARHitbox = static_cast<HitboxType>(LSTARHitboxTypeIndex);
							}
						}

						const char* LSTARSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::LSTARSmoothingMethod, LSTARSmoothingMethodIndex, IM_ARRAYSIZE(LSTARSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedLSTAR", &Features::Aimbot::LSTARSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The LSTAR\nHigher = Faster");
							}

							if (Features::Aimbot::LSTARSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::LSTARSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedLSTAR", &Features::Aimbot::LSTARMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##LSTAR", &Features::Aimbot::LSTARFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##LSTAR", &Features::Aimbot::LSTARZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::LSTARSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::LSTARSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The LSTAR Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The LSTAR Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedLSTAR", &Features::Aimbot::LSTARExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedLSTAR", &Features::Aimbot::LSTARDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::LSTARFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::LSTARMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::LSTARMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 19) // TripleTake
				{
					if (Features::Aimbot::TripleTake) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##TripleTakeAimbot", &Features::Aimbot::TripleTakeFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##TripleTakeAimbot", &Features::Aimbot::TripleTakeADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int TripleTakeAimBind = static_cast<int>(Features::AimbotBinds::TripleTakeAimBind);
							ImGui::ComboBox("Aim Bind##TripleTakeAimbot", &TripleTakeAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::TripleTakeAimBind = static_cast<InputKeyType>(TripleTakeAimBind);
							int TripleTakeExtraBind = static_cast<int>(Features::AimbotBinds::TripleTakeExtraBind);
							ImGui::ComboBox("Extra Bind##TripleTakeAimbot", &TripleTakeExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::TripleTakeExtraBind = static_cast<InputKeyType>(TripleTakeExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##TripleTakeAdvancedHitbox", &Features::Aimbot::TripleTakeClosestHitbox);
							if (!Features::Aimbot::TripleTakeClosestHitbox) {
								const char* TripleTakeHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int TripleTakeHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::TripleTakeHitbox);
								ImGui::ComboBox("Hitbox Type##TripleTakeAdvancedHitbox", &TripleTakeHitboxTypeIndex, TripleTakeHitboxTypes, IM_ARRAYSIZE(TripleTakeHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::TripleTakeHitbox = static_cast<HitboxType>(TripleTakeHitboxTypeIndex);
							}
						}

						const char* TripleTakeSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::TripleTakeSmoothingMethod, TripleTakeSmoothingMethodIndex, IM_ARRAYSIZE(TripleTakeSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedTripleTake", &Features::Aimbot::TripleTakeSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The TripleTake\nHigher = Faster");
							}

							if (Features::Aimbot::TripleTakeSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::TripleTakeSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedTripleTake", &Features::Aimbot::TripleTakeMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##TripleTake", &Features::Aimbot::TripleTakeFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##TripleTake", &Features::Aimbot::TripleTakeZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::TripleTakeSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::TripleTakeSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The TripleTake Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The TripleTake Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedTripleTake", &Features::Aimbot::TripleTakeExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedTripleTake", &Features::Aimbot::TripleTakeDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::TripleTakeFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::TripleTakeMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::TripleTakeMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 20) // Volt
				{
					if (Features::Aimbot::Volt) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##VoltAimbot", &Features::Aimbot::VoltFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##VoltAimbot", &Features::Aimbot::VoltADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int VoltAimBind = static_cast<int>(Features::AimbotBinds::VoltAimBind);
							ImGui::ComboBox("Aim Bind##VoltAimbot", &VoltAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::VoltAimBind = static_cast<InputKeyType>(VoltAimBind);
							int VoltExtraBind = static_cast<int>(Features::AimbotBinds::VoltExtraBind);
							ImGui::ComboBox("Extra Bind##VoltAimbot", &VoltExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::VoltExtraBind = static_cast<InputKeyType>(VoltExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##VoltAdvancedHitbox", &Features::Aimbot::VoltClosestHitbox);
							if (!Features::Aimbot::VoltClosestHitbox) {
								const char* VoltHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int VoltHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::VoltHitbox);
								ImGui::ComboBox("Hitbox Type##VoltAdvancedHitbox", &VoltHitboxTypeIndex, VoltHitboxTypes, IM_ARRAYSIZE(VoltHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::VoltHitbox = static_cast<HitboxType>(VoltHitboxTypeIndex);
							}
						}

						const char* VoltSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::VoltSmoothingMethod, VoltSmoothingMethodIndex, IM_ARRAYSIZE(VoltSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedVolt", &Features::Aimbot::VoltSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Volt\nHigher = Faster");
							}

							if (Features::Aimbot::VoltSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedVolt", &Features::Aimbot::VoltHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedVolt", &Features::Aimbot::VoltADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::VoltSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedVolt", &Features::Aimbot::VoltMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedVolt", &Features::Aimbot::VoltMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedVolt", &Features::Aimbot::VoltMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedVolt", &Features::Aimbot::VoltMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Volt", &Features::Aimbot::VoltFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Volt", &Features::Aimbot::VoltZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::VoltSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedVolt", &Features::Aimbot::VoltHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedVolt", &Features::Aimbot::VoltADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::VoltSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedVolt", &Features::Aimbot::VoltMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedVolt", &Features::Aimbot::VoltMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Volt Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedVolt", &Features::Aimbot::VoltMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedVolt", &Features::Aimbot::VoltMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Volt Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedVolt", &Features::Aimbot::VoltExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedVolt", &Features::Aimbot::VoltDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::VoltFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::VoltMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::VoltMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 21) // Nemesis
				{
					if (Features::Aimbot::Nemesis) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##NemesisAimbot", &Features::Aimbot::NemesisFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##NemesisAimbot", &Features::Aimbot::NemesisADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int NemesisAimBind = static_cast<int>(Features::AimbotBinds::NemesisAimBind);
							ImGui::ComboBox("Aim Bind##NemesisAimbot", &NemesisAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::NemesisAimBind = static_cast<InputKeyType>(NemesisAimBind);
							int NemesisExtraBind = static_cast<int>(Features::AimbotBinds::NemesisExtraBind);
							ImGui::ComboBox("Extra Bind##NemesisAimbot", &NemesisExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::NemesisExtraBind = static_cast<InputKeyType>(NemesisExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##NemesisAdvancedHitbox", &Features::Aimbot::NemesisClosestHitbox);
							if (!Features::Aimbot::NemesisClosestHitbox) {
								const char* NemesisHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int NemesisHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::NemesisHitbox);
								ImGui::ComboBox("Hitbox Type##NemesisAdvancedHitbox", &NemesisHitboxTypeIndex, NemesisHitboxTypes, IM_ARRAYSIZE(NemesisHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::NemesisHitbox = static_cast<HitboxType>(NemesisHitboxTypeIndex);
							}
						}

						const char* NemesisSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::NemesisSmoothingMethod, NemesisSmoothingMethodIndex, IM_ARRAYSIZE(NemesisSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedNemesis", &Features::Aimbot::NemesisSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Nemesis\nHigher = Faster");
							}

							if (Features::Aimbot::NemesisSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::NemesisSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedNemesis", &Features::Aimbot::NemesisMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Nemesis", &Features::Aimbot::NemesisFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Nemesis", &Features::Aimbot::NemesisZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::NemesisSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::NemesisSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Nemesis Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Nemesis Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedNemesis", &Features::Aimbot::NemesisExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedNemesis", &Features::Aimbot::NemesisDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::NemesisFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::NemesisMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::NemesisMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 23) // Mozambique
				{
					if (Features::Aimbot::Mozambique) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##MozambiqueAimbot", &Features::Aimbot::MozambiqueFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##MozambiqueAimbot", &Features::Aimbot::MozambiqueADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int MozambiqueAimBind = static_cast<int>(Features::AimbotBinds::MozambiqueAimBind);
							ImGui::ComboBox("Aim Bind##MozambiqueAimbot", &MozambiqueAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::MozambiqueAimBind = static_cast<InputKeyType>(MozambiqueAimBind);
							int MozambiqueExtraBind = static_cast<int>(Features::AimbotBinds::MozambiqueExtraBind);
							ImGui::ComboBox("Extra Bind##MozambiqueAimbot", &MozambiqueExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::MozambiqueExtraBind = static_cast<InputKeyType>(MozambiqueExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##MozambiqueAdvancedHitbox", &Features::Aimbot::MozambiqueClosestHitbox);
							if (!Features::Aimbot::MozambiqueClosestHitbox) {
								const char* MozambiqueHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int MozambiqueHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::MozambiqueHitbox);
								ImGui::ComboBox("Hitbox Type##MozambiqueAdvancedHitbox", &MozambiqueHitboxTypeIndex, MozambiqueHitboxTypes, IM_ARRAYSIZE(MozambiqueHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::MozambiqueHitbox = static_cast<HitboxType>(MozambiqueHitboxTypeIndex);
							}
						}

						const char* MozambiqueSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::MozambiqueSmoothingMethod, MozambiqueSmoothingMethodIndex, IM_ARRAYSIZE(MozambiqueSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedMozambique", &Features::Aimbot::MozambiqueSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Mozambique\nHigher = Faster");
							}

							if (Features::Aimbot::MozambiqueSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::MozambiqueSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedMozambique", &Features::Aimbot::MozambiqueMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Mozambique", &Features::Aimbot::MozambiqueFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Mozambique", &Features::Aimbot::MozambiqueZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::MozambiqueSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::MozambiqueSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mozambique Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mozambique Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedMozambique", &Features::Aimbot::MozambiqueExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedMozambique", &Features::Aimbot::MozambiqueDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::MozambiqueFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::MozambiqueMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::MozambiqueMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 24) // Peacekeeper
				{
					if (Features::Aimbot::Peacekeeper) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##PeacekeeperAimbot", &Features::Aimbot::PeacekeeperFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##PeacekeeperAimbot", &Features::Aimbot::PeacekeeperADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int PeacekeeperAimBind = static_cast<int>(Features::AimbotBinds::PeacekeeperAimBind);
							ImGui::ComboBox("Aim Bind##PeacekeeperAimbot", &PeacekeeperAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::PeacekeeperAimBind = static_cast<InputKeyType>(PeacekeeperAimBind);
							int PeacekeeperExtraBind = static_cast<int>(Features::AimbotBinds::PeacekeeperExtraBind);
							ImGui::ComboBox("Extra Bind##PeacekeeperAimbot", &PeacekeeperExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::PeacekeeperExtraBind = static_cast<InputKeyType>(PeacekeeperExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##PeacekeeperAdvancedHitbox", &Features::Aimbot::PeacekeeperClosestHitbox);
							if (!Features::Aimbot::PeacekeeperClosestHitbox) {
								const char* PeacekeeperHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int PeacekeeperHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::PeacekeeperHitbox);
								ImGui::ComboBox("Hitbox Type##PeacekeeperAdvancedHitbox", &PeacekeeperHitboxTypeIndex, PeacekeeperHitboxTypes, IM_ARRAYSIZE(PeacekeeperHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::PeacekeeperHitbox = static_cast<HitboxType>(PeacekeeperHitboxTypeIndex);
							}
						}

						const char* PeacekeeperSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::PeacekeeperSmoothingMethod, PeacekeeperSmoothingMethodIndex, IM_ARRAYSIZE(PeacekeeperSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Peacekeeper\nHigher = Faster");
							}

							if (Features::Aimbot::PeacekeeperSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::PeacekeeperSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Peacekeeper", &Features::Aimbot::PeacekeeperFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Peacekeeper", &Features::Aimbot::PeacekeeperZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::PeacekeeperSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::PeacekeeperSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Peacekeeper Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Peacekeeper Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedPeacekeeper", &Features::Aimbot::PeacekeeperDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::PeacekeeperFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::PeacekeeperMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::PeacekeeperMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 25) // Mastiff
				{
					if (Features::Aimbot::Mastiff) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##MastiffAimbot", &Features::Aimbot::MastiffFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##MastiffAimbot", &Features::Aimbot::MastiffADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int MastiffAimBind = static_cast<int>(Features::AimbotBinds::MastiffAimBind);
							ImGui::ComboBox("Aim Bind##MastiffAimbot", &MastiffAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::MastiffAimBind = static_cast<InputKeyType>(MastiffAimBind);
							int MastiffExtraBind = static_cast<int>(Features::AimbotBinds::MastiffExtraBind);
							ImGui::ComboBox("Extra Bind##MastiffAimbot", &MastiffExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::MastiffExtraBind = static_cast<InputKeyType>(MastiffExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##MastiffAdvancedHitbox", &Features::Aimbot::MastiffClosestHitbox);
							if (!Features::Aimbot::MastiffClosestHitbox) {
								const char* MastiffHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int MastiffHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::MastiffHitbox);
								ImGui::ComboBox("Hitbox Type##MastiffAdvancedHitbox", &MastiffHitboxTypeIndex, MastiffHitboxTypes, IM_ARRAYSIZE(MastiffHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::MastiffHitbox = static_cast<HitboxType>(MastiffHitboxTypeIndex);
							}
						}

						const char* MastiffSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::MastiffSmoothingMethod, MastiffSmoothingMethodIndex, IM_ARRAYSIZE(MastiffSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedMastiff", &Features::Aimbot::MastiffSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Mastiff\nHigher = Faster");
							}

							if (Features::Aimbot::MastiffSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::MastiffSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedMastiff", &Features::Aimbot::MastiffMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Mastiff", &Features::Aimbot::MastiffFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Mastiff", &Features::Aimbot::MastiffZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::MastiffSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::MastiffSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mastiff Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Mastiff Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedMastiff", &Features::Aimbot::MastiffExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedMastiff", &Features::Aimbot::MastiffDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::MastiffFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::MastiffMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::MastiffMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 27) // Longbow
				{
					if (Features::Aimbot::Longbow) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##LongbowAimbot", &Features::Aimbot::LongbowFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##LongbowAimbot", &Features::Aimbot::LongbowADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int LongbowAimBind = static_cast<int>(Features::AimbotBinds::LongbowAimBind);
							ImGui::ComboBox("Aim Bind##LongbowAimbot", &LongbowAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::LongbowAimBind = static_cast<InputKeyType>(LongbowAimBind);
							int LongbowExtraBind = static_cast<int>(Features::AimbotBinds::LongbowExtraBind);
							ImGui::ComboBox("Extra Bind##LongbowAimbot", &LongbowExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::LongbowExtraBind = static_cast<InputKeyType>(LongbowExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##LongbowAdvancedHitbox", &Features::Aimbot::LongbowClosestHitbox);
							if (!Features::Aimbot::LongbowClosestHitbox) {
								const char* LongbowHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int LongbowHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::LongbowHitbox);
								ImGui::ComboBox("Hitbox Type##LongbowAdvancedHitbox", &LongbowHitboxTypeIndex, LongbowHitboxTypes, IM_ARRAYSIZE(LongbowHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::LongbowHitbox = static_cast<HitboxType>(LongbowHitboxTypeIndex);
							}
						}

						const char* LongbowSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::LongbowSmoothingMethod, LongbowSmoothingMethodIndex, IM_ARRAYSIZE(LongbowSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedLongbow", &Features::Aimbot::LongbowSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Longbow\nHigher = Faster");
							}

							if (Features::Aimbot::LongbowSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::LongbowSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedLongbow", &Features::Aimbot::LongbowMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Longbow", &Features::Aimbot::LongbowFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Longbow", &Features::Aimbot::LongbowZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::LongbowSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::LongbowSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Longbow Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Longbow Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedLongbow", &Features::Aimbot::LongbowExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedLongbow", &Features::Aimbot::LongbowDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::LongbowFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::LongbowMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::LongbowMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 28) // ChargeRifle
				{
					if (Features::Aimbot::ChargeRifle) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##ChargeRifleAimbot", &Features::Aimbot::ChargeRifleFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##ChargeRifleAimbot", &Features::Aimbot::ChargeRifleADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int ChargeRifleAimBind = static_cast<int>(Features::AimbotBinds::ChargeRifleAimBind);
							ImGui::ComboBox("Aim Bind##ChargeRifleAimbot", &ChargeRifleAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ChargeRifleAimBind = static_cast<InputKeyType>(ChargeRifleAimBind);
							int ChargeRifleExtraBind = static_cast<int>(Features::AimbotBinds::ChargeRifleExtraBind);
							ImGui::ComboBox("Extra Bind##ChargeRifleAimbot", &ChargeRifleExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ChargeRifleExtraBind = static_cast<InputKeyType>(ChargeRifleExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##ChargeRifleAdvancedHitbox", &Features::Aimbot::ChargeRifleClosestHitbox);
							if (!Features::Aimbot::ChargeRifleClosestHitbox) {
								const char* ChargeRifleHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int ChargeRifleHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::ChargeRifleHitbox);
								ImGui::ComboBox("Hitbox Type##ChargeRifleAdvancedHitbox", &ChargeRifleHitboxTypeIndex, ChargeRifleHitboxTypes, IM_ARRAYSIZE(ChargeRifleHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::ChargeRifleHitbox = static_cast<HitboxType>(ChargeRifleHitboxTypeIndex);
							}
						}

						const char* ChargeRifleSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::ChargeRifleSmoothingMethod, ChargeRifleSmoothingMethodIndex, IM_ARRAYSIZE(ChargeRifleSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The ChargeRifle\nHigher = Faster");
							}

							if (Features::Aimbot::ChargeRifleSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ChargeRifleSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##ChargeRifle", &Features::Aimbot::ChargeRifleFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##ChargeRifle", &Features::Aimbot::ChargeRifleZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::ChargeRifleSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ChargeRifleSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ChargeRifle Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ChargeRifle Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedChargeRifle", &Features::Aimbot::ChargeRifleExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedChargeRifle", &Features::Aimbot::ChargeRifleDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::ChargeRifleFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::ChargeRifleMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::ChargeRifleMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 29) // Sentinel
				{
					if (Features::Aimbot::Sentinel) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##SentinelAimbot", &Features::Aimbot::SentinelFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##SentinelAimbot", &Features::Aimbot::SentinelADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int SentinelAimBind = static_cast<int>(Features::AimbotBinds::SentinelAimBind);
							ImGui::ComboBox("Aim Bind##SentinelAimbot", &SentinelAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::SentinelAimBind = static_cast<InputKeyType>(SentinelAimBind);
							int SentinelExtraBind = static_cast<int>(Features::AimbotBinds::SentinelExtraBind);
							ImGui::ComboBox("Extra Bind##SentinelAimbot", &SentinelExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::SentinelExtraBind = static_cast<InputKeyType>(SentinelExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##SentinelAdvancedHitbox", &Features::Aimbot::SentinelClosestHitbox);
							if (!Features::Aimbot::SentinelClosestHitbox) {
								const char* SentinelHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int SentinelHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::SentinelHitbox);
								ImGui::ComboBox("Hitbox Type##SentinelAdvancedHitbox", &SentinelHitboxTypeIndex, SentinelHitboxTypes, IM_ARRAYSIZE(SentinelHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::SentinelHitbox = static_cast<HitboxType>(SentinelHitboxTypeIndex);
							}
						}

						const char* SentinelSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SentinelSmoothingMethod, SentinelSmoothingMethodIndex, IM_ARRAYSIZE(SentinelSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedSentinel", &Features::Aimbot::SentinelSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Sentinel\nHigher = Faster");
							}

							if (Features::Aimbot::SentinelSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::SentinelSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedSentinel", &Features::Aimbot::SentinelMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Sentinel", &Features::Aimbot::SentinelFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Sentinel", &Features::Aimbot::SentinelZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::SentinelSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::SentinelSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Sentinel Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Sentinel Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedSentinel", &Features::Aimbot::SentinelExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedSentinel", &Features::Aimbot::SentinelDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::SentinelFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::SentinelMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::SentinelMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 30) // Wingman
				{
					if (Features::Aimbot::Wingman) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##WingmanAimbot", &Features::Aimbot::WingmanFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##WingmanAimbot", &Features::Aimbot::WingmanADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int WingmanAimBind = static_cast<int>(Features::AimbotBinds::WingmanAimBind);
							ImGui::ComboBox("Aim Bind##WingmanAimbot", &WingmanAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::WingmanAimBind = static_cast<InputKeyType>(WingmanAimBind);
							int WingmanExtraBind = static_cast<int>(Features::AimbotBinds::WingmanExtraBind);
							ImGui::ComboBox("Extra Bind##WingmanAimbot", &WingmanExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::WingmanExtraBind = static_cast<InputKeyType>(WingmanExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##WingmanAdvancedHitbox", &Features::Aimbot::WingmanClosestHitbox);
							if (!Features::Aimbot::WingmanClosestHitbox) {
								const char* WingmanHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int WingmanHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::WingmanHitbox);
								ImGui::ComboBox("Hitbox Type##WingmanAdvancedHitbox", &WingmanHitboxTypeIndex, WingmanHitboxTypes, IM_ARRAYSIZE(WingmanHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::WingmanHitbox = static_cast<HitboxType>(WingmanHitboxTypeIndex);
							}
						}

						const char* WingmanSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::WingmanSmoothingMethod, WingmanSmoothingMethodIndex, IM_ARRAYSIZE(WingmanSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedWingman", &Features::Aimbot::WingmanSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Wingman\nHigher = Faster");
							}

							if (Features::Aimbot::WingmanSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedWingman", &Features::Aimbot::WingmanHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedWingman", &Features::Aimbot::WingmanADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::WingmanSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedWingman", &Features::Aimbot::WingmanMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedWingman", &Features::Aimbot::WingmanMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedWingman", &Features::Aimbot::WingmanMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedWingman", &Features::Aimbot::WingmanMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Wingman", &Features::Aimbot::WingmanFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Wingman", &Features::Aimbot::WingmanZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::WingmanSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::WingmanSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Wingman Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Wingman Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedWingman", &Features::Aimbot::WingmanExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedWingman", &Features::Aimbot::WingmanDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::WingmanFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::WingmanMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::WingmanMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 31) // EVA8
				{
					if (Features::Aimbot::EVA8) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##EVA8Aimbot", &Features::Aimbot::EVA8Fire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##EVA8Aimbot", &Features::Aimbot::EVA8ADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int EVA8AimBind = static_cast<int>(Features::AimbotBinds::EVA8AimBind);
							ImGui::ComboBox("Aim Bind##EVA8Aimbot", &EVA8AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::EVA8AimBind = static_cast<InputKeyType>(EVA8AimBind);
							int EVA8ExtraBind = static_cast<int>(Features::AimbotBinds::EVA8ExtraBind);
							ImGui::ComboBox("Extra Bind##EVA8Aimbot", &EVA8ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::EVA8ExtraBind = static_cast<InputKeyType>(EVA8ExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##EVA8AdvancedHitbox", &Features::Aimbot::EVA8ClosestHitbox);
							if (!Features::Aimbot::EVA8ClosestHitbox) {
								const char* EVA8HitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int EVA8HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::EVA8Hitbox);
								ImGui::ComboBox("Hitbox Type##EVA8AdvancedHitbox", &EVA8HitboxTypeIndex, EVA8HitboxTypes, IM_ARRAYSIZE(EVA8HitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::EVA8Hitbox = static_cast<HitboxType>(EVA8HitboxTypeIndex);
							}
						}

						const char* EVA8SmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::EVA8SmoothingMethod, EVA8SmoothingMethodIndex, IM_ARRAYSIZE(EVA8SmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedEVA8", &Features::Aimbot::EVA8Speed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The EVA8\nHigher = Faster");
							}

							if (Features::Aimbot::EVA8SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8HipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8ADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::EVA8SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8MinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8MaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8MinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedEVA8", &Features::Aimbot::EVA8MaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##EVA8", &Features::Aimbot::EVA8FOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##EVA8", &Features::Aimbot::EVA8ZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::EVA8SmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8HipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8ADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::EVA8SmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8MinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8MaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The EVA8 Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8MinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8MaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The EVA8 Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedEVA8", &Features::Aimbot::EVA8ExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedEVA8", &Features::Aimbot::EVA8Deadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::EVA8FOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::EVA8MinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::EVA8MaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 32) // Bocek
				{
					if (Features::Aimbot::Bocek) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##BocekAimbot", &Features::Aimbot::BocekFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##BocekAimbot", &Features::Aimbot::BocekADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int BocekAimBind = static_cast<int>(Features::AimbotBinds::BocekAimBind);
							ImGui::ComboBox("Aim Bind##BocekAimbot", &BocekAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::BocekAimBind = static_cast<InputKeyType>(BocekAimBind);
							int BocekExtraBind = static_cast<int>(Features::AimbotBinds::BocekExtraBind);
							ImGui::ComboBox("Extra Bind##BocekAimbot", &BocekExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::BocekExtraBind = static_cast<InputKeyType>(BocekExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##BocekAdvancedHitbox", &Features::Aimbot::BocekClosestHitbox);
							if (!Features::Aimbot::BocekClosestHitbox) {
								const char* BocekHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int BocekHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::BocekHitbox);
								ImGui::ComboBox("Hitbox Type##BocekAdvancedHitbox", &BocekHitboxTypeIndex, BocekHitboxTypes, IM_ARRAYSIZE(BocekHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::BocekHitbox = static_cast<HitboxType>(BocekHitboxTypeIndex);
							}
						}

						const char* BocekSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::BocekSmoothingMethod, BocekSmoothingMethodIndex, IM_ARRAYSIZE(BocekSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedBocek", &Features::Aimbot::BocekSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Bocek\nHigher = Faster");
							}

							if (Features::Aimbot::BocekSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedBocek", &Features::Aimbot::BocekHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedBocek", &Features::Aimbot::BocekADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::BocekSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedBocek", &Features::Aimbot::BocekMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedBocek", &Features::Aimbot::BocekMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedBocek", &Features::Aimbot::BocekMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedBocek", &Features::Aimbot::BocekMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Bocek", &Features::Aimbot::BocekFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Bocek", &Features::Aimbot::BocekZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::BocekSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedBocek", &Features::Aimbot::BocekHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedBocek", &Features::Aimbot::BocekADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::BocekSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedBocek", &Features::Aimbot::BocekMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedBocek", &Features::Aimbot::BocekMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Bocek Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedBocek", &Features::Aimbot::BocekMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedBocek", &Features::Aimbot::BocekMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Bocek Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedBocek", &Features::Aimbot::BocekExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedBocek", &Features::Aimbot::BocekDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::BocekFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::BocekMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::BocekMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 33) // Kraber
				{
					if (Features::Aimbot::Kraber) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##KraberAimbot", &Features::Aimbot::KraberFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##KraberAimbot", &Features::Aimbot::KraberADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int KraberAimBind = static_cast<int>(Features::AimbotBinds::KraberAimBind);
							ImGui::ComboBox("Aim Bind##KraberAimbot", &KraberAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::KraberAimBind = static_cast<InputKeyType>(KraberAimBind);
							int KraberExtraBind = static_cast<int>(Features::AimbotBinds::KraberExtraBind);
							ImGui::ComboBox("Extra Bind##KraberAimbot", &KraberExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::KraberExtraBind = static_cast<InputKeyType>(KraberExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##KraberAdvancedHitbox", &Features::Aimbot::KraberClosestHitbox);
							if (!Features::Aimbot::KraberClosestHitbox) {
								const char* KraberHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int KraberHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::KraberHitbox);
								ImGui::ComboBox("Hitbox Type##KraberAdvancedHitbox", &KraberHitboxTypeIndex, KraberHitboxTypes, IM_ARRAYSIZE(KraberHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::KraberHitbox = static_cast<HitboxType>(KraberHitboxTypeIndex);
							}
						}

						const char* KraberSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::KraberSmoothingMethod, KraberSmoothingMethodIndex, IM_ARRAYSIZE(KraberSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedKraber", &Features::Aimbot::KraberSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The Kraber\nHigher = Faster");
							}

							if (Features::Aimbot::KraberSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedKraber", &Features::Aimbot::KraberHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedKraber", &Features::Aimbot::KraberADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::KraberSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedKraber", &Features::Aimbot::KraberMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedKraber", &Features::Aimbot::KraberMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedKraber", &Features::Aimbot::KraberMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedKraber", &Features::Aimbot::KraberMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##Kraber", &Features::Aimbot::KraberFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##Kraber", &Features::Aimbot::KraberZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::KraberSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedKraber", &Features::Aimbot::KraberHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedKraber", &Features::Aimbot::KraberADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::KraberSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedKraber", &Features::Aimbot::KraberMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedKraber", &Features::Aimbot::KraberMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Kraber Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedKraber", &Features::Aimbot::KraberMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedKraber", &Features::Aimbot::KraberMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The Kraber Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedKraber", &Features::Aimbot::KraberExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedKraber", &Features::Aimbot::KraberDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::KraberFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::KraberMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::KraberMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				if (WeaponsComboBoxCurrent == 34) // ThrowingKnife
				{
					if (Features::Aimbot::Knife) {
						ImGui::Text("Keybinds");
						if (Features::Aimbot::BindMethod == 0) { // OnFire & OnADS
							ImGui::Checkbox("On Fire##ThrowingKnifeAimbot", &Features::Aimbot::ThrowingKnifeFire);
							ImGui::SameLine();
							ImGui::Checkbox("On ADS##ThrowingKnifeAimbot", &Features::Aimbot::ThrowingKnifeADS);
						}
						if (Features::Aimbot::BindMethod == 1) { // Keybinds
							int ThrowingKnifeAimBind = static_cast<int>(Features::AimbotBinds::ThrowingKnifeAimBind);
							ImGui::ComboBox("Aim Bind##ThrowingKnifeAimbot", &ThrowingKnifeAimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ThrowingKnifeAimBind = static_cast<InputKeyType>(ThrowingKnifeAimBind);
							int ThrowingKnifeExtraBind = static_cast<int>(Features::AimbotBinds::ThrowingKnifeExtraBind);
							ImGui::ComboBox("Extra Bind##ThrowingKnifeAimbot", &ThrowingKnifeExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
							Features::AimbotBinds::ThrowingKnifeExtraBind = static_cast<InputKeyType>(ThrowingKnifeExtraBind);
						}
						if (Features::Aimbot::AimbotMode == 0) {
							ImGui::Text("Hitbox");
							ImGui::Checkbox("Closest To Crosshair##ThrowingKnifeAdvancedHitbox", &Features::Aimbot::ThrowingKnifeClosestHitbox);
							if (!Features::Aimbot::ThrowingKnifeClosestHitbox) {
								const char* ThrowingKnifeHitboxTypes[] = { "Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip" };
								int ThrowingKnifeHitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::ThrowingKnifeHitbox);
								ImGui::ComboBox("Hitbox Type##ThrowingKnifeAdvancedHitbox", &ThrowingKnifeHitboxTypeIndex, ThrowingKnifeHitboxTypes, IM_ARRAYSIZE(ThrowingKnifeHitboxTypes));
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Which bone the aimbot will aim at.");
								Features::AimbotHitboxes::ThrowingKnifeHitbox = static_cast<HitboxType>(ThrowingKnifeHitboxTypeIndex);
							}
						}

						const char* ThrowingKnifeSmoothingMethodIndex[] = { "Static", "Random" };
						ImGui::ComboBox("Smoothing Method", &Features::Aimbot::ThrowingKnifeSmoothingMethod, ThrowingKnifeSmoothingMethodIndex, IM_ARRAYSIZE(ThrowingKnifeSmoothingMethodIndex));

						if (Features::Aimbot::AimbotMode == 0) {
							if (Features::Aimbot::InputMethod == 0) // Mouse Only
							{
								ImGui::MainSliderFloat("Speed##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeSpeed, 1, 100, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Speed Of The Aim-Assist For The ThrowingKnife\nHigher = Faster");
							}

							if (Features::Aimbot::ThrowingKnifeSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ThrowingKnifeSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMinHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMaxHipfireSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMinADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMaxADSSmooth, 0, 0.99, "%.3f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("FOV##ThrowingKnife", &Features::Aimbot::ThrowingKnifeFOV, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View");
							ImGui::MainSliderFloat("Zoom Scale##ThrowingKnife", &Features::Aimbot::ThrowingKnifeZoomScale, 0, 5, "%.1f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View For Scopes");
						}

						if (Features::Aimbot::AimbotMode == 1) {
							if (Features::Aimbot::ThrowingKnifeSmoothingMethod == 0) // Static
							{
								ImGui::MainSliderFloat("Hipfire Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("ADS Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
							}

							if (Features::Aimbot::ThrowingKnifeSmoothingMethod == 1) // Random
							{
								ImGui::MainSliderFloat("Min Hipfire Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMinHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max Hipfire Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMaxHipfireSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst Hipfiring.\nHigher = Smoother");
								ImGui::MainSliderFloat("Min ADS Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMinADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
								ImGui::MainSliderFloat("Max ADS Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeMaxADSSmooth1, 1, 1000, "%.0f");
								if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
									ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist For The ThrowingKnife Whilst ADS.\nHigher = Smoother");
							}

							ImGui::MainSliderFloat("Extra Smoothing##1AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeExtraSmooth1, 1, 9999, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
							ImGui::MainSliderFloat("Deadzone##AdvancedThrowingKnife", &Features::Aimbot::ThrowingKnifeDeadzone, 0, 10, "%.03f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");

							ImGui::MainSliderFloat("FOV", &Features::Aimbot::ThrowingKnifeFOV1, 1, 90, "%.0f");
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
								ImGui::SetTooltip("Field of View.");
						}

						ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::ThrowingKnifeMinDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Minimum Distance for Aim-Assist to work");
						ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::ThrowingKnifeMaxDistance1, 1, 500, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Maximum Distance for Aim-Assist to work");

						ImGui::Spacing();
					}

					else {
						ImGui::Text("Selected Weapon Is Not Enabled! Check Weapon Selection!");
					}
				}

				ImGui::Spacing();
				ImGui::EndChildFrame();
			}
			ImGui::NextColumn();

			// ImGui::EndChildFrame();
		}
	}

	void AdvancedRCSTab(int WeaponID) {
		ImGui::BeginChildFrame(14, ImVec2(WindowWidth - 220, 128), true);
		{
			if (Features::RCS::RCSEnabled) {
				ImGui::Spacing();
				ImGui::Text("Advanced RCS - Recoil Control");
				ImGui::Checkbox("Enabled", &Features::RCS::AdvancedRCS);
			}
			if (!Features::RCS::RCSEnabled) {
				ImGui::Text("RCS Must Be Enabled To Enable Advanced RCS.");
			}
			if (Features::RCS::RCSEnabled && Features::RCS::AdvancedRCS) {
				const char* RCSModeIndex[] = { "Standalone", "Combined" };
				ImGui::ComboBox("RCS Method", &Features::RCS::RCSMode, RCSModeIndex, IM_ARRAYSIZE(RCSModeIndex));
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("What RCS Method You Would Like.\nStandalone Provideds Legit & Customizable Settings.\nCombined Works Alongside Aimbot And Provides Better Recoil Control (Aimbot Must Be Enabled & Aimbot Mode = Cubic Bezier (xap-client)!)");
				ImGui::Text("Conditions");
				ImGui::Checkbox("On ADS Only?", &Features::RCS::OnADS);
				if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					ImGui::SetTooltip("Toggle when the RCS will take control\nEnabled = Only when aiming.\nDisabled = Always.");
			}
			ImGui::EndChildFrame();
		}

		if (Features::RCS::AdvancedRCS) {
			ImGui::BeginChildFrame(13, ImVec2({ static_cast<float>(WindowWidth - 220), 96 }), true);
			{
				ImGui::Spacing();
				ImGui::Text("Current Held Weapon: ");
				if (Features::RCS::P2020 && WeaponID == WeaponIDs::P2020) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "P2020");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedP2020", &Features::RCS::P2020Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the P2020.");
						ImGui::MainSliderFloat("Yaw##AdvancedP2020", &Features::RCS::P2020Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the P2020.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedP2020", &Features::RCS::P2020PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The P2020.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedP2020", &Features::RCS::P2020YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The P2020.");
					}
				}

				if (Features::RCS::RE45 && WeaponID == WeaponIDs::RE45) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "RE45");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedRE45", &Features::RCS::RE45Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the RE45.");
						ImGui::MainSliderFloat("Yaw##AdvancedRE45", &Features::RCS::RE45Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the RE45.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRE45", &Features::RCS::RE45PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The RE45.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRE45", &Features::RCS::RE45YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The RE45.");
					}
				}

				if (Features::RCS::Alternator && WeaponID == WeaponIDs::ALTERNATOR) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Alternator");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedAlternator", &Features::RCS::AlternatorPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Alternator.");
						ImGui::MainSliderFloat("Yaw##AdvancedAlternator", &Features::RCS::AlternatorYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Alternator.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedAlternator", &Features::RCS::AlternatorPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Alternator.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedAlternator", &Features::RCS::AlternatorYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Alternator.");
					}
				}

				if (Features::RCS::R99 && WeaponID == WeaponIDs::R99) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R99");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedR99", &Features::RCS::R99Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the R99.");
						ImGui::MainSliderFloat("Yaw##AdvancedR99", &Features::RCS::R99Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the R99.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedR99", &Features::RCS::R99PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The R99.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedR99", &Features::RCS::R99YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The R99.");
					}
				}

				if (Features::RCS::R301 && WeaponID == WeaponIDs::R301) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R301");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedR301", &Features::RCS::R301Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the R301.");
						ImGui::MainSliderFloat("Yaw##AdvancedR301", &Features::RCS::R301Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the R301.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedR301", &Features::RCS::R301PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The R301.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedR301", &Features::RCS::R301YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The R301.");
					}
				}

				if (Features::RCS::Spitfire && WeaponID == WeaponIDs::SPITFIRE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Spitfire");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedSpitfire", &Features::RCS::SpitfirePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Spitfire.");
						ImGui::MainSliderFloat("Yaw##AdvancedSpitfire", &Features::RCS::SpitfireYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Spitfire.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedSpitfire", &Features::RCS::SpitfirePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Spitfire.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedSpitfire", &Features::RCS::SpitfireYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Spitfire.");
					}
				}

				if (Features::RCS::G7 && WeaponID == WeaponIDs::G7) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "G7");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedG7", &Features::RCS::G7Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the G7.");
						ImGui::MainSliderFloat("Yaw##AdvancedG7", &Features::RCS::G7Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the G7.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedG7", &Features::RCS::G7PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The G7.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedG7", &Features::RCS::G7YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The G7.");
					}
				}

				if (Features::RCS::Flatline && WeaponID == WeaponIDs::FLATLINE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Flatline");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedFlatline", &Features::RCS::FlatlinePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Flatline.");
						ImGui::MainSliderFloat("Yaw##AdvancedFlatline", &Features::RCS::FlatlineYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Flatline.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedFlatline", &Features::RCS::FlatlinePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Flatline.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedFlatline", &Features::RCS::FlatlineYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Flatline.");
					}
				}

				if (Features::RCS::Hemlock && WeaponID == WeaponIDs::HEMLOCK) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Hemlock");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedHemlock", &Features::RCS::HemlockPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Hemlock.");
						ImGui::MainSliderFloat("Yaw##AdvancedHemlock", &Features::RCS::HemlockYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Hemlock.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedHemlock", &Features::RCS::HemlockPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Hemlock.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedHemlock", &Features::RCS::HemlockYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Hemlock.");
					}
				}

				if (Features::RCS::Prowler && WeaponID == WeaponIDs::PROWLER) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Prowler");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedProwler", &Features::RCS::ProwlerPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Prowler.");
						ImGui::MainSliderFloat("Yaw##AdvancedProwler", &Features::RCS::ProwlerYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Prowler.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedProwler", &Features::RCS::ProwlerPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Prowler.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedProwler", &Features::RCS::ProwlerYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Prowler.");
					}
				}

				if (Features::RCS::Repeater && WeaponID == WeaponIDs::REPEATER) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Repeater");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedRepeater", &Features::RCS::RepeaterPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Repeater.");
						ImGui::MainSliderFloat("Yaw##AdvancedRepeater", &Features::RCS::RepeaterYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Repeater.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRepeater", &Features::RCS::RepeaterPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Repeater.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRepeater", &Features::RCS::RepeaterYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Repeater.");
					}
				}

				if (Features::RCS::Rampage && WeaponID == WeaponIDs::RAMPAGE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Rampage");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedRampage", &Features::RCS::RampagePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Rampage.");
						ImGui::MainSliderFloat("Yaw##AdvancedRampage", &Features::RCS::RampageYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Rampage.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRampage", &Features::RCS::RampagePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Rampage.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRampage", &Features::RCS::RampageYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Rampage.");
					}
				}

				if (Features::RCS::CARSMG && WeaponID == WeaponIDs::CAR) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "CARSMG");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedCARSMG", &Features::RCS::CARSMGPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the CARSMG.");
						ImGui::MainSliderFloat("Yaw##AdvancedCARSMG", &Features::RCS::CARSMGYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the CARSMG.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedCARSMG", &Features::RCS::CARSMGPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The CARSMG.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedCARSMG", &Features::RCS::CARSMGYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The CARSMG.");
					}
				}

				if (Features::RCS::Havoc && WeaponID == WeaponIDs::HAVOC) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Havoc");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedHavoc", &Features::RCS::HavocPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Havoc.");
						ImGui::MainSliderFloat("Yaw##AdvancedHavoc", &Features::RCS::HavocYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Havoc.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedHavoc", &Features::RCS::HavocPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Havoc.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedHavoc", &Features::RCS::HavocYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Havoc.");
					}
				}

				if (Features::RCS::Devotion && WeaponID == WeaponIDs::DEVOTION) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Devotion");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedDevotion", &Features::RCS::DevotionPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Devotion.");
						ImGui::MainSliderFloat("Yaw##AdvancedDevotion", &Features::RCS::DevotionYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Devotion.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedDevotion", &Features::RCS::DevotionPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Devotion.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedDevotion", &Features::RCS::DevotionYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Devotion.");
					}
				}

				if (Features::RCS::LSTAR && WeaponID == WeaponIDs::LSTAR) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "LSTAR");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedLSTAR", &Features::RCS::LSTARPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the LSTAR.");
						ImGui::MainSliderFloat("Yaw##AdvancedLSTAR", &Features::RCS::LSTARYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the LSTAR.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedLSTAR", &Features::RCS::LSTARPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The LSTAR.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedLSTAR", &Features::RCS::LSTARYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The LSTAR.");
					}
				}

				if (Features::RCS::TripleTake && WeaponID == WeaponIDs::TRIPLETAKE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "TripleTake");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedTripleTake", &Features::RCS::TripleTakePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the TripleTake.");
						ImGui::MainSliderFloat("Yaw##AdvancedTripleTake", &Features::RCS::TripleTakeYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the TripleTake.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedTripleTake", &Features::RCS::TripleTakePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The TripleTake.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedTripleTake", &Features::RCS::TripleTakeYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The TripleTake.");
					}
				}

				if (Features::RCS::Volt && WeaponID == WeaponIDs::VOLT) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Volt");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedVolt", &Features::RCS::VoltPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Volt.");
						ImGui::MainSliderFloat("Yaw##AdvancedVolt", &Features::RCS::VoltYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Volt.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedVolt", &Features::RCS::VoltPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Volt.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedVolt", &Features::RCS::VoltYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Volt.");
					}
				}

				if (Features::RCS::Nemesis && WeaponID == WeaponIDs::NEMESIS) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Nemesis");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedNemesis", &Features::RCS::NemesisPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Nemesis.");
						ImGui::MainSliderFloat("Yaw##AdvancedNemesis", &Features::RCS::NemesisYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Nemesis.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedNemesis", &Features::RCS::NemesisPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Nemesis.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedNemesis", &Features::RCS::NemesisYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Nemesis.");
					}
				}

				if (Features::RCS::Mozambique && WeaponID == WeaponIDs::MOZAMBIQUE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Mozambique");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedMozambique", &Features::RCS::MozambiquePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Mozambique.");
						ImGui::MainSliderFloat("Yaw##AdvancedMozambique", &Features::RCS::MozambiqueYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Mozambique.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedMozambique", &Features::RCS::MozambiquePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Mozambique.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedMozambique", &Features::RCS::MozambiqueYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Mozambique.");
					}
				}

				if (Features::RCS::Peacekeeper && WeaponID == WeaponIDs::PEACEKEEPER) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Peacekeeper");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedPeacekeeper", &Features::RCS::PeacekeeperPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Peacekeeper.");
						ImGui::MainSliderFloat("Yaw##AdvancedPeacekeeper", &Features::RCS::PeacekeeperYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Peacekeeper.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedPeacekeeper", &Features::RCS::PeacekeeperPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Peacekeeper.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedPeacekeeper", &Features::RCS::PeacekeeperYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Peacekeeper.");
					}
				}

				if (Features::RCS::Mastiff && WeaponID == WeaponIDs::MASTIFF) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Mastiff");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedMastiff", &Features::RCS::MastiffPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Mastiff.");
						ImGui::MainSliderFloat("Yaw##AdvancedMastiff", &Features::RCS::MastiffYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Mastiff.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedMastiff", &Features::RCS::MastiffPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Mastiff.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedMastiff", &Features::RCS::MastiffYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Mastiff.");
					}
				}

				if (Features::RCS::Longbow && WeaponID == WeaponIDs::LONGBOW) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Longbow");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedLongbow", &Features::RCS::LongbowPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Longbow.");
						ImGui::MainSliderFloat("Yaw##AdvancedLongbow", &Features::RCS::LongbowYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Longbow.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedLongbow", &Features::RCS::LongbowPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Longbow.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedLongbow", &Features::RCS::LongbowYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Longbow.");
					}
				}

				if (Features::RCS::ChargeRifle && WeaponID == WeaponIDs::CHARGE_RIFLE) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "ChargeRifle");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedChargeRifle", &Features::RCS::ChargeRiflePitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the ChargeRifle.");
						ImGui::MainSliderFloat("Yaw##AdvancedChargeRifle", &Features::RCS::ChargeRifleYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the ChargeRifle.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedChargeRifle", &Features::RCS::ChargeRiflePitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The ChargeRifle.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedChargeRifle", &Features::RCS::ChargeRifleYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The ChargeRifle.");
					}
				}

				if (Features::RCS::Sentinel && WeaponID == WeaponIDs::SENTINEL) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Sentinel");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedSentinel", &Features::RCS::SentinelPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Sentinel.");
						ImGui::MainSliderFloat("Yaw##AdvancedSentinel", &Features::RCS::SentinelYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Sentinel.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedSentinel", &Features::RCS::SentinelPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Sentinel.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedSentinel", &Features::RCS::SentinelYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Sentinel.");
					}
				}

				if (Features::RCS::Wingman && WeaponID == WeaponIDs::WINGMAN) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Wingman");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedWingman", &Features::RCS::WingmanPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Wingman.");
						ImGui::MainSliderFloat("Yaw##AdvancedWingman", &Features::RCS::WingmanYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Wingman.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedWingman", &Features::RCS::WingmanPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Wingman.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedWingman", &Features::RCS::WingmanYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Wingman.");
					}
				}

				if (Features::RCS::EVA8 && WeaponID == WeaponIDs::EVA8) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "EVA8");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedEVA8", &Features::RCS::EVA8Pitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the EVA8.");
						ImGui::MainSliderFloat("Yaw##AdvancedEVA8", &Features::RCS::EVA8Yaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the EVA8.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedEVA8", &Features::RCS::EVA8PitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The EVA8.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedEVA8", &Features::RCS::EVA8YawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The EVA8.");
					}
				}

				if (Features::RCS::Kraber && WeaponID == WeaponIDs::KRABER) {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Kraber");
					if (Features::RCS::RCSMode == 0) {
						ImGui::MainSliderFloat("Pitch##AdvancedKraber", &Features::RCS::KraberPitch, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Pitch Power for the Kraber.");
						ImGui::MainSliderFloat("Yaw##AdvancedKraber", &Features::RCS::KraberYaw, 1, 50, "%.1f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Yaw Power for the Kraber.");
					}
					if (Features::RCS::RCSMode == 1 && !Features::Aimbot::AimbotMode == 1) {
						ImGui::MainSliderFloat("Pitch Reduction %##AdvancedKraber", &Features::RCS::KraberPitchReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Horizontal Recoil That Will Be Reduced For The Kraber.");
						ImGui::MainSliderFloat("Yaw Reduction %##AdvancedKraber", &Features::RCS::KraberYawReduction, 0, 100, "%.0f");
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							ImGui::SetTooltip("Percentage Of Yaw Recoil That Will Be Reduced For The Kraber.");
					}
				}

				else {
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.99, 0.99, 0.99, 1.00f), "Unknown");
				}

				ImGui::EndChildFrame();
			}
		}
	}

	void AdvancedTriggerbotTab(int WeaponID) {
		if (!Features::Triggerbot::Enabled) {
			ImGui::Text("Triggerbot Is Disabled!");
		}

		if (Features::Triggerbot::Enabled) {
			ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 136), true);
			{
				ImGui::Spacing();
				ImGui::Text("Advanced Triggerbot");
				ImGui::Checkbox("Enabled", &Features::Triggerbot::AdvancedTriggerbot);
				if (Features::Triggerbot::AdvancedTriggerbot) {
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
				}
				ImGui::EndChildFrame();
			}

			if (Features::Triggerbot::AdvancedTriggerbot) {
				ImGui::BeginChildFrame(2, ImVec2({ static_cast<float>(WindowWidth - 220), 96 }), true);
				{
					ImGui::Spacing();
					ImGui::Text("Current Held Weapon: ");

					if (Features::Triggerbot::P2020 && WeaponID == WeaponIDs::P2020) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "P2020");
						ImGui::MainSliderFloat("Range##P2020Triggerbot", &Features::Triggerbot::P2020Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::RE45 && WeaponID == WeaponIDs::RE45) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "RE45");
						ImGui::MainSliderFloat("Range##RE45Triggerbot", &Features::Triggerbot::RE45Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Alternator && WeaponID == WeaponIDs::ALTERNATOR) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Alternator");
						ImGui::MainSliderFloat("Range##AlternatorTriggerbot", &Features::Triggerbot::AlternatorRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::R99 && WeaponID == WeaponIDs::R99) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R99");
						ImGui::MainSliderFloat("Range##R99Triggerbot", &Features::Triggerbot::R99Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::R301 && WeaponID == WeaponIDs::R301) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R301");
						ImGui::MainSliderFloat("Range##R301Triggerbot", &Features::Triggerbot::R301Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Spitfire && WeaponID == WeaponIDs::SPITFIRE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Spitfire");
						ImGui::MainSliderFloat("Range##SpitfireTriggerbot", &Features::Triggerbot::SpitfireRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::G7 && WeaponID == WeaponIDs::G7) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "G7");
						ImGui::MainSliderFloat("Range##G7Triggerbot", &Features::Triggerbot::G7Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Flatline && WeaponID == WeaponIDs::FLATLINE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Flatline");
						ImGui::MainSliderFloat("Range##FlatlineTriggerbot", &Features::Triggerbot::FlatlineRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Prowler && WeaponID == WeaponIDs::PROWLER) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Prowler");
						ImGui::MainSliderFloat("Range##ProwlerTriggerbot", &Features::Triggerbot::ProwlerRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Hemlock && WeaponID == WeaponIDs::HEMLOCK) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Hemlock");
						ImGui::MainSliderFloat("Range##HemlockTriggerbot", &Features::Triggerbot::HemlockRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Repeater && WeaponID == WeaponIDs::REPEATER) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Repeater");
						ImGui::MainSliderFloat("Range##RepeaterTriggerbot", &Features::Triggerbot::RepeaterRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Rampage && WeaponID == WeaponIDs::RAMPAGE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Rampage");
						ImGui::MainSliderFloat("Range##RampageTriggerbot", &Features::Triggerbot::RampageRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::CARSMG && WeaponID == WeaponIDs::CAR) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "CARSMG");
						ImGui::MainSliderFloat("Range##CARSMGTriggerbot", &Features::Triggerbot::CARSMGRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Havoc && WeaponID == WeaponIDs::HAVOC) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Havoc");
						ImGui::MainSliderFloat("Range##HavocTriggerbot", &Features::Triggerbot::HavocRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Devotion && WeaponID == WeaponIDs::DEVOTION) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Devotion");
						ImGui::MainSliderFloat("Range##DevotionTriggerbot", &Features::Triggerbot::DevotionRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::LSTAR && WeaponID == WeaponIDs::LSTAR) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "LSTAR");
						ImGui::MainSliderFloat("Range##LSTARTriggerbot", &Features::Triggerbot::LSTARRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::TripleTake && WeaponID == WeaponIDs::TRIPLETAKE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "TripleTake");
						ImGui::MainSliderFloat("Range##TripleTakeTriggerbot", &Features::Triggerbot::TripleTakeRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Volt && WeaponID == WeaponIDs::VOLT) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Volt");
						ImGui::MainSliderFloat("Range##VoltTriggerbot", &Features::Triggerbot::VoltRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Nemesis && WeaponID == WeaponIDs::NEMESIS) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Nemesis");
						ImGui::MainSliderFloat("Range##NemesisTriggerbot", &Features::Triggerbot::NemesisRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Mozambique && WeaponID == WeaponIDs::MOZAMBIQUE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Mozambique");
						ImGui::MainSliderFloat("Range##MozambiqueTriggerbot", &Features::Triggerbot::MozambiqueRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Peacekeeper && WeaponID == WeaponIDs::PEACEKEEPER) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Peacekeeper");
						ImGui::MainSliderFloat("Range##PeacekeeperTriggerbot", &Features::Triggerbot::PeacekeeperRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Mastiff && WeaponID == WeaponIDs::MASTIFF) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Mastiff");
						ImGui::MainSliderFloat("Range##MastiffTriggerbot", &Features::Triggerbot::MastiffRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Longbow && WeaponID == WeaponIDs::LONGBOW) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Longbow");
						ImGui::MainSliderFloat("Range##LongbowTriggerbot", &Features::Triggerbot::LongbowRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::ChargeRifle && WeaponID == WeaponIDs::CHARGE_RIFLE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "ChargeRifle");
						ImGui::MainSliderFloat("Range##ChargeRifleTriggerbot", &Features::Triggerbot::ChargeRifleRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Sentinel && WeaponID == WeaponIDs::SENTINEL) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Sentinel");
						ImGui::MainSliderFloat("Range##SentinelTriggerbot", &Features::Triggerbot::SentinelRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Wingman && WeaponID == WeaponIDs::WINGMAN) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Wingman");
						ImGui::MainSliderFloat("Range##WingmanTriggerbot", &Features::Triggerbot::WingmanRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::EVA8 && WeaponID == WeaponIDs::EVA8) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "EVA8");
						ImGui::MainSliderFloat("Range##EVA8Triggerbot", &Features::Triggerbot::EVA8Range, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Bocek && WeaponID == WeaponIDs::BOCEK) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Bocek");
						ImGui::MainSliderFloat("Range##BocekTriggerbot", &Features::Triggerbot::BocekRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Kraber && WeaponID == WeaponIDs::KRABER) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Kraber");
						ImGui::MainSliderFloat("Range##KraberTriggerbot", &Features::Triggerbot::KraberRange, 0, 1000, "%.0f");
					}

					if (Features::Triggerbot::Knife && WeaponID == WeaponIDs::KNIFE) {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "ThrowingKnife");
						ImGui::MainSliderFloat("Range##ThrowingKnifeTriggerbot", &Features::Triggerbot::ThrowingKnifeRange, 0, 1000, "%.0f");
					}

					else {
						ImGui::SameLine();
						ImGui::TextColored(ImVec4(0.99, 0.99, 0.99, 1.00f), "Unknown (Check Your Selected Weapon!)");
					}

					ImGui::EndChildFrame();
				}
			}
		}
	}

	void TextCentered(std::string text) {
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}

	void RenderCombo(std::string title, std::vector<std::string>items, int& index, int comboWidth) {
		ImGui::PushItemWidth(comboWidth);
		if (ImGui::BeginCombo(title.c_str(), items.at(index).c_str(), 0)) {

			for (int n = 0; n < items.size(); n++) {
				const bool is_selected = (index == n);
				if (ImGui::Selectable(items.at(n).c_str(), is_selected))index = n;

				if (is_selected)ImGui::SetItemDefaultFocus();// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
};