#include "GraphicsPipeline.hpp"
#include "Utils.hpp"
#include "Graphics/Vertex.hpp"

Engine::GraphicsPipeline::GraphicsPipeline(std::shared_ptr<Device> device) : _device(device)
{
    /*
    std::vector<vk::AttachmentDescription> attachmentDescriptions;
    attachmentDescriptions.push_back(vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
                                                               colorFormat,
                                                               vk::SampleCountFlagBits::e1,
                                                               vk::AttachmentLoadOp::eClear,
                                                               vk::AttachmentStoreOp::eStore,
                                                               vk::AttachmentLoadOp::eDontCare,
                                                               vk::AttachmentStoreOp::eDontCare,
                                                               vk::ImageLayout::eUndefined,
                                                               vk::ImageLayout::eTransferDstOptimal));
    if (depthFormat != vk::Format::eUndefined)
    {
        attachmentDescriptions.push_back(
            vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
                                      depthFormat,
                                      vk::SampleCountFlagBits::e1,
                                      loadOp,
                                      vk::AttachmentStoreOp::eDontCare,
                                      vk::AttachmentLoadOp::eDontCare,
                                      vk::AttachmentStoreOp::eDontCare,
                                      vk::ImageLayout::eUndefined,
                                      vk::ImageLayout::eDepthStencilAttachmentOptimal));
    }
    vk::AttachmentReference colorAttachment(0, vk::ImageLayout::eColorAttachmentOptimal);
    vk::AttachmentReference depthAttachment(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);
    vk::SubpassDescription subpassDescription(vk::SubpassDescriptionFlags(),
                                              vk::PipelineBindPoint::eGraphics,
                                              {},
                                              colorAttachment,
                                              {},
                                              (depthFormat != vk::Format::eUndefined) ? &depthAttachment
                                                                                      : nullptr);
    _renderPass = _device->getUniqueDevice()->get().createRenderPassUnique(
        vk::RenderPassCreateInfo(vk::RenderPassCreateFlags(), attachmentDescriptions, subpassDescription));
*/

    std::vector<std::tuple<vk::DescriptorType, uint32_t, vk::ShaderStageFlags>> const &bindingData = {{vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex}};
    std::vector<vk::DescriptorSetLayoutBinding> bindings(bindingData.size());
    for (size_t i = 0; i < bindingData.size(); i++)
    {
        bindings[i] = vk::DescriptorSetLayoutBinding(checked_cast<uint32_t>(i),
                                                     std::get<0>(bindingData[i]),
                                                     std::get<1>(bindingData[i]),
                                                     std::get<2>(bindingData[i]));
    }
    vk::UniqueDescriptorSetLayout descriptorSetLayout = _device->getUniqueDevice()->get().createDescriptorSetLayoutUnique(vk::DescriptorSetLayoutCreateInfo(vk::DescriptorSetLayoutCreateFlags(), bindings));

    _pipelineLayout = device->getUniqueDevice()->get().createPipelineLayoutUnique(
        vk::PipelineLayoutCreateInfo(vk::PipelineLayoutCreateFlags(), *descriptorSetLayout));
}

Engine::GraphicsPipeline::~GraphicsPipeline()
{
}

void Engine::GraphicsPipeline::createGraphicsPipeline(Engine::ShaderResource *vertexShader, Engine::ShaderResource *fragmentShader)
{
    vk::UniqueShaderModule vertShaderModule = _createShadermodule(vertexShader->getShader());
    vk::UniqueShaderModule fragShaderModule = _createShadermodule(fragmentShader->getShader());

    std::array<vk::PipelineShaderStageCreateInfo, 2> pipelineShaderStageCreateInfos = {
        vk::PipelineShaderStageCreateInfo(vk::PipelineShaderStageCreateFlags(),
                                          vk::ShaderStageFlagBits::eVertex,
                                          vertShaderModule.get(),
                                          "main"),
        vk::PipelineShaderStageCreateInfo(vk::PipelineShaderStageCreateFlags(),
                                          vk::ShaderStageFlagBits::eFragment,
                                          fragShaderModule.get(),
                                          "main")};

    std::vector<vk::VertexInputAttributeDescription> vertexInputAttributeDescriptions;
    vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo;
    vk::VertexInputBindingDescription vertexInputBindingDescription(Engine::Vertex::getBindingDescription());

    vertexInputAttributeDescriptions.insert(vertexInputAttributeDescriptions.end(), Engine::Vertex::getAttributeDescriptions().begin(), Engine::Vertex::getAttributeDescriptions().end());

    vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
        vk::PipelineInputAssemblyStateCreateFlags(), vk::PrimitiveTopology::eTriangleList);

    vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
        vk::PipelineViewportStateCreateFlags(), 1, nullptr, 1, nullptr);

    vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
        vk::PipelineRasterizationStateCreateFlags(),
        false,
        false,
        vk::PolygonMode::eFill,
        vk::CullModeFlagBits::eBack,
        vk::FrontFace::eCounterClockwise,
        false,
        0.0f,
        0.0f,
        0.0f,
        1.0f);

    vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo({}, vk::SampleCountFlagBits::e1);

    vk::StencilOpState stencilOpState(
        vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::CompareOp::eAlways);
    vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
        vk::PipelineDepthStencilStateCreateFlags(),
        true,
        true,
        vk::CompareOp::eLessOrEqual,
        false,
        false,
        stencilOpState,
        stencilOpState);

    vk::ColorComponentFlags colorComponentFlags(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                                                vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
    vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(false,
                                                                            vk::BlendFactor::eZero,
                                                                            vk::BlendFactor::eZero,
                                                                            vk::BlendOp::eAdd,
                                                                            vk::BlendFactor::eZero,
                                                                            vk::BlendFactor::eZero,
                                                                            vk::BlendOp::eAdd,
                                                                            colorComponentFlags);
    vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(vk::PipelineColorBlendStateCreateFlags(),
                                                                            false,
                                                                            vk::LogicOp::eNoOp,
                                                                            pipelineColorBlendAttachmentState,
                                                                            {{1.0f, 1.0f, 1.0f, 1.0f}});

    std::array<vk::DynamicState, 2> dynamicStates = {vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(vk::PipelineDynamicStateCreateFlags(),
                                                                      dynamicStates);

    vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo(vk::PipelineCreateFlags(),
                                                              pipelineShaderStageCreateInfos,
                                                              &pipelineVertexInputStateCreateInfo,
                                                              &pipelineInputAssemblyStateCreateInfo,
                                                              nullptr,
                                                              &pipelineViewportStateCreateInfo,
                                                              &pipelineRasterizationStateCreateInfo,
                                                              &pipelineMultisampleStateCreateInfo,
                                                              &pipelineDepthStencilStateCreateInfo,
                                                              &pipelineColorBlendStateCreateInfo,
                                                              &pipelineDynamicStateCreateInfo,
                                                              _pipelineLayout.get(),
                                                              nullptr);

    auto result = _device->getUniqueDevice()->get().createGraphicsPipelineUnique(_pipelineCache.get(), graphicsPipelineCreateInfo);
    assert(result.result == vk::Result::eSuccess);
    std::move(result.value);
}

vk::UniqueShaderModule Engine::GraphicsPipeline::_createShadermodule(const std::vector<unsigned int> &code)
{
    vk::ShaderModuleCreateInfo vertexShaderModuleCreateInfo(vk::ShaderModuleCreateFlags(), code);

    vk::UniqueShaderModule shaderModule;

    _device->getUniqueDevice()->get().createShaderModuleUnique(vertexShaderModuleCreateInfo);
    return shaderModule;
}