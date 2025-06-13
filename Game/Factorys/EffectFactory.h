#pragma once
#include "Interface/IObject.h"
#include "Game/Parameters/ParameterKeys.h"


class EffectFactory
{
public:

	static std::unique_ptr<IObject> CreateEffectController(IObject* parent, std::vector<ParametersID> ids);
};