#pragma once
#ifndef __ROUTES_H__
#define __ROUTES_H__

#include <string>

using std::string;

class Routes {
public:
	/*Variables*/
	string model;
	string texture;

	Routes(string model, string texture);
	Routes();
	~Routes();
};

#endif
