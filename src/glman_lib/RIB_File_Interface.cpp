#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#include "glman/RIB_File_Interface.h"

RIB_File_Interface::RIB_File_Interface(std::string filename){
	indent = 0;
	this->filename = filename;
	myfile.open (filename);
	BOOST_LOG_TRIVIAL(info) << "RIB interface for file " << filename << " initialized";
}

RIB_File_Interface::~RIB_File_Interface(){
	myfile.close();
}


void RIB_File_Interface::write(std::string cmd) {
	for (int i=0; i < indent; i++) {
		myfile << "  ";
	}
	myfile << cmd << std::endl;
}


void RIB_File_Interface::ri_WorldBegin() {
	write("WorldBegin");
	indent++;
}


void RIB_File_Interface::ri_WorldEnd() {
	indent--;
	write("WorldEnd");
}


void RIB_File_Interface::ri_Display(std::string output, std::string display, std::string channels) {
	boost::format cmd("Display \"%1%\" \"%2%\" \"%3%\"");
	cmd % output % display % channels;
	write(cmd.str());
}


void RIB_File_Interface::ri_Format(unsigned int width, unsigned int height, float aspect) {
	boost::format cmd("Format %1% %2% %3%");
	cmd % width % height % aspect;
	write(cmd.str());
}


void RIB_File_Interface::ri_Translate(double x, double y, double z) {
	boost::format cmd("Translate %1% %2% %3%");
	cmd  % x % y % z;
	write(cmd.str());
}