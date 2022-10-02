#include "ims_generator_lua.h"

void ImStudio::RecreateLua(BaseObject obj, std::string* output, bool staticlayout)
{
    std::string bfs;

    if (obj.type == "button")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.Button(\"{}\", {}, {}) ", obj.value_s, obj.size.x, obj.size.y);
        bfs += "-- remove size argument (ImVec2) to auto-resize\n\n";

    }

    if (obj.type == "radio")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tr1{} = false\n", obj.id);
        bfs += fmt::format("\tr1{}_pressed = false\n", obj.id);
        bfs += fmt::format("\tr1{}, r1{}_pressed = ImGui.RadioButton(\"{}\", r1{})\n\n", obj.id, obj.id, obj.label, obj.id);
    }

    if (obj.type == "checkbox")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tc1{} = false\n", obj.id);
        bfs += fmt::format("\tc1{}_pressed = false\n", obj.id);
        bfs += fmt::format("\tc1{}, c1{}_pressed = ImGui.Checkbox(\"{}\", c1{})\n\n", obj.id, obj.id, obj.label, obj.id);
    }

    if (obj.type == "text")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.Text(\"{}\");\n\n", obj.value_s);
    }

    if (obj.type == "bullet")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += "\tImGui.Bullet()\n\n";

    }

    if (obj.type == "arrow")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += "\tImGui.ArrowButton(\"##left\", ImGuiDir.Left)\n";
        bfs += "\tImGui.SameLine()\n";
        bfs += "\tImGui.ArrowButton(\"##right\", ImGuiDir.Right)\n\n";
    }

    if (obj.type == "combo")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        bfs += fmt::format("\tcombo1{}_updated = false\n", obj.id);
        bfs += fmt::format("\titem_current{} = 0\n", obj.id);
        bfs += fmt::format("\titems{} = {{\"Never\", \"Gonna\", \"Give\", \"You\", \"Up\"}}\n", obj.id);
        bfs += fmt::format("\titem_current{}, combo1{}_updated = ImGui.Combo(\"{0}\", item_current{1}, items{1}, #(items{1}))\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "listbox")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        bfs += fmt::format("\tlist1{}_updated = false\n", obj.id);
        bfs += fmt::format("\titem_current{} = 0\n", obj.id);
        bfs += fmt::format("\titems{} = {{\"Never\", \"Gonna\", \"Give\", \"You\", \"Up\"}}\n", obj.id);
        bfs += fmt::format("\titem_current{}, list1{}_updated = ImGui.ListBox(\"{0}\", item_current{1}, items{1}, #(items{1}))\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "textinput")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({}) ", obj.width);
        bfs += "-- NOTE: (Push/Pop)ItemWidth is optional\n";
        //static char str0[128] = "Hello, world!";
        //ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
        bfs += fmt::format("\tinput1{}_updated = false\n");
        bfs += fmt::format("\tstr{} = \"{}\"\n", obj.id, obj.value_s);
        bfs += fmt::format("\tstr{}, input1{}_updated = ImGui.InputText(\"{0}\", str{1}, 128);\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "inputint")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static int i0 = 123;
        //ImGui::InputInt("input int", &i0);
        bfs += fmt::format("\ti{}_updated = false\n", obj.id);
        bfs += fmt::format("\ti{} = 123\n", obj.id);
        bfs += fmt::format("\ti{}, i{}_updated = ImGui.InputInt(\"{}\", i{})\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "inputfloat")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f0 = 0.001f;
        //ImGui::InputFloat("input float", &f0, 0.01f, 1.0f, "%.3f");
        bfs += fmt::format("\tf{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf{} = 0.001\n", obj.id);
        bfs += fmt::format("\tf{}, f{}_updated = ImGui.InputFloat(\"{}\", f{}, 0.01, 1.0, \"%.3f\")\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "inputdouble")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static double d0 = 999999.00000001;
        //ImGui::InputDouble("input double", &d0, 0.01f, 1.0f, "%.8f");
        bfs += fmt::format("\td{}_updated = false\n", obj.id);
        bfs += fmt::format("\td{} = 999999.00000001\n", obj.id);
        bfs += fmt::format("\td{}, d{}_updated = ImGui.InputDouble(\"{}\", d{}, 0.01, 1.0, \"%.8lf\")\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "inputscientific")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f1 = 1.e10f;
        //ImGui::InputFloat("input scientific", &f1, 0.0f, 0.0f, "%e");
        bfs += fmt::format("\tf{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf{} = 1.e10\n", obj.id);
        bfs += fmt::format("\tf{}, f{}_updated = ImGui.InputFloat(\"{}\", f{}, 0.0, 0.0, \"%e\")\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "inputfloat3")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
        //ImGui::InputFloat3("input float3", vec4a);
        bfs += fmt::format("\tvec3{}_updated = false\n", obj.id);
        bfs += fmt::format("\tvec3{} = {{0.10, 0.20, 0.30}}\n", obj.id);
        bfs += fmt::format("\tvec3{}, vec3{}_updated = ImGui::InputFloat3(\"{}\", vec3{})\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "dragint")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static int i1 = 50;
        //ImGui::DragInt("drag int", &i1, 1);
        bfs += fmt::format("\ti1{}_updated = false\n", obj.id);
        bfs += fmt::format("\ti1{0} = 50\n", obj.id);
        bfs += fmt::format("\ti1{}, i1{}_updated = ImGui.DragInt(\"{}\", i1{}, 1)\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "dragint100")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static int i2 = 42;
        //ImGui::DragInt("drag int 0..100", &i2, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);
        bfs += fmt::format("\ti2{}_updated = false\n", obj.id);
        bfs += fmt::format("\ti2{0} = 42;\n", obj.id);
        bfs += fmt::format("\ti2{}, i2{}_updated = ImGui.DragInt(\"{}\", i2{}, 1, 0, 100, \"%d%%\", ImGuiSliderFlags.AlwaysClamp)\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "dragfloat")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f1 = 1.00f;
        //ImGui::DragFloat("drag float", &f1, 0.005f);
        bfs += fmt::format("\tf1{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf1{0} = 1.00\n", obj.id);
        bfs += fmt::format("\tf1{}, f1{}_updated = ImGui.DragFloat(\"{}\", f1{}, 0.005)\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "dragfloatsmall")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f2 = 0.0067f;
        //ImGui::DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
        bfs += fmt::format("\tf2{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf2{0} = 0.0067\n", obj.id);
        bfs += fmt::format("\tf2{}, f2{}_updated = ImGui.DragFloat(\"{}\", f2{}, 0.0001, 0.0, 0.0, \"%.06f ns\")\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "sliderint")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static int i1 = 0;
        //ImGui::SliderInt("slider int", &i1, -1, 3);
        bfs += fmt::format("\ti1{}_updated = false\n", obj.id);
        bfs += fmt::format("\ti1{0} = 0\n", obj.id);
        bfs += fmt::format("\ti1{}, i1{}_updated = ImGui.SliderInt(\"{}\", i1{}, -1, 3)\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "sliderfloat")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f1 = 0.123f;
        //ImGui::SliderFloat("slider float", &f1, 0.0f, 1.0f, "ratio = %.3f");
        bfs += fmt::format("\tf1{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf1{0} = 0.123\n", obj.id);
        bfs += fmt::format("\tf1{}, f1{}_updated = ImGui.SliderFloat(\"{}\", f1{}, 0.0, 1.0, \"ratio = %.3f\")\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "sliderfloatlog")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float f2 = 0.0f;
        //ImGui::SliderFloat("slider float (log)", &f2, -10.0f, 10.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
        bfs += fmt::format("\tf2{}_updated = false\n", obj.id);
        bfs += fmt::format("\tf2{0} = 0.0\n", obj.id);
        bfs += fmt::format("\tf2{}, f2{}_updated = ImGui.SliderFloat(\"{}\", f2{}, -10.0, 10.0, \"%.4f\", ImGuiSliderFlags.Logarithmic)\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "sliderangle")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float angle = 0.0f;
        //ImGui::SliderAngle("slider angle", &angle);
        bfs += fmt::format("\tangle{}_updated = false\n", obj.id);
        bfs += fmt::format("\tangle{0} = 0.0\n", obj.id);
        bfs += fmt::format("\tangle{}, angle{}_updated = ImGui.SliderAngle(\"{}\", angle{})\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "color1")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        //static float col1[3] = {1.0f, 0.0f, 0.2f};
        //ImGui::ColorEdit3(label.c_str(), col1, ImGuiColorEditFlags_NoInputs);
        bfs += fmt::format("\tcol1{}_updated = false\n", obj.id);
        bfs += fmt::format("\tcol1{0} = {{1.0, 0.0, 0.2}}\n", obj.id);
        bfs += fmt::format("\tcol1{}, col1{}_updated = ImGui.ColorEdit3(\"{}\", col1{}, ImGuiColorEditFlags.NoInputs)\n\n", obj.id, obj.id, obj.label, obj.id);
    }

    if (obj.type == "color2")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float col2[3] = {1.0f, 0.0f, 0.2f};
        //ImGui::ColorEdit3(label.c_str(), col2);
        bfs += fmt::format("\tcol2{}_updated = false\n", obj.id);
        bfs += fmt::format("\tcol2{0} = {{1.0, 0.0, 0.2}}\n", obj.id);
        bfs += fmt::format("\tcol2{}, col2{}_updated = ImGui.ColorEdit3(\"{}\", col2{})\n\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "color3")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float col3[4] = {0.4f, 0.7f, 0.0f, 0.5f};
        //ImGui::ColorEdit4(label.c_str(), col3);
        bfs += fmt::format("\tcol4{}_updated = false\n", obj.id);
        bfs += fmt::format("\tcol4{0} = {{0.4, 0.7, 0.0, 0.5}}\n", obj.id);
        bfs += fmt::format("\tcol4{}, col4{}_updated = ImGui.ColorEdit4(\"{}\", col4{})\n\n", obj.id, obj.id, obj.label, obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    if (obj.type == "sameline")
    {
        if (staticlayout) {
            bfs += "\tImGui.SameLine()\n\n";
        }
    }

    if (obj.type == "newline")
    {
        if (staticlayout) {
            bfs += "\tImGui.NewLine()\n\n";
        }
    }

    if (obj.type == "separator")
    {
        if (staticlayout) {
            bfs += "\tImGui.Separator()\n\n";
        }
    }

    if (obj.type == "progressbar")
    {
        if (!staticlayout) {
            bfs += fmt::format("\tImGui.SetCursorPos({}, {})\n", obj.pos.x, obj.pos.y);
        }
        bfs += fmt::format("\tImGui.PushItemWidth({})\n", obj.width);
        //static float progress = 0.0f;
        //ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        bfs += fmt::format("\tprogress{} = 0.0\n", obj.id);
        bfs += fmt::format("\tImGui.ProgressBar(progress{}, 0.0, 0.0)\n", obj.id);
        bfs += "\tImGui.PopItemWidth()\n\n";
    }

    output->append(bfs);

}

void ImStudio::GenerateCodeLua(std::string* output, BufferWindow* bw)
{
#ifdef __EMSCRIPTEN__
    * output = "--[[ \nGENERATED CODE | READ-ONLY\nCopy by clicking the above button\n]]\n\n";
#else
    * output = "--[[\nGENERATED CODE | READ-ONLY\nYou can directly copy from here, or from File > Export to clipboard\n]]\n\n";
#endif
    * output += "window = true\n";
    *output += fmt::format("ImGui.SetNextWindowSize({}, {})\n", bw->size.x, bw->size.y);
    *output += "-- !! You might want to use these ^^ values in the OS window instead, and add the ImGuiWindowFlags_NoTitleBar flag in the ImGui window !!\n\n";
    *output += "if (window = ImGui.Begin(\"window_name\", window)) then\n\n";
    for (auto i = bw->objects.begin(); i != bw->objects.end(); ++i)
    {
        Object& o = **i;

        if (o.type != "child")
        {
            RecreateLua(o, output, bw->staticlayout);
        }
        else
        {
            if (!bw->staticlayout) {
                *output += fmt::format("\tImGui.SetCursorPos({}, {})\n", o.child.freerect.Min.x, o.child.freerect.Min.y);
            }
            *output += fmt::format("\tImGui.BeginChild({}, {}, {}, {})\n\n", o.child.id, o.child.freerect.GetSize().x, o.child.freerect.GetSize().y, o.child.border);
            for (auto i = o.child.objects.begin(); i != o.child.objects.end(); ++i)
            {
                BaseObject& cw = **i;// child widget

                RecreateLua(cw, output, bw->staticlayout);

            }
            *output += "\tImGui.EndChild()\n\n";
        }
    }
    *output += "\nend\nImGui.End()\n";
    *output += "\n--[[\nReminder: some widgets may have the same label \"##\" (if you didn't change it), and can lead to undesired ID collisions.\nMore info: https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-about-the-id-stack-system\n]]\n";
    ImGui::InputTextMultiline("##source", output,
        ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 64), ImGuiInputTextFlags_ReadOnly);

}