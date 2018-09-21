#include <dlfcn.h>
#include <stdlib.h>
#include <boost/format.hpp>

#include "glman_lib/renderer/display.h"

Display::Display(std::string drivername){
	char *error;
    char *glman_home = getenv("GLMAN_HOME");
    
	boost::format libdspy_name("%1%/etc/d_%2%.so");
	libdspy_name % glman_home % drivername;

	void* lib_handle = dlopen(libdspy_name.str().c_str(), RTLD_NOW);//RTLD_LOCAL|RTLD_LAZY);
    if (!lib_handle) {
        printf("[%s] Unable to load library: %s\n", __FILE__, dlerror());
        exit(1);
    } else {
    	m_OpenFunc = (PtDspyOpenFuncPtr)dlsym(lib_handle, "DspyImageOpen");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        m_CloseFunc = (PtDspyCloseFuncPtr)dlsym(lib_handle, "DspyImageClose");
    }
}
