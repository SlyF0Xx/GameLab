﻿#include "BTSystem.h"
#include <variant>

#include "../BaseComponents/BTComponent.h"

BTSystem::BTSystem(::entt::registry& registry) : m_registry(registry)
{
    NonTickFunction::registry = &registry;
}

BTSystem::~BTSystem()
{
    // ..
}

void BTSystem::tick(float deltaSeconds)
{
    auto Cooldowns = m_registry.view<BTCooldownComponent>();
    Cooldowns.each([this,deltaSeconds](BTCooldownComponent& cooldown)
    {
        cooldown.remains -= deltaSeconds;
        if (cooldown.remains <= 0.0f)
        {
            cooldown.onCooldownRef = false;
            m_registry.destroy(entt::to_entity(m_registry,cooldown));
        }
    });

    auto AITasks = m_registry.view<BTComponent>();
    AITasks.each([this,deltaSeconds](BTComponent& BT)
    {
        auto script = m_registry.try_get<diffusion::ScriptComponentState>(entt::to_entity(m_registry,BT));
        if (script)
        {
            auto status = std::visit(BehaviourTickFunctions{script, deltaSeconds}, BT.root);
            if (status != BehaviourState::Running)
            {
                std::visit(NonTickFunction{script, BehaviourActionFunctions::OnFinish}, BT.root);
                std::visit(NonTickFunction{script, BehaviourActionFunctions::OnInit}, BT.root);
            }
        }
    });
}

void BTSystem::onInit() {
    auto AITasks = m_registry.view<BTComponent>();
    AITasks.each([this](BTComponent& BT) {
        auto script = m_registry.try_get<diffusion::ScriptComponentState>(entt::to_entity(m_registry, BT));
        if (script) {
            std::visit(NonTickFunction {script, BehaviourActionFunctions::OnInit}, BT.root);
        }
    });
}

void BTSystem::onAbort() {
    auto AITasks = m_registry.view<BTComponent>();
    AITasks.each([this](BTComponent& BT) {
        auto script = m_registry.try_get<diffusion::ScriptComponentState>(entt::to_entity(m_registry, BT));
        if (script) {
            std::visit(NonTickFunction {script, BehaviourActionFunctions::OnAbort}, BT.root);
        }
    });
}
