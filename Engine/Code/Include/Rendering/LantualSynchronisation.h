#pragma once
#include <iostream>
#include <vector>



class LantualDevice;

class LantualSynchronisation {
public:

	virtual void Create() = 0;
	virtual void Destroy() = 0;

};