#include "glman_lib/rib/attributes.h"


Attributes::Attributes(){

}

Attributes::~Attributes(){
	// destoy all nested attributes
	while (!attributes.empty())
  	{
    	delete attributes.back();
    	attributes.pop_back();
  	}
}