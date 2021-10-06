#include "CubeEntity.h"

#include "BoundingComponent.h"
#include "TransformComponent.h"
#include "PossessedComponent.h"
#include "VulkanCameraComponent.h"

namespace diffusion {

CubeEntity::CubeEntity(Game& game, glm::vec3 translation)
    : PrimitiveEntity(
        game,
        { 
          PrimitiveColoredVertex{-0.25f, 0.75f, 0.5f, {0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.5f, {0.0f, 0.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.5f, {1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.5f, {1.0f, 0.0f}},

          PrimitiveColoredVertex{-0.25f, 0.75f, 0.7f, {0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.7f, {0.0f, 0.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.7f, {1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.7f, {1.0f, 0.0f}}
        },
        { 
          0, 1, 2,
          1, 3, 2,
          0, 4, 5,
          0, 5, 1,
          2, 6, 7,
          2, 7, 3,
          4, 5, 6,
          5, 7, 6,
          1, 5, 7,
          1, 7, 3,
          0, 4, 6,
          0, 6, 2
        },
        translation,
        { 0, 0, 0 },
        { 1, 1, 1 }
    )
{
    add_component(ComponentGuard(std::make_unique<BoundingComponent>(glm::vec3(-0.5f, 0.5f, 0.6f), 0.25f, std::vector<Component::Tag>{}, this)));
}

CubePossesedEntity::CubePossesedEntity(Game& game, glm::vec3 translation)
    : CubeEntity(game, translation)
{
    add_component(ComponentGuard(std::make_unique<PossessedComponent>(std::vector<Component::Tag>{}, this)));
    add_component(ComponentGuard(std::make_unique<VulkanCameraComponent>(game, std::vector<Component::Tag>{ CameraComponent::s_main_camera_component_tag }, this)));
}

} // namespace diffusion {