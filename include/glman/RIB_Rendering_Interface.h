#ifndef __RIB_Rendering_Interface_h__
#define __RIB_Rendering_Interface_h__

#include "glman/Display.h"
#include "glman/RIB_Interface.h"

class RIB_Rendering_Interface: public RIB_Interface {
	public:
		RIB_Rendering_Interface();

		void ri_WorldBegin();
		void ri_WorldEnd();

		void ri_Display(std::string output, std::string display, std::string channels);
		void ri_Format(unsigned int width, unsigned int height, float aspect);

		void ri_Translate(double x, double y, double z);
	private:
		Display *display=NULL;
};


#endif