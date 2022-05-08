#pragma once

#include <string>

#include "imgui_docking/imgui.h"
#include "fmt/format.h"

#include "ims_object.h"
#include "ims_buffer.h"

namespace ImStudio
{

    void RecreateLua(BaseObject obj, std::string* output, bool staticlayout);
    void GenerateCodeLua(std::string* output, BufferWindow* bw);

}