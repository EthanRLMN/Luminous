#include "Include/Engine.hpp"

#include "Rendering/Vulkan/VulkanRenderInterface.hpp"
#include "ResourceManager/Mesh.hpp"


void Engine::DestroyWindow() const
{
    m_inputManager->Destroy(m_window);
    m_interface->DeleteInputManager(m_inputManager);

    m_window->Destroy();
    m_interface->DeleteWindow(m_window);
}

void Engine::Destroy() const
{
    m_synchronization->Destroy(m_device);
    m_interface->DeleteSynchronization(m_synchronization);

    m_commandBuffer->Destroy();
    m_interface->DeleteCommandBuffer(m_commandBuffer);

    m_descriptor->Destroy(m_device);
    m_interface->DeleteDescriptor(m_descriptor);

    m_buffer->Destroy(m_device);
    m_interface->DeleteBuffer(m_buffer);

    m_model->Destroy();
    m_interface->DeleteModel(m_model);

    m_texture->Destroy(m_device);
    m_interface->DeleteTexture(m_texture);

    m_frameBuffer->Destroy(m_device);
    m_interface->DeleteFrameBuffer(m_frameBuffer);

    m_depthResource->Destroy(m_device);
    m_interface->DeleteDepthResource(m_depthResource);

    m_commandPool->Destroy(m_device);
    m_interface->DeleteCommandPool(m_commandPool);

    m_pipeline->Destroy(m_device);
    m_interface->DeletePipeline(m_pipeline);

    m_descriptorSetLayout->Destroy(m_device);
    m_interface->DeleteDescriptorSetLayout(m_descriptorSetLayout);

    m_renderPass->Destroy(m_device);
    m_interface->DeleteRenderPass(m_renderPass);

    m_swapChain->Destroy(m_device);
    m_interface->DeleteSwapChain(m_swapChain);

    m_device->Destroy();
    m_interface->DeleteDevice(m_device);

    m_surface->Destroy(m_instance);
    m_interface->DeleteSurface(m_surface);

    m_instance->Destroy();
    m_interface->DeleteContext(m_instance);

    m_inputManager->Destroy(m_window);

    m_interface->DeleteInputManager(m_inputManager);
    m_interface->DeleteResourceManager(m_resourceManager);
    //delete(m_window);

    m_renderingDraw->Destroy();
    m_interface->DeleteRenderingDraw(m_renderingDraw);
}


void Engine::Init()
{
    Debug::Logger& l_logger = Debug::Logger::GetInstance();
    l_logger.Init("Engine", 1_MiB, 5, true);

    m_interface = new VulkanRenderInterface();
    m_isRunning = true;

    m_window = m_interface->InstantiateWindow();
    m_window->Initialize("Luminous", 1280, 720);

    m_inputManager = m_interface->InstantiateInputManager();
    m_inputManager->Initialize(m_window);

    m_instance = m_interface->InstantiateContext();
    m_instance->Create(m_window);

    m_surface = m_interface->InstantiateSurface();
    m_surface->Create(m_instance, m_window);

    m_device = m_interface->InstantiateDevice();
    m_device->Create(m_instance, m_window, m_surface);

    m_swapChain = m_interface->InstantiateSwapChain();
    m_swapChain->Create(m_window, m_device, m_surface);

    m_renderPass = m_interface->InstantiateRenderPass();
    m_renderPass->Create(m_swapChain, m_device);

    m_uiRenderPass = m_interface->InstantiateRenderPass();

    m_descriptorSetLayout = m_interface->InstantiateDescriptorSetLayout();
    m_descriptorSetLayout->Create(m_device);

    m_pipeline = m_interface->InstantiatePipeline();
    m_pipeline->Create(m_device, m_renderPass, m_descriptorSetLayout);

    m_commandPool = m_interface->InstantiateCommandPool();
    m_commandPool->Create(m_device, m_surface);

    m_depthResource = m_interface->InstantiateDepthResource();
    m_depthResource->Create(m_device, m_swapChain, m_renderPass);

    m_frameBuffer = m_interface->InstantiateFrameBuffer();
    m_frameBuffer->Create(m_device, m_swapChain, m_renderPass, m_depthResource);

    m_texture = m_interface->InstantiateTexture();
    m_texture->Create(m_device, m_swapChain, m_depthResource, m_commandPool);

    m_model = m_interface->InstantiateModel();
    m_model->Create();

    m_buffer = m_interface->InstantiateBuffer();
    m_buffer->Create(m_device, m_texture, m_commandPool, m_depthResource, m_model);

    m_descriptor = m_interface->InstantiateDescriptor();
    m_descriptor->Create(m_device, m_descriptorSetLayout, m_texture, m_buffer);

    m_commandBuffer = m_interface->InstantiateCommandBuffer();
    m_commandBuffer->Create(m_device, m_commandPool);

    m_editorCommandBuffer = m_interface->InstantiateCommandBuffer();
    m_commandBuffer->Create(m_device, m_commandPool);

    m_synchronization = m_interface->InstantiateSynchronization();
    m_synchronization->Create(m_device);

    m_resourceManager = m_interface->InstantiateResourceManager();
    Mesh* mesh2 = m_resourceManager->GetResource<Mesh>("Engine/Assets/Models/metalSonic.obj");
    Mesh* mesh = m_resourceManager->LoadResource<Mesh>("Engine/Assets/Models/metalSonic.obj");

    //m_resourceManager->DeleteResource<Mesh>("Engine/Assets/Models/metalSonic.obj");
    Mesh* mesh5 = m_resourceManager->LoadResource<Mesh>("Engine/Assets/Models/metalSonic.obj");
    Mesh* mesh3 = m_resourceManager->GetResource<Mesh>("Engine/Assets/Models/metalSonic.obj");

    m_renderingDraw = m_interface->InstantiateRenderingDraw();
}

void Engine::Update()
{
    // TODO : Cleanup
    while (!m_window->ShouldClose())
    {
        m_window->PollEvents();
        m_inputManager->Update(m_window);

        m_renderingDraw->Create(m_window, m_device, m_swapChain, m_pipeline, m_buffer, m_renderPass, m_descriptor, m_model, m_synchronization, m_commandBuffer, m_frameBuffer, m_depthResource, m_surface);
    }
    m_isRunning = false;
    Destroy();
    DestroyWindow();
}
