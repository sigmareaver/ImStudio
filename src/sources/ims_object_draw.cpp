#include "ims_object.h"

void ImStudio::BaseObject::draw(int* select, bool staticlayout = false)
{
    if (state)
    {
        if (type == "button")
        {
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            if (autoresize) // auto resize
            {
                ImGui::Button(value_s.c_str());
                size = ImGui::GetItemRectSize();
            }
            else // manual
            {
                ImGui::Button(value_s.c_str(), size);
            }

            if (size.x < ImGui::CalcTextSize(value_s.c_str()).x)
                size.x = ImGui::CalcTextSize(value_s.c_str()).x;

            ImGui::PopID();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "checkbox")
        {
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::Checkbox(label.c_str(), &value_b);

            ImGui::PopID();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "radio")
        {
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::RadioButton(label.c_str(), value_b);

            ImGui::PopID();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "text")
        {

            ImGui::PushID(id);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::TextUnformatted(value_s.c_str());
            if (!staticlayout)
            {
                ImVec2 textsize = ImGui::CalcTextSize(value_s.c_str());
                if (textsize.x <= 0)
                {
                    textsize.x = 1;
                }
                ImGui::SetCursorPos(pos);
                ImGui::InvisibleButton("", textsize);
            }

            ImGui::PopID();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "textinput")
        {
            ImGui::PushID(id);
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::InputText(label.c_str(), &value_s);

            ImGui::PopItemWidth();
            ImGui::PopID();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "arrow")
        {
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::ArrowButton("##left", ImGuiDir_Left);
            ImGui::SameLine();
            ImGui::ArrowButton("##right", ImGuiDir_Right);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "combo")
        {
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            const char* items[] = { "Never", "Gonna", "Give", "You", "Up" };
            ImGui::Combo(label.c_str(), &item_current, items, IM_ARRAYSIZE(items));

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "listbox")
        {
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            const char* items[] = { "Never", "Gonna", "Give", "You", "Up" };
            ImGui::ListBox(label.c_str(), &item_current, items, IM_ARRAYSIZE(items));

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "inputint")
        {
            static int i0 = 123;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::InputInt(label.c_str(), &i0);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "inputfloat")
        {
            static float f0 = 0.001f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::InputFloat(label.c_str(), &f0, 0.01f, 1.0f, "%.3f");

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "inputdouble")
        {
            static double d0 = 999999.00000001;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::InputDouble(label.c_str(), &d0, 0.01f, 1.0f, "%.8f");

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "inputscientific")
        {
            static float f1 = 1.e10f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::InputFloat(label.c_str(), &f1, 0.0f, 0.0f, "%e");

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "inputfloat3")
        {
            static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::InputFloat3(label.c_str(), vec4a);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "dragint")
        {
            static int i1 = 50;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::DragInt(label.c_str(), &i1, 1);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "dragint100")
        {
            static int i2 = 42;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::DragInt(label.c_str(), &i2, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "dragfloat")
        {
            static float f1 = 1.00f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::DragFloat(label.c_str(), &f1, 0.005f);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "dragfloatsmall")
        {
            static float f2 = 0.0067f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::DragFloat(label.c_str(), &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "sliderint")
        {
            static int i1 = 0;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::SliderInt(label.c_str(), &i1, -1, 3);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "sliderfloat")
        {
            static float f1 = 0.123f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::SliderFloat(label.c_str(), &f1, 0.0f, 1.0f, "ratio = %.3f");

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "sliderfloatlog")
        {
            static float f2 = 0.0f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::SliderFloat(label.c_str(), &f2, -10.0f, 10.0f, "%.4f", ImGuiSliderFlags_Logarithmic);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "sliderangle")
        {
            static float angle = 0.0f;
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::SliderAngle(label.c_str(), &angle);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "color1")
        {
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::ColorEdit3(label.c_str(), col1, ImGuiColorEditFlags_NoInputs);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "color2")
        {
            static float col2[3] = { 1.0f, 0.0f, 0.2f };
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::ColorEdit3(label.c_str(), col2);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "color3")
        {
            static float col3[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::ColorEdit4(label.c_str(), col3);

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (ImGui::IsItemActive()))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
        if (type == "bullet")
        {
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::Bullet();

            ImGui::PopID();
            if ((!locked) && ((ImGui::IsItemActive()) && (ImGui::IsMouseDown(0))))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            highlight(select);
        }
        if (type == "sameline")
        {
            if (staticlayout)
                ImGui::SameLine();
        }
        if (type == "newline")
        {
            if (staticlayout)
                ImGui::NewLine();
        }
        if (type == "separator")
        {
            if (staticlayout)
                ImGui::Separator();
        }
        if (type == "progressbar")
        {
            static float progress = 0.0f, progress_dir = 1.0f;
            if (animate)
            {
                progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                if (progress >= +1.1f)
                {
                    progress = +1.1f;
                    progress_dir *= -1.0f;
                }
                if (progress <= -0.1f)
                {
                    progress = -0.1f;
                    progress_dir *= -1.0f;
                }
            }
            ImGui::PushItemWidth(width);
            if (!staticlayout)
                ImGui::SetCursorPos(pos);
            ImGui::PushID(id);

            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));

            ImGui::PopID();
            ImGui::PopItemWidth();
            if ((!locked) && (utils::IsItemActiveAlt(pos, id)))
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                pos = utils::GetLocalCursor();
                *select = id;
            }
            if ((!staticlayout) && (center_h))
            {
                pos.x = utils::CenterHorizontal();
            }
            highlight(select);
        }
    }
}
