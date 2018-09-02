#include <dlfcn.h>

#include <boost/format.hpp>

#include "glman/Display.h"

Display::Display(std::string drivername){
	char *error;

	boost::format libdspy_name("/opt/glman/bin/d_%1%.so");
	libdspy_name % drivername;

	void* lib_handle = dlopen(libdspy_name.str().c_str(), RTLD_LOCAL|RTLD_LAZY);
    if (!lib_handle) {
        printf("[%s] Unable to load library: %s\n", __FILE__, dlerror());
        exit(1);
    } else {
    	//DspyImageOpen = dlsym(lib_handle, "DspyImageOpen");
        //if ((error = dlerror()) != NULL)  {
        //    fputs(error, stderr);
        //    exit(1);
        //}
    }
}
