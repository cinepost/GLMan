#include <boost/log/trivial.hpp>

#include "glman/RIB_Rendering_Interface.h"

RIB_Rendering_Interface::RIB_Rendering_Interface(){
	BOOST_LOG_TRIVIAL(info) << "RIB interface for image rendering initialized";
}


void RIB_Rendering_Interface::ri_WorldBegin() {

}


void RIB_Rendering_Interface::ri_WorldEnd() {

}


void RIB_Rendering_Interface::ri_Display(std::string output, std::string display, std::string channels) {

}


void RIB_Rendering_Interface::ri_Format(unsigned int width, unsigned int height, float aspect) {
	
}


void RIB_Rendering_Interface::ri_Translate(double x, double y, double z) {

}