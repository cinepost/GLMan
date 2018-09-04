#ifndef __Display_h__
#define __Display_h__

#include <string>
#include <vector>

#include "prman/ndspy.h"

class Display {
	public:
		Display(std::string drivername);
		/*
		PtDspyError (* DspyImageOpen)(PtDspyImageHandle *pvImage,
        const char *drivername,
        const char *filename,
        int width,
        int height,
        int paramCount,
        const UserParameter *parameters,
        int formatCount,
        PtDspyDevFormat *format,
        PtFlagStuff *flagstuff);
        */
        PtDspyError (* DspyImageOpen)(PtDspyImageHandle *,
        const char *,
        const char *,
        int ,
        int ,
        int ,
        const UserParameter *,
        int ,
        PtDspyDevFormat *,
        PtFlagStuff *);

	private:

};


#endif