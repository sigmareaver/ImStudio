#include "ims_serializer.h"
#include "ims_object.h"
#include "ims_buffer.h"
#include "ims_gui.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

#include "ImGuiFileDialog/ImGuiFileDialog.h"

namespace YAML {
    template<>
    struct convert<ImVec2> {
        static Node encode(const ImVec2& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }

        static bool decode(const Node& node, ImVec2& rhs) {
            if (!node.IsSequence() || node.size() != 2) {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<ImRect> {
        static Node encode(const ImRect& rhs) {
            Node node;
            node.push_back(rhs.Min);
            node.push_back(rhs.Max);
            return node;
        }

        static bool decode(const Node& node, ImRect& rhs) {
            if (!node.IsSequence() || node.size() != 2) {
                return false;
            }

            rhs.Min = node[0].as<ImVec2>();
            rhs.Max = node[1].as<ImVec2>();
            return true;
        }
    };
}

YAML::Emitter& operator<< (YAML::Emitter& out, const ImVec2& v)
{
    out << YAML::Flow << YAML::BeginSeq;
    out << v.x;
    out << v.y;
    out << YAML::EndSeq;

    return out;
}

YAML::Emitter& operator<< (YAML::Emitter& out, const ImRect& r)
{
    out << YAML::Flow << YAML::BeginSeq;
    out << r.Min;
    out << r.Max;
    out << YAML::EndSeq;

    return out;
}

int ImStudio::Serializer::SaveBaseObject(YAML::Emitter& out, ImStudio::BaseObject& obj)
{
    KEY(out, "ID", obj.id);
    KEY(out, "Type", obj.type);
    KEY(out, "Identifier", obj.identifier);
    KEY(out, "State", obj.state);
    KEY(out, "Pos", obj.pos);
    KEY(out, "Size", obj.size);
    KEY(out, "Width", obj.width);
    KEY(out, "Init", obj.init);
    KEY(out, "PropInit", obj.propinit);
    KEY(out, "Initial_Selection", obj.initial_selection);
    KEY(out, "Locked", obj.locked);
    KEY(out, "CenterH", obj.center_h);
    KEY(out, "AutoResize", obj.autoresize);
    KEY(out, "Animate", obj.animate);
    KEY(out, "Label", obj.label);
    KEY(out, "ValueS", obj.value_s);
    KEY(out, "ValueB", obj.value_b);

    //Object* parent = nullptr;              //--
    ////int                     parentid                = 0;                  //  | For child objects and
    //if (obj.parent) // Apparently parent doesn't get initialized, needs done before further coding...
    //    KEY(out, "ParentID", obj.parent->id);
    //else
    //    KEY(out, "ParentID", 0);

    //KEY(out, "IsChild", obj.ischild);
    KEY(out, "IsChildWidget", obj.ischildwidget);
    KEY(out, "ItemCurrent", obj.item_current);

    return 0;
}

int ImStudio::Serializer::SaveObject(YAML::Emitter& out, ImStudio::Object& obj)
{
    // BaseObject
    SaveBaseObject(out, obj);

    // ContainerChild
    BEGIN_MAP(out, "ContainerChild");
    auto& child = obj.child;
    KEY(out, "ID", child.id);
    KEY(out, "FreeRect", child.freerect);
    KEY(out, "WindowRect", child.windowrect);
    KEY(out, "Open", child.open);
    KEY(out, "Locked", child.locked);
    KEY(out, "Border", child.border);
    KEY(out, "Init", child.init);
    KEY(out, "Grab1ID", child.grab1_id);
    KEY(out, "Grab2ID", child.grab2_id);
    KEY(out, "Grab1", child.grab1);
    KEY(out, "Grab2", child.grab2);
    KEY(out, "GrabInit", child.grabinit);

    BEGIN_BSEQ(out, "Objects");
    for (auto& cw : child.objects)
    {
        SaveBaseObject(out, cw);
    }
    END_SEQ(out);

    END_MAP(out);

    return 0;
}

int ImStudio::Serializer::SaveBuffer(YAML::Emitter& out, ImStudio::BufferWindow& bw)
{
    KEY(out, "State", bw.state);
    KEY(out, "Pos", bw.pos);
    KEY(out, "Size", bw.size);
    KEY(out, "IDGen", bw.idgen);

    //Object* current_child = nullptr;              //

    KEY(out, "StaticLayout", bw.staticlayout);

    BEGIN_BSEQ(out, "Objects");
    for (auto& o : bw.objects)
    {
        out << YAML::BeginMap;
        SaveObject(out, o);
        out << YAML::EndMap;
    }
    END_SEQ(out);

	return 0;
}

int ImStudio::Serializer::SaveGUI(YAML::Emitter& out, GUI& gui)
{
    KEY(out, "State", gui.state);
    KEY(out, "Compact", gui.compact);
    KEY(out, "WkspCreate", gui.wksp_create);
    KEY(out, "Menubar", gui.menubar);
    KEY(out, "MenubarPos", gui.mb_P);
    KEY(out, "MenubarSize", gui.mb_S);
    KEY(out, "Sidebar", gui.sidebar);
    KEY(out, "SidebarPos", gui.sb_P);
    KEY(out, "SidebarSize", gui.sb_S);
    KEY(out, "Properties", gui.properties);
    KEY(out, "PropertiesPos", gui.pt_P);
    KEY(out, "PropertiesSize", gui.pt_S);

    KEY(out, "Viewport", gui.viewport);
    KEY(out, "ViewportPos", gui.vp_P);
    KEY(out, "ViewportSize", gui.vp_S);

    BEGIN_MAP(out, "BufferWindow");
    SaveBuffer(out, gui.bw);
    END_MAP(out);

    KEY(out, "WkspOutputCPP", gui.wksp_output_cpp);
    KEY(out, "OutputPos", gui.ot_P);
    KEY(out, "OutputSize", gui.ot_S);

    //std::string             output = {};

    KEY(out, "WkspOutputLua", gui.wksp_output_lua);
    KEY(out, "ChildStyle", gui.child_style);
    KEY(out, "ChildDemo", gui.child_demo);
    KEY(out, "ChildMetrics", gui.child_metrics);
    KEY(out, "ChildColor", gui.child_color);
    KEY(out, "ChildStack", gui.child_stack);
    KEY(out, "ChildResources", gui.child_resources);
    KEY(out, "ChildAbout", gui.child_about);

    //std::string             filename;
    //std::string             path;

    return 0;
}

int ImStudio::Serializer::SaveProjectAs(GUI& gui)
{
    ImGuiFileDialog::Instance()->OpenDialog("SaveAsDlg", "Save As", ".gui", ".", 1, nullptr, ImGuiFileDialogFlags_ConfirmOverwrite);
    return 0;
}

int ImStudio::Serializer::SaveProject(GUI& gui)
{
    if (gui.filename.length() == 0)
    {
        SaveProjectAs(gui);
        return -1;
    }
    std::string path = gui.path + "\\" + gui.filename;
    std::ofstream fp(path);

	// Add file error handling
    if (!fp.good())
    {
        return -1;
    }

	YAML::Emitter out;

	// SaveGUI()
    out << YAML::BeginMap;
    SaveGUI(out, gui);
    out << YAML::EndMap;

    fp << out.c_str();

	return 0;
}

static void ClearProject(ImStudio::GUI& gui)
{
    gui.bw.state = true;
    gui.bw.size = {};
    gui.bw.pos = {};
    gui.bw.idgen = 0;
    gui.bw.open_child = false;
    gui.bw.open_child_id = -1;
    gui.bw.selected_obj_id = -1;
    gui.bw.staticlayout = false;
    gui.bw.objects.clear();
}

int ImStudio::Serializer::LoadProjectDlg()
{
    ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlg", "Load File", ".gui", ".");
    return 0;
}

int ImStudio::Serializer::LoadBaseObject(YAML::detail::iterator_value& it, Object& obj)
{
    obj.id = it["ID"].as<int>();
    obj.type = it["Type"].as<std::string>();
    obj.identifier = it["Identifier"].as<std::string>();
    obj.state = it["State"].as<bool>();
    obj.pos = it["Pos"].as<ImVec2>();
    obj.size = it["Size"].as<ImVec2>();
    obj.width = it["Width"].as<float>();
    obj.init = it["Init"].as<bool>();
    obj.propinit = it["PropInit"].as<bool>();
    obj.initial_selection = it["Initial_Selection"].as<bool>();
    obj.locked = it["Locked"].as<bool>();
    obj.center_h = it["CenterH"].as<bool>();
    obj.autoresize = it["AutoResize"].as<bool>();
    obj.animate = it["Animate"].as<bool>();
    obj.label = it["Label"].as<std::string>();
    obj.value_s = it["ValueS"].as<std::string>();
    obj.value_b = it["ValueB"].as<bool>();

    //Object* parent = nullptr;              //--
    ////int                     parentid                = 0;                  //  | For child objects and
    //if (obj.parent) // Apparently parent doesn't get initialized, needs done before further coding...
    //    KEY(out, "ParentID", obj.parent->id);
    //else
    //    KEY(out, "ParentID", 0);

    //KEY(out, "IsChild", obj.ischild);
    obj.ischildwidget = it["IsChildWidget"].as<bool>();
    obj.item_current = it["ItemCurrent"].as<int>();

    return 0;
}

int ImStudio::Serializer::LoadObject(YAML::detail::iterator_value& it, Object& obj)
{
    // BaseObject
    LoadBaseObject(it, obj);

    // ContainerChild
    auto cc_node = it["ContainerChild"];
    auto& child = obj.child;
    child.id = cc_node["ID"].as<int>();
    child.freerect = cc_node["FreeRect"].as<ImRect>();
    child.windowrect = cc_node["WindowRect"].as<ImRect>();
    child.open = cc_node["Open"].as<bool>();
    child.locked = cc_node["Locked"].as<bool>();
    child.border = cc_node["Border"].as<bool>();
    child.init = cc_node["Init"].as<bool>();
    child.grab1_id = cc_node["Grab1ID"].as<int>();
    child.grab2_id = cc_node["Grab2ID"].as<int>();
    child.grab1 = cc_node["Grab1"].as<ImVec2>();
    child.grab2 = cc_node["Grab2"].as<ImVec2>();
    child.grabinit = cc_node["GrabInit"].as<bool>();

    auto objects_node = cc_node["Objects"];
    for (auto it : objects_node)
    {
        int id = it["ID"].as<int>();
        std::string type = it["Type"].as<std::string>();
        Object widget(id, type);
        LoadBaseObject(it, widget);
        child.objects.push_back(widget);
    }

    return 0;
}

int ImStudio::Serializer::LoadBuffer(YAML::Node& node, ImStudio::BufferWindow& bw)
{
    bw.state = node["State"].as<bool>();
    bw.pos = node["Pos"].as<ImVec2>();
    bw.size = node["Size"].as<ImVec2>();
    bw.idgen = node["IDGen"].as<int>();

    //Object* current_child = nullptr;              //

    bw.staticlayout = node["StaticLayout"].as<bool>();

    auto objects_node = node["Objects"];
    for (auto it : objects_node)
    {
        int id = it["ID"].as<int>();
        std::string type = it["Type"].as<std::string>();
        Object widget(id, type);
        LoadObject(it, widget);
        bw.objects.push_back(widget);
    }

    return 0;
}

int ImStudio::Serializer::LoadGUI(YAML::Node& node, GUI& gui)
{
    gui.state = node["State"].as<bool>();
    gui.compact = node["Compact"].as<bool>();
    gui.wksp_create = node["WkspCreate"].as<bool>();
    gui.menubar = node["Menubar"].as<bool>();
    gui.mb_P = node["MenubarPos"].as<ImVec2>();
    gui.mb_S = node["MenubarSize"].as<ImVec2>();
    gui.sidebar = node["Sidebar"].as<bool>();
    gui.sb_P = node["SidebarPos"].as<ImVec2>();
    gui.sb_S = node["SidebarSize"].as<ImVec2>();
    gui.properties = node["Properties"].as<bool>();
    gui.pt_P = node["PropertiesPos"].as<ImVec2>();
    gui.pt_S = node["PropertiesSize"].as<ImVec2>();

    gui.viewport = node["Viewport"].as<bool>();
    gui.vp_P = node["ViewportPos"].as<ImVec2>();
    gui.vp_S = node["ViewportSize"].as<ImVec2>();

    {
        auto bw_node = node["BufferWindow"];
        LoadBuffer(bw_node, gui.bw);
    }

    gui.wksp_output_cpp = node["WkspOutputCPP"].as<bool>();
    gui.ot_P = node["OutputPos"].as<ImVec2>();
    gui.ot_S = node["OutputSize"].as<ImVec2>();

    //std::string             output = {};

    gui.wksp_output_lua = node["WkspOutputLua"].as<bool>();
    gui.child_style = node["ChildStyle"].as<bool>();
    gui.child_demo = node["ChildDemo"].as<bool>();
    gui.child_metrics = node["ChildMetrics"].as<bool>();
    gui.child_color = node["ChildColor"].as<bool>();
    gui.child_stack = node["ChildStack"].as<bool>();
    gui.child_resources = node["ChildResources"].as<bool>();
    gui.child_about = node["ChildAbout"].as<bool>();

    return 0;
}

int ImStudio::Serializer::LoadProject(GUI& gui)
{
    if (gui.filename.length() == 0)
    {
        LoadProjectDlg();
        return -1;
    }


    try
    {
        std::string path = gui.path + "\\" + gui.filename;
        YAML::Node node = YAML::LoadFile(path);

        ClearProject(gui);

        LoadGUI(node, gui);
    }
    catch (const std::exception& e)
    {
        printf("%s\n", e.what());
    }

    return 0;
}
