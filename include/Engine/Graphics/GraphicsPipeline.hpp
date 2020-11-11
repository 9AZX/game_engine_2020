#ifndef ENGINE_GRAPHICSPIPELINE_HPP_
#define ENGINE_GRAPHICSPIPELINE_HPP_

#include <vulkan/vulkan.hpp>

namespace Engine
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline();
        ~GraphicsPipeline();

        void createGraphicsPipeline(std::string filePathVertexShader, std::string filePathFragmentShader);

    private:
        vk::UniquePipelineLayout _pipelineLayout;
        vk::UniquePipeline _graphicsPipeline;
    };
} // namespace Engine

#endif /* !ENGINE_GRAPHICSPIPELINE_HPP_ */
