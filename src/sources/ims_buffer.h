#pragma once

#include <string>
#include <vector>
#include <memory>

#include "imgui_docking/imgui.h"

#include "sources/ims_object.h"

namespace ImStudio
{

  class BufferWindow
  {
    public:
      bool                    state                   = false;                //
      ImVec2                  size                    = {};                   //
      ImVec2                  pos                     = {};                   //
      int                     idvar                   = 0;                    //
      Object*                 current_child           = nullptr;              //
    
      bool                    staticlayout            = false;                //
    
      std::vector<std::unique_ptr<Object>>     objects                 = {};                   //
  
      void                    drawall                 (int *select);
      Object *                getobj                  (int id);
      BaseObject *            getbaseobj              (int id);
      void                    create                  (std::string type_);
  };

}