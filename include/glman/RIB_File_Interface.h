#ifndef __RIB_File_Interface_h__
#define __RIB_File_Interface_h__

#include <string>
#include <iostream>
#include <fstream>

#include "glman/RIB_Interface.h"

class RIB_File_Interface: public RIB_Interface {
	public:
		RIB_File_Interface(std::string filename);
		~RIB_File_Interface();
		
		void ri_WorldBegin();
		void ri_WorldEnd();

		void ri_Display(std::string output, std::string display, std::string channels);
		void ri_Format(unsigned int width, unsigned int height, float aspect);

		void ri_Translate(double x, double y, double z);
	private:
		void write(std::string cmd);
		unsigned char indent;
		std::string filename;
		std::ofstream myfile;
};


#endif