#include "soh/UIWidgets.hpp"
#include "soh/OTRGlobals.h"
#include "plando.h"

void PlandoMakerWindow::DrawElement() {
    ImGui::SetNextWindowSize(ImVec2(920, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Randomizer Editor", &mIsVisible, ImGuiWindowFlags_NoFocusOnAppearing)) {
        ImGui::End();
        return;
    }

    bool disableEditingRandoSettings = CVarGetInteger("gRandoGenerating", 0) || CVarGetInteger("gOnFileSelectNameEntry", 0);
    if (disableEditingRandoSettings) {
        UIWidgets::DisableComponent(ImGui::GetStyle().Alpha * 0.5f);
    }
}

void PlandoMakerWindow::InitElement() {

}