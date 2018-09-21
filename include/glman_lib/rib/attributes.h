#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include <string>
#include <map>
#include <vector>

using namespace std;

class Attributes {
	public:
		Attributes();
		~Attributes();

	private:
		std::vector<Attributes*> attributes;
};

#endif