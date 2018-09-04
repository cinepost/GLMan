#ifndef __RIB_RENDERING_INTERFACE_H__
#define __RIB_RENDERING_INTERFACE_H__

#include "glman_lib/interfaces/rib_interface.h"
#include "glman_lib/renderer/renderer.h"

class RIB_Rendering_Interface: public RIB_Interface {
	public:
		RIB_Rendering_Interface();
		~RIB_Rendering_Interface();

		void ri_WorldBegin();
		void ri_WorldEnd();

		void ri_Display(std::string output, std::string display, std::string channels);
		void ri_Format(unsigned int width, unsigned int height, float aspect);

		void ri_Translate(double x, double y, double z);
	private:
		Renderer *renderer=NULL;
		Display *display=NULL;
};


#endif