#ifndef __RIB_LOADER_H
#define __RIB_LOADER_H

#include <string>

namespace scene
{
    class Scene;
}

namespace rib
{
    class RIB_Loader
    {
    public:
        bool    load(const std::string &filename, scene::Scene &target);
    };
}

#endif
