#pragma once

#include <string>

#include "imgui_docking/imgui.h"
#include "imgui_docking/imgui_internal.h"

#ifdef __EMSCRIPTEN__
#include "HyperlinkHelper.h"
#endif

namespace utils
{

    ImVec2         GetLocalCursor                 ();
    void           TextCentered                   (std::string text, int type);
    float          RandomFloat                    (float a, float b);
    ImVec4         RainbowCol                     ();
    void           DrawGrid                       ();
    void           ShowStyleEditorWindow          (bool *child_sty);
    void           ShowColorExportWindow          (bool *child_colexp);
    void           ShowResourcesWindow            (bool *child_resources);
    void           ShowAboutWindow                (bool *child_about);
    bool           IsItemActiveAlt                (ImVec2 pos, int id);
    bool           GrabButton                     (ImVec2 pos, int random_int);
    void           HelpMarker                     (const char *desc);
    float          CenterHorizontal               ();

}