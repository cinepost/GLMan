#ifndef __IFD_Interface_h__
#define __IFD_Interface_h__

#include <string>


class IFD_Interface {
	public:
		IFD_Interface();
		
		virtual void ray_Start(std::string object_type)=0;
		virtual void ray_End()=0;

		virtual void ray_DeviceOption(std::string type, std::string name, std::string value)=0;

		virtual void ray_Time(double time)=0;
		virtual void ray_Raytrace()=0;

		virtual void ray_Geometry(std::string geometry_object)=0;

	private:
		
};


#endif