#include <boost/log/trivial.hpp>

#include "glman_lib/renderer/renderer.h"
#include "glman_lib/interfaces/rib_rendering_interface.h"

RIB_Rendering_Interface::RIB_Rendering_Interface(){
	renderer = new Renderer();
	BOOST_LOG_TRIVIAL(info) << "RIB interface for image rendering initialized";
}

RIB_Rendering_Interface::~RIB_Rendering_Interface(){
	if (renderer){
		delete renderer;
	}

	BOOST_LOG_TRIVIAL(info) << "RIB interface for image rendering destroyed";
}

void RIB_Rendering_Interface::ri_WorldBegin() {

}


void RIB_Rendering_Interface::ri_WorldEnd() {

}


void RIB_Rendering_Interface::ri_Display(std::string output, std::string display, std::string channels) {
	//this->display = new Display("houdini");
}


void RIB_Rendering_Interface::ri_Format(unsigned int width, unsigned int height, float aspect) {
	
}


void RIB_Rendering_Interface::ri_Translate(double x, double y, double z) {

}