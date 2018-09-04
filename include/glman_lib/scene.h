#ifndef TUTORIAL_SCENE_SCENE_H
#define TUTORIAL_SCENE_SCENE_H

#include <string>

#include <boost/ref.hpp>

using namespace std;

namespace scene
{
    class Scene
    {
    public:
        Scene();

        boost::reference_wrapper<int const> getColorSize() const { return boost::cref(m_ColorSize); }

        void setDisplay(string data);

    private:
        int m_ColorSize;
    };
}

#endif
