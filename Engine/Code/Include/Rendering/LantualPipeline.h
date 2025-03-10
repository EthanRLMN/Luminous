#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>

class LantualDevice;
class LantualRenderPass;


class LantualPipeline {
public:

	virtual void Create() = 0;
	virtual void Destroy() = 0;

};