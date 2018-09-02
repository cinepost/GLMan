#ifndef __Renderer_h__
#define __Renderer_h__

#include <iostream>
#include <string>
#include <map>
#include <vector>

// Renderer class is a singleton
class Renderer {
    public:
    	static Renderer& Instance() {
    		// this is a lazy and thread safe code
    		static Renderer e;
    		return e;
    	}
		

	private:
		Renderer(); // constructor is protected
		~Renderer() {}; // so as destructor

		// need to forbid copying
		Renderer(Renderer const&) = delete;
		Renderer& operator= (Renderer const&) = delete;

};

#endif