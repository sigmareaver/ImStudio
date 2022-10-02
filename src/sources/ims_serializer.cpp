#include "ims_serializer.h"
#include "ims_object.h"
#include "ims_buffer.h"
#include "ims_gui.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

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
    KEY(out, "SelectInit", obj.selectinit);
    KEY(out, "Locked", obj.locked);
    KEY(out, "CenterH", obj.center_h);
    KEY(out, "AutoResize", obj.autoresize);
    KEY(out, "Animate", obj.animate);
    KEY(out, "Label", obj.label);
    KEY(out, "ValueS", obj.value_s);
    KEY(out, "ValueB", obj.value_b);

    Object* parent = nullptr;              //--
    //int                     parentid                = 0;                  //  | For child objects and
    if (obj.parent) // Apparently parent doesn't get initialized, needs done before further coding...
        KEY(out, "ParentID", obj.parent->id);
    else
        KEY(out, "ParentID", 0);

    KEY(out, "IsChild", obj.ischild);
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
    bool                    grabinit = false;                //--
    KEY(out, "GrabInit", child.grabinit);

    std::vector<BaseObject> objects = {};
    BEGIN_BSEQ(out, "Objects");
    for (auto& cptr : child.objects)
    {
        auto& cw = *cptr;
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
    KEY(out, "IDVar", bw.idvar);

    Object* current_child = nullptr;              //

    KEY(out, "StaticLayout", bw.staticlayout);

    BEGIN_BSEQ(out, "Objects");
    for (auto& ptr : bw.objects)
    {
        auto& o = *ptr;
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
    KEY(out, "AllVecSize", gui.allvecsize);

    int                     selectid = 0;                    // Selected object (VP)
    KEY(out, "SelectID", gui.selectid);
    int                     previd = 0;                    // Previous object
    KEY(out, "PrevID", gui.previd);
    BaseObject* selectobj = nullptr;              // Pointer to access

    KEY(out, "SelectPropArray", gui.selectproparray);
    KEY(out, "Viewport", gui.viewport);
    KEY(out, "ViewportPos", gui.vp_P);
    KEY(out, "ViewportSize", gui.vp_S);

    BEGIN_MAP(out, "BufferWindow");
    SaveBuffer(out, gui.bw);
    END_MAP(out);

    KEY(out, "WkspOutputCPP", gui.wksp_output_cpp);
    KEY(out, "OutputPos", gui.ot_P);
    KEY(out, "OutputSize", gui.ot_S);

    std::string             output = {};

    KEY(out, "WkspOutputLua", gui.wksp_output_lua);
    KEY(out, "ChildStyle", gui.child_style);
    KEY(out, "ChildDemo", gui.child_demo);
    KEY(out, "ChildMetrics", gui.child_metrics);
    KEY(out, "ChildColor", gui.child_color);
    KEY(out, "ChildStack", gui.child_stack);
    KEY(out, "ChildResources", gui.child_resources);
    KEY(out, "ChildAbout", gui.child_about);

    std::string             filename;
    std::string             path;

    return 0;
}

int ImStudio::Serializer::SaveProject(GUI& gui)
{
	//std::string path = gui.path + gui.filename;
    std::string path = "test.gui"; // Test save
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
