#ifndef ENGINE_GRAPHICSPIPELINE_HPP_
#define ENGINE_GRAPHICSPIPELINE_HPP_

#include <vulkan/vulkan.hpp>
#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/RenderPass.hpp"
#include "Engine/Resources/ShaderResource.hpp"
namespace Engine
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline(std::shared_ptr<Device> device, std::shared_ptr<Renderpass> renderPass);
        ~GraphicsPipeline();

        void createGraphicsPipeline(Engine::ShaderResource *vertexShader, Engine::ShaderResource *fragmentShader);

    private:
        std::shared_ptr<Renderpass> _renderPass;
        vk::UniquePipelineLayout _pipelineLayout;
        vk::UniquePipeline _graphicsPipeline;
        vk::UniquePipelineCache _pipelineCache;
        std::shared_ptr<Device> _device;
        vk::UniqueShaderModule _vertexShaderModule;
        vk::UniqueShaderModule _fragmentShaderModule;

        vk::UniqueShaderModule _createShadermodule(const std::vector<unsigned int> &code);
    };
} // namespace Engine

#endif /* !ENGINE_GRAPHICSPIPELINE_HPP_ */
