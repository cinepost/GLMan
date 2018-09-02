#ifndef __RiModule_h__
#define __RiModule_h__

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <vector>

#include "glman/RIB_Interface.h"

class RiModule {
	public:
		RiModule();

		void ri_Begin(std::string rendertarget);
		void ri_End();
		void ri_WorldBegin();
		void ri_WorldEnd();
		void ri_Display(std::string output, std::string display, std::string channels);
		void ri_Format(unsigned int width, unsigned int height, float aspect);
		void ri_Translate(double x, double y, double z);
		void ri_Projection(std::string name, PyObject* parms=NULL);
		void ri_Geometry(std::string name, PyObject* parms=NULL);

	private:
		std::vector<RIB_Interface *> ri_ifaces; // ri interfaces stack
		RIB_Interface *iface; // current ri interface set by ri.Begin(...)
};


#endif