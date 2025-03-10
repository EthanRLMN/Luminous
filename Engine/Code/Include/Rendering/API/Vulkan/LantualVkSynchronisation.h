#pragma once
#include <iostream>
#include "../../LantualSynchronisation.h"


class LantualVkSynchronisation : public LantualSynchronisation
{
	void Create() override;
	void Destroy() override;
};
