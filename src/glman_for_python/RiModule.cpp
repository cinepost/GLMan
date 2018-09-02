#include <boost/log/trivial.hpp>

#include "glman/RIB_Interface.h"
#include "glman/RIB_File_Interface.h"
#include "glman/RIB_Rendering_Interface.h"
#include "glman_for_python/RiModule.h"


//Node *(Node::*createNode)(std::string) = &Node::createNode;
//Node *(Node::*createNamedNode)(std::string, std::string) = &Node::createNode;

RiModule::RiModule() {
	iface = NULL;
};

void RiModule::ri_Begin(std::string rendertarget) {
	if (rendertarget == "Ri:render") {
		// image rendering interface
		ri_ifaces.push_back (new RIB_Rendering_Interface());
	} else {
		// rib file rendering interface
		ri_ifaces.push_back (new RIB_File_Interface(rendertarget));
	}
	iface = ri_ifaces.back();
}

void RiModule::ri_End() {
	ri_ifaces.pop_back();
	if (ri_ifaces.size() > 0) {
		iface = ri_ifaces.back();
	} else {
		iface = NULL;
	}
}

void RiModule::ri_WorldBegin() {
	iface->ri_WorldBegin();
}

void RiModule::ri_WorldEnd() {
	iface->ri_WorldEnd();
}

void RiModule::ri_Display(std::string output, std::string display, std::string channels) {
	iface->ri_Display(output, display, channels);
}

void RiModule::ri_Format(unsigned int width, unsigned int height, float aspect) {
	iface->ri_Format(width, height, aspect);
}

void RiModule::ri_Translate(double x, double y, double z){
	iface->ri_Translate(x, y, z);
}

//boost::shared_ptr<RiModule> RiModule::createNode(std::string type_name) {
//	return boost::shared_ptr<RiModule>(new RiModule(_node->createNode(type_name)));
//}

//boost::shared_ptr<RiModule> RiModule::createNamedNode(std::string type_name, std::string name) {
//	return boost::shared_ptr<RiModule>(new RiModule(_node->createNode(type_name, name)));
//}

//boost::shared_ptr<RiModule> RiModule::node(std::string path) {
//	return boost::shared_ptr<RiModule>(new RiModule(_node->node(path)));
//}

namespace glman_for_python {
	void export_Ri() {

		// Ri class
  		boost::python::class_<RiModule, boost::shared_ptr<RiModule>>("Ri")
  			.def("Begin", &RiModule::ri_Begin)
  			.def("WorldBegin", &RiModule::ri_WorldBegin)
  			.def("End", &RiModule::ri_End)
  			.def("WorldEnd", &RiModule::ri_WorldEnd)
  			.def("Display", &RiModule::ri_Display)
  			.def("Format", &RiModule::ri_Format)
  			.def("Translate", &RiModule::ri_Translate);

  	}
}