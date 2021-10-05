#pragma once

#include "IRender.h"
#include "System.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

class Game;

class ForwardRender :
    public IRender,
    public diffusion::System
{
    struct PerSwapchainImageData
    {
        // Variable per image value
        vk::Image m_color_image;

        vk::Image m_depth_image;
        vk::DeviceMemory m_depth_memory;

        vk::ImageView m_color_image_view;
        vk::ImageView m_depth_image_view;

        vk::Framebuffer m_framebuffer;

        vk::CommandBuffer m_command_buffer;

        vk::DescriptorSet m_shadows_descriptor_set;

        // Constant per image value
        vk::Fence m_fence;
        vk::Semaphore m_sema;
    };

    std::vector<vk::DescriptorSetLayout> m_descriptor_set_layouts;
    vk::PipelineLayout m_layout;

    vk::Semaphore m_sema;
    std::vector<vk::CommandBuffer> m_command_buffers;

    std::vector<PerSwapchainImageData> m_swapchain_data;

    vk::RenderPass m_render_pass;
    vk::ShaderModule m_vertex_shader;
    vk::ShaderModule m_fragment_shader;
    vk::PipelineCache m_cache;
    vk::Pipeline m_pipeline;


    //vk::PipelineLayout m_layout;
    //std::array<vk::DescriptorSetLayout, 1> m_descriptor_set_layouts;

    Game& m_game;

    void InitializePipelineLayout();

    void InitializeRenderPass();
    void DestroyRenderPass();

    void InitializeConstantPerImage();
    // screen dependent
    // flexiable
    void DestroyConstantPerImageResources();
    void InitializeVariablePerImage(const std::vector<vk::Image>& swapchain_images);
    void DestroyVariablePerImageResources();

    void InitializePipeline();
    void DestroyPipeline();

    void InitCommandBuffer();
    void DestroyCommandBuffer();

    void DestroyResources();

public:
    ForwardRender(Game& game, const std::vector<vk::Image>& swapchain_images);
    ~ForwardRender();

    void Update(const std::vector<vk::Image>& swapchain_images) override;

    // Only after init objects
    void Initialize() override;

    void Draw() override;

    void tick() override;
};
