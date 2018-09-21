#include <boost/log/trivial.hpp>

#include "glman_lib/interfaces/rib_interface.h"
#include "glman_lib/interfaces/rib_file_interface.h"
#include "glman_lib/interfaces/rib_rendering_interface.h"
#include "glman_for_python/ri_module.h"


//Node *(Node::*createNode)(std::string) = &Node::createNode;
//Node *(Node::*createNamedNode)(std::string, std::string) = &Node::createNode;

Ri_Module::Ri_Module() {
	iface = NULL;
};

Ri_Module::~Ri_Module() {
	while (!ri_ifaces.empty())
  	{
    	delete ri_ifaces.back();
    	ri_ifaces.pop_back();
  	}

	if (iface) delete iface;
};

void Ri_Module::ri_Begin(std::string rendertarget) {
	if ((rendertarget == "Ri:render") || (rendertarget == "__render")){
		// image rendering interface
		ri_ifaces.push_back (new RIB_Rendering_Interface());
	} else {
		// rib file rendering interface
		ri_ifaces.push_back (new RIB_File_Interface(rendertarget));
	}
	iface = ri_ifaces.back();
}

void Ri_Module::ri_End() {
	// delete current rib interface from stack ...
	if(iface) {
		delete iface;
		ri_ifaces.pop_back();
	}

	// ... and make previous cureent
	if (ri_ifaces.size() > 0) {
		iface = ri_ifaces.back();
	} else {
		iface = NULL;
	}
}

void Ri_Module::ri_WorldBegin() {
	iface->ri_WorldBegin();
}

void Ri_Module::ri_WorldEnd() {
	iface->ri_WorldEnd();
}

void Ri_Module::ri_Display(std::string output, std::string display, std::string channels) {
	iface->ri_Display(output, display, channels);
}

void Ri_Module::ri_Format(unsigned int width, unsigned int height, float aspect) {
	iface->ri_Format(width, height, aspect);
}

void Ri_Module::ri_Translate(double x, double y, double z){
	iface->ri_Translate(x, y, z);
}

void Ri_Module::ri_Projection(std::string name, PyObject* parms){
	//iface->ri_Translate(x, y, z);
}

void Ri_Module::ri_Geometry(std::string name, PyObject* parms){
	//iface->ri_Translate(x, y, z);
}

void Ri_Module::ri_PointsPolygons(boost::python::list pointsPolyNvertices, boost::python::list pointsPolyVertices,
                  boost::python::dict pointsPolyPointData) {

}

void Ri_Module::ri_ArchiveBegin(std::string name, PyObject* parms) {

}

void Ri_Module::ri_Sides(uint sides) {

}

void Ri_Module::ri_ReverseOrientation(void) {

}

//boost::shared_ptr<Ri_Module> Ri_Module::createNode(std::string type_name) {
//	return boost::shared_ptr<Ri_Module>(new Ri_Module(_node->createNode(type_name)));
//}

//boost::shared_ptr<Ri_Module> Ri_Module::createNamedNode(std::string type_name, std::string name) {
//	return boost::shared_ptr<Ri_Module>(new Ri_Module(_node->createNode(type_name, name)));
//}

//boost::shared_ptr<Ri_Module> Ri_Module::node(std::string path) {
//	return boost::shared_ptr<Ri_Module>(new Ri_Module(_node->node(path)));
//}

// Thin wrappers for overloaded functions default arguments
void ri_Projection_1(Ri_Module* ri, std::string name) { ri->ri_Projection(name); }
void ri_Projection_2(Ri_Module* ri, std::string name, PyObject* parms) { ri->ri_Geometry(name, parms); }
void ri_Geometry_1(Ri_Module* ri, std::string name) { ri->ri_Projection(name); }
void ri_Geometry_2(Ri_Module* ri, std::string name, PyObject* parms) { ri->ri_Geometry(name, parms); }

namespace glman_for_python {
	void export_Ri() {

		// Ri class
  		boost::python::class_<Ri_Module, boost::shared_ptr<Ri_Module>>("Ri")
  			.def("Begin", &Ri_Module::ri_Begin)
  			.def("WorldBegin", &Ri_Module::ri_WorldBegin)
  			.def("End", &Ri_Module::ri_End)
  			.def("WorldEnd", &Ri_Module::ri_WorldEnd)
  			.def("Display", &Ri_Module::ri_Display)
  			.def("Format", &Ri_Module::ri_Format)
  			.def("Translate", &Ri_Module::ri_Translate)
  			.def("Projection", &ri_Projection_1)
  			.def("Projection", &ri_Projection_2)
  			.def("Geometry", &ri_Geometry_1)
  			.def("Geometry", &ri_Geometry_2)
  			.def("PointsPolygons", &Ri_Module::ri_PointsPolygons)
  			.def("ArchiveBegin", &Ri_Module::ri_ArchiveBegin)
  			.def("Sides", &Ri_Module::ri_Sides)
  			.def("ReverseOrientation", &Ri_Module::ri_ReverseOrientation);

  	}
}