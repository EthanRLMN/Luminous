#include "Include/Engine.hpp"

#include "Game/Systems/Time.inl"
#include "Rendering/Vulkan/VulkanRenderInterface.hpp"
#include "ResourceManager/ResourceManager.hpp"


#define JPH_DEBUG_RENDERER


void Engine::Init()
{
    Debug::Logger& l_logger = Debug::Logger::GetInstance();
    l_logger.Init("Engine", 1_MiB, 5, true);

    m_interface = new VulkanRenderInterface();
    m_scene = new Scene();
    m_physicsSystem = new PhysicsSystem();
    m_isRunning = true;

    Window();
    Input();
    PreRender();
    InitPhysics();

    m_entityManager.Initialize(this);
    m_scene->RegisterScene(m_entityManager);
    m_entityManager.GameplayStarted();

}

void Engine::Update()
{
    Time::Update();

    m_window->Update();
    m_inputManager->Update();
    m_renderer->DrawFrame(m_window, m_device, m_swapChain, m_pipeline, m_buffer, m_renderPassManager, m_descriptor, m_synchronization, m_commandBuffer, m_frameBufferManager, m_depthResource, m_surface, m_multiSampling, m_inputManager, m_entityManager);
    m_physicsSystem->Update();

    m_inputManager->ResetMouseDelta();
    if (m_window->ShouldClose())
        m_isRunning = false;
}

void Engine::Destroy() const
{
    ResourceManager::GetInstance().DeleteResource<VulkanShader>("v=Engine/Assets/Shaders/vert.spv, f=Engine/Assets/Shaders/frag.spv, t=, g=", m_device);
    ResourceManager::Destroy(m_device);

    m_renderer->CastVulkan()->DestroyViewportImage(m_device);
    m_descriptor->Destroy(m_device);
    m_interface->DeleteDescriptor(m_descriptor);

    m_buffer->Destroy(m_device);
    m_interface->DeleteBuffer(m_buffer);

    m_frameBufferManager->Destroy(m_device);
    m_interface->DeleteFrameBufferManager(m_frameBufferManager);

    m_depthResource->Destroy(m_device);
    m_interface->DeleteDepthResource(m_depthResource);

    m_multiSampling->Destroy(m_device);
    m_interface->DeleteMultiSampling(m_multiSampling);

    m_editorCommandPool->Destroy(m_device, m_synchronization, m_renderer);
    m_interface->DeleteCommandPool(m_editorCommandPool);

    m_commandPool->Destroy(m_device, m_synchronization, m_renderer);
    m_interface->DeleteCommandPool(m_commandPool);

    m_pipeline->Destroy(m_device);
    m_interface->DeletePipeline(m_pipeline);

    m_descriptorSetLayout->Destroy(m_device);
    m_interface->DeleteDescriptorSetLayout(m_descriptorSetLayout);

    m_renderPassManager->Destroy(m_device);
    m_interface->DeleteRenderPassManager(m_renderPassManager);

    m_swapChain->Destroy(m_device);
    m_interface->DeleteSwapChain(m_swapChain);

    m_synchronization->Destroy(m_device);
    m_interface->DeleteSynchronization(m_synchronization);

    m_device->Destroy();
    m_interface->DeleteDevice(m_device);

    m_surface->Destroy(m_instance);
    m_interface->DeleteSurface(m_surface);

    m_instance->Destroy();
    m_interface->DeleteContext(m_instance);

    m_renderer->Destroy();
    m_interface->DeleteRenderer(m_renderer);

    DestroyInput(); // Destroy InputManager before the window as it relies on the window's context
    DestroyWindow(); // Then destroy the window
}


void Engine::Window()
{
    m_window = m_interface->InstantiateWindow();
    m_window->Initialize("Luminous", true);
}


void Engine::Input()
{
    m_inputManager = m_interface->InstantiateInputManager();
    m_inputManager->Initialize(m_window);
}


void Engine::PreRender()
{
    m_instance = m_interface->InstantiateContext();
    m_instance->Create();

    m_surface = m_interface->InstantiateSurface();
    m_surface->Create(m_instance, m_window);

    m_device = m_interface->InstantiateDevice();
    m_device->Create(m_instance, m_surface);

    m_swapChain = m_interface->InstantiateSwapChain();
    m_swapChain->Create(m_window, m_device, m_surface);

    m_multiSampling = m_interface->InstantiateMultiSampling();
    m_multiSampling->SetSampleCount(m_device, SamplingCount::MSAA_SAMPLECOUNT_4);
    m_multiSampling->Create(m_device, m_swapChain);

    m_renderPassManager = m_interface->InstantiateRenderPassManager();
    m_renderPassManager->Create(m_swapChain, m_device, false); // Create Main Render Pass
    m_renderPassManager->Create(m_swapChain, m_device, true); // Create Editor Render Pass

    m_descriptorSetLayout = m_interface->InstantiateDescriptorSetLayout();
    m_descriptorSetLayout->Create(m_device);

    m_pipeline = m_interface->InstantiatePipeline();
    m_pipeline->Create(m_device, m_renderPassManager->GetRenderPassAt(0), m_descriptorSetLayout);

    m_commandPool = m_interface->InstantiateCommandPool();
    m_commandPool->Create(m_device, m_surface);

    m_editorCommandPool = m_interface->InstantiateCommandPool();

    m_depthResource = m_interface->InstantiateDepthResource();
    m_depthResource->Create(m_device, m_swapChain, m_renderPassManager->GetRenderPasses()[0]);

    m_frameBufferManager = m_interface->InstantiateFrameBufferManager();
    m_frameBufferManager->Create(m_device, m_swapChain, m_renderPassManager->GetRenderPasses()[0], m_depthResource, m_multiSampling, false); // Create Renderer Frame Buffer
    m_frameBufferManager->Create(m_device, m_swapChain, m_renderPassManager->GetRenderPasses()[1], m_depthResource, m_multiSampling, true); // Create Editor Frame Buffer

    m_buffer = m_interface->InstantiateBuffer();
    m_buffer->Create(m_device);

    m_descriptor = m_interface->InstantiateDescriptor();
    m_descriptor->Create(m_device, m_descriptorSetLayout, m_buffer);

    m_commandBuffer = m_interface->InstantiateCommandBuffer();
    m_commandBuffer->Create(m_device, m_commandPool);

    m_synchronization = m_interface->InstantiateSynchronization();
    m_synchronization->Create(m_device);

    m_renderer = m_interface->InstantiateRenderer();
    m_renderer->Create(m_device, m_swapChain);
    m_renderer->SetViewportSize(m_swapChain->GetSize().x, m_swapChain->GetSize().y);
    m_renderer->CastVulkan()->CreateViewportImage(m_device, m_swapChain);
}

void Engine::InitPhysics()
{
    constexpr PhysicsSystem::Settings l_settings{}; // Init physics system with default settings
    m_physicsSystem->Init(l_settings);
}

void Engine::DestroyWindow() const
{
    m_window->Destroy();
    m_interface->DeleteWindow(m_window);
}

void Engine::DestroyInput() const { m_interface->DeleteInputManager(m_inputManager); }
