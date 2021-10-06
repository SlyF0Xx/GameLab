#pragma once
#include "CameraComponent.h"

namespace diffusion {

class VulkanCameraComponent :
    public CameraComponent
{
public:
    VulkanCameraComponent(Game& game, const std::vector<Tag>& tags, Entity* parent);
    ~VulkanCameraComponent();

    void Draw(const vk::PipelineLayout& layout, const vk::CommandBuffer& cmd_buffer);

    static inline Tag s_vulkan_camera_component;

private:
    void recalculate_state() override;

    vk::DescriptorPool m_descriptor_pool;
    vk::DescriptorSet m_descriptor_set;
    glm::mat4 m_view_projection_matrix;
    vk::Buffer m_world_view_projection_matrix_buffer;
    vk::DeviceMemory m_world_view_projection_matrix_memory;
    std::byte* m_world_view_projection_mapped_memory;
};

} // namespace diffusion {