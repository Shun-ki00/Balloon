#include "pch.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Particle/EffectController.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Node/Root.h"


std::unique_ptr<IObject>EffectFactory::CreateEffectController(IObject* parent, std::vector<ParametersID> ids)
{

	std::unique_ptr<EffectController> m_effectController;

	m_effectController.reset(new EffectController(parent ,true , IObject::ObjectID::EFFECT_CONTROLLER));

	m_effectController->Initialize();

	for (const auto& id : ids)
	{
		//m_effectController->AddEffect(id);
	}

	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::EFFECT_CONTROLLER, Root::GetInstance()->GetNodeCount(), m_effectController.get());

	return std::move(m_effectController);
}