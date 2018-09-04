#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <string>
#include <iostream>

#include "glman_lib/renderer/renderer.h"

#include "glman_for_python/ri_module.h"

namespace glman_for_python {

	//Renderer& renderer = Renderer::Instance();

  	void Init(boost::python::list args) {
  		std::cout << "glman_for_python args: ";
  		for (int i = 0; i < len(args); ++i)
    	{
			std::cout << boost::python::extract<std::string>(boost::python::object(args[i]).attr("__str__")())();
    	}
    	std::cout << std::endl;
  	};

  	void export_Ri();

}


BOOST_PYTHON_MODULE(glman_for_python){

  	// Ri()
	//boost::python::def("Ri", &glman_for_python::getRi);
	boost::python::def("Init", &glman_for_python::Init);

	// Ri class
  	glman_for_python::export_Ri();

}






