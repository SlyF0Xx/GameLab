#pragma once

#include "Entity.h"
#include "Engine.h"

#include <filesystem>

namespace diffusion {

class ImportableEntity : public Entity
{
public:
	ImportableEntity(
		Game& game,
		const std::filesystem::path& path,
		const glm::vec3& position,
		const glm::vec3& rotation,
		const glm::vec3& scale);
};

} // namespace diffusion {