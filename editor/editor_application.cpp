//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "editor_application.h"
#include "engine.h"
#include "camera.h"
#include "glfw_window.h"

#include "view/game_view.h"

namespace vox {
namespace editor {
EditorApplication::EditorApplication():
GraphicsApplication(),
_panelsManager(_canvas) {
}

bool EditorApplication::prepare(Engine &engine) {
    GraphicsApplication::prepare(engine);
    
    _gui = std::make_unique<::vox::ui::UIManager>(static_cast<GlfwWindow*>(&engine.window())->handle(), _renderContext.get());
    _sceneManager = std::make_unique<SceneManager>(_device);
    auto scene = _sceneManager->currentScene();
    
    _particleManager = std::make_unique<ParticleManager>(_device);
    _lightManager = std::make_unique<LightManager>(scene);
    {
        auto extent = engine.window().extent();
        auto factor = engine.window().contentScaleFactor();
        scene->updateSize(extent.width, extent.height, factor * extent.width, factor * extent.height);
        // _mainCamera->resize(extent.width, extent.height, factor * extent.width, factor * extent.height);
    }
    _lightManager->setCamera(_mainCamera);
    _shadowManager = std::make_unique<ShadowManager>(scene, _mainCamera);
    
    // Create a render pass descriptor for thelighting and composition pass
    // Whatever rendered in the final pass needs to be stored so it can be displayed
    _renderPassDescriptor.colorAttachmentCount = 1;
    _renderPassDescriptor.colorAttachments = &_colorAttachments;
    
    _colorAttachments.storeOp = wgpu::StoreOp::Store;
    _colorAttachments.loadOp = wgpu::LoadOp::Clear;
    auto& color = scene->background.solidColor;
    _colorAttachments.clearValue = wgpu::Color{color.r, color.g, color.b, color.a};
    
    return true;
}

void EditorApplication::setupUI() {
    PanelWindowSettings settings;
    settings.closable = true;
    settings.collapsable = true;
    settings.dockable = true;
    
    _panelsManager.createPanel<ui::GameView>("Game View", true, settings,
                                             _renderContext.get(), _sceneManager->currentScene());
}

void EditorApplication::update(float delta_time) {
    GraphicsApplication::update(delta_time);
    _sceneManager->currentScene()->update(delta_time);
    
    wgpu::CommandEncoder commandEncoder = _device.CreateCommandEncoder();
    updateGPUTask(commandEncoder);
    
    // Render the gui
    _colorAttachments.view = _renderContext->currentDrawableTexture();
    wgpu::RenderPassEncoder encoder = commandEncoder.BeginRenderPass(&_renderPassDescriptor);
    encoder.PushDebugGroup("GUI Rendering");
    _gui->render(encoder);
    encoder.PopDebugGroup();
    encoder.End();

    // Finalize rendering here & push the command buffer to the GPU
    wgpu::CommandBuffer commands = commandEncoder.Finish();
    _device.GetQueue().Submit(1, &commands);
    _renderContext->present();
}

void EditorApplication::updateGPUTask(wgpu::CommandEncoder& commandEncoder) {
    _shadowManager->draw(commandEncoder);
    _lightManager->draw(commandEncoder);
    _particleManager->draw(commandEncoder);
}

bool EditorApplication::resize(uint32_t win_width, uint32_t win_height,
                                uint32_t fb_width, uint32_t fb_height) {
    GraphicsApplication::resize(win_width, win_height, fb_width, fb_height);

    _sceneManager->currentScene()->updateSize(win_width, win_height, fb_width, fb_height);
    // _mainCamera->resize(win_width, win_height, fb_width, fb_height);
    return true;
}

void EditorApplication::inputEvent(const InputEvent &inputEvent) {
    GraphicsApplication::inputEvent(inputEvent);
    _sceneManager->currentScene()->updateInputEvent(inputEvent);
}

}
}