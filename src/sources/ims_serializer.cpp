#include "ims_serializer.h"
#include "ims_object.h"
#include "ims_buffer.h"
#include "ims_gui.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

int ImStudio::Serializer::SaveGUI(GUI& gui)
{
    bool                    state = true;                 // Alive
    bool                    compact = false;                // Compact/Spacious Switch
    bool                    wksp_create = true;                 // Workspace "Create"
    bool                    menubar = true;                 // Menubar State
    ImVec2                  mb_P = {};                   // Menubar Pos
    ImVec2                  mb_S = {};                   // Menubar Size
    bool                    sidebar = true;                 // Sidebar State
    ImVec2                  sb_P = {};                   // Sidebar Pos
    ImVec2                  sb_S = {};                   // Sidebar Size
    bool                    properties = true;                 // Properties State
    ImVec2                  pt_P = {};                   // Properties Pos
    ImVec2                  pt_S = {};                   // Properties Size
    int                     allvecsize = 0;                    //
    int                     selectid = 0;                    // Selected object (VP)
    int                     previd = 0;                    // Previous object
    BaseObject* selectobj = nullptr;              // Pointer to access
    int                     selectproparray = 0;                    // Selected from prop array
    bool                    viewport = true;                 // Viewport State
    ImVec2                  vp_P = {};                   // Viewport Pos
    ImVec2                  vp_S = {};                   // Viewport Size
    BufferWindow            bw;
    bool                    wksp_output_cpp = false;                // Workspace "Output"
    ImVec2                  ot_P = {};                   // Output Window Pos
    ImVec2                  ot_S = {};                   // Output Window Size
    std::string             output = {};
    bool                    wksp_output_lua = false;                // Workspace "Output"
    bool                    child_style = false;                // Show Style Editor
    bool                    child_demo = false;                // Show Demo Window
    bool                    child_metrics = false;                // Show Metrics Window
    bool                    child_color = false;                // Show Color Export
    bool                    child_stack = false;                // Show Stack Tool
    bool                    child_resources = false;                // Show Help Resources
    bool                    child_about = false;                // Show About Window
    std::string             filename;
    std::string             path;

	return 0;
}

int ImStudio::Serializer::SaveBuffer(ImStudio::BufferWindow& bw)
{
    bool                    state = false;                //
    ImVec2                  size = {};                   //
    ImVec2                  pos = {};                   //
    int                     idvar = 0;                    //
    Object* current_child = nullptr;              //
    bool                    staticlayout = false;                //
    std::vector<Object>     objects = {};                   //

	// Iterate children
	// SaveObject(child)

	return 0;
}

int ImStudio::Serializer::SaveObject(ImStudio::Object& obj)
{
    // BaseObject
    int                     id = 0;                    // Unique ID
    std::string             type = {};                   // Widget type
    std::string             identifier = {};                   // type+id
    bool                    state = true;                 // Alive
    ImVec2                  pos = ImVec2(100, 100);     //--
    ImVec2                  size = {};                   //  | Widget vectors
    float                   width = 200;                  //--
    bool                    init = false;                //--
    bool                    propinit = false;                //  | Initialised
    bool                    selectinit = true;                 //--
    bool                    locked = false;                //--
    bool                    center_h = false;                //  | Properties
    bool                    autoresize = true;                 //  |
    bool                    animate = true;                 //--
    std::string             label = "Label";              //--
    std::string             value_s = {};                   //  | Widget values/contents
    bool                    value_b = false;                //--
    Object* parent = nullptr;              //--
    //int                     parentid                = 0;                  //  | For child objects and
    bool                    ischild = false;                //  | child widgets
    bool                    ischildwidget = false;                //--
    int                     item_current = 0;                    //

    // ContainerChild
    int                     id = 0;                    // Unique ID
    ImRect                  freerect = {};                   // Buffer rect ctrld by grabs
    ImRect                  windowrect = {};                   // Window dimensions for highlighting
    bool                    open = true;                 //--
    bool                    locked = false;                //  | Properties
    bool                    border = true;                 //  |
    bool                    init = false;                //--
    int                     grab1_id = 0;                    //--
    int                     grab2_id = 0;                    //  | ugly
    ImVec2                  grab1 = ImVec2(90, 90);       //  | storage
    ImVec2                  grab2 = ImVec2(200, 200);     //  | stuff
    bool                    grabinit = false;                //--
    std::vector<BaseObject> objects = {};

	return 0;
}

int ImStudio::Serializer::SaveProject(GUI& gui)
{
	std::string path = gui.path + gui.filename;
	std::ofstream fp(path);

	// Add file error handling

	YAML::Emitter out;

	// SaveGUI()
	// SaveChildren()

	return 0;
}
