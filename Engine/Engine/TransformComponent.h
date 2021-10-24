#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace diffusion {

namespace entt {

struct TransformComponent
{
	glm::mat4 m_world_matrix;
};

}

class TransformComponent : public Component
{
public:
	inline static Tag s_transform_component_tag;

	TransformComponent(
		const glm::vec3& position,
		const glm::vec3& rotation,
		const glm::vec3& scale,
		const std::vector<Tag>& tags,
		Entity* parent);

	virtual void UpdateWorldMatrix(const glm::mat4& world_matrix);

	glm::mat4 get_world_matrix() const
	{
		return m_world_matrix;
	}

private:
	glm::mat4 m_world_matrix;
};

} // namespace diffusion {