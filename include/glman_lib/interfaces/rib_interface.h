#ifndef __RIB_Interface_h__
#define __RIB_Interface_h__

#include <string>

#include "glman_lib/renderer/display.h"
#include "glman_lib/renderer/renderer.h"


class RIB_Interface {
	public:
		RIB_Interface();
		virtual ~RIB_Interface(){};
		
		virtual void ri_WorldBegin()=0;
		virtual void ri_WorldEnd()=0;

		virtual void ri_Display(std::string output, std::string display, std::string channels)=0;
		virtual void ri_Format(unsigned int width, unsigned int height, float aspect)=0;

		virtual void ri_Translate(double x, double y, double z)=0;
	private:
		//OP_Node *_node;
};


#endif