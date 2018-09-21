#ifndef __Display_h__
#define __Display_h__

#include <string>
#include <vector>

#include "prman/ndspy.h"

class Display {
	public:
		Display(std::string drivername);
		

	private:
                PtDspyOpenFuncPtr               m_OpenFunc;
                PtDspyWriteFuncPtr              m_WriteFunc;
                PtDspyDeepWriteFuncPtr          m_DeepWriteFunc;
                PtDspyActiveRegionFuncPtr       m_ActiveRedionFunc;
                PtDspyCloseFuncPtr              m_CloseFunc;
                PtDspyFlushFuncPtr              m_FlushFunc;
                PtDspyReopenFuncPtr             m_ReopenFunc;
                PtDspyDelayCloseFuncPtr         m_DelayCloseFunc;
                PtDspyQueryFuncPtr              m_QueryFunc;
};


#endif