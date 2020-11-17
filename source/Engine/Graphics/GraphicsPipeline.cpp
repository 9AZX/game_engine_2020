#include "Engine/Graphics/GraphicsPipeline.hpp"
#include "Engine/Utils.hpp"
#include "Engine/Graphics/Vertex.hpp"

#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

Engine::GraphicsPipeline::GraphicsPipeline(std::shared_ptr<Device> device, std::shared_ptr<Renderpass> renderPass) : _device(device), _renderPass(renderPass)
{
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

static std::vector<char> readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void Engine::GraphicsPipeline::createGraphicsPipeline(Engine::ShaderResource *vertexShader, Engine::ShaderResource *fragmentShader)
{
    auto vert = readFile("C:/Users/joni/tek/game_engine_2020/include/Engine/Shader/vert.spv");

    auto frag = readFile("C:/Users/joni/tek/game_engine_2020/include/Engine/Shader/frag.spv");
    /* vk::UniqueShaderModule vertShaderModule = _createShadermodule(vertexShader->getShader());
    vk::UniqueShaderModule fragShaderModule = _createShadermodule(fragmentShader->getShader());*/

    vk::UniqueShaderModule vertShaderModule = _createShadermodule(vert);
    vk::UniqueShaderModule fragShaderModule = _createShadermodule(frag);

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

    /*auto a = Engine::Vertex::getAttributeDescriptions().begin();
    auto b = Engine::Vertex::getAttributeDescriptions().end();*/

    auto c = Engine::Vertex::getAttributeDescriptions();
    //auto b = Engine::Vertex::getAttributeDescriptions().end();
    //vertexInputAttributeDescriptions.insert(vertexInputAttributeDescriptions.end(), a, b);

    vertexInputAttributeDescriptions.push_back(c.at(0));
    vertexInputAttributeDescriptions.push_back(c.at(1));
    vertexInputAttributeDescriptions.push_back(c.at(2));
    vertexInputAttributeDescriptions.push_back(c.at(3));

    pipelineVertexInputStateCreateInfo.setVertexBindingDescriptions(vertexInputBindingDescription);
    pipelineVertexInputStateCreateInfo.setVertexAttributeDescriptions(vertexInputAttributeDescriptions);

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
                                                              _renderPass->renderPass);

    _pipelineCache = _device->getUniqueDevice()->get().createPipelineCacheUnique(vk::PipelineCacheCreateInfo());
    auto result = _device->getUniqueDevice()->get().createGraphicsPipelineUnique(_pipelineCache.get(), graphicsPipelineCreateInfo);
    assert(result.result == vk::Result::eSuccess);
    std::move(result.value);
}

vk::UniqueShaderModule Engine::GraphicsPipeline::_createShadermodule(const std::vector<unsigned int> &code)
{
    vk::ShaderModuleCreateInfo vertexShaderModuleCreateInfo(vk::ShaderModuleCreateFlags(), code);

    vk::UniqueShaderModule shaderModule;
    shaderModule = _device->getUniqueDevice()->get().createShaderModuleUnique(vertexShaderModuleCreateInfo);
    return shaderModule;
}

vk::UniqueShaderModule Engine::GraphicsPipeline::_createShadermodule(const std::vector<char> &code)
{
    vk::ShaderModuleCreateInfo vertexShaderModuleCreateInfo(vk::ShaderModuleCreateFlags(), code.size(), reinterpret_cast<const uint32_t *>(code.data()));

    vk::UniqueShaderModule shaderModule;
    shaderModule = _device->getUniqueDevice()->get().createShaderModuleUnique(vertexShaderModuleCreateInfo);
    return shaderModule;
}