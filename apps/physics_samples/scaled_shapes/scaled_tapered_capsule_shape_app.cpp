//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "apps/physics_samples/scaled_shapes/scaled_tapered_capsule_shape_app.h"

#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Collision/Shape/TaperedCapsuleShape.h>

#include "apps/physics_samples/physics_utils.h"
#include "vox.render/camera.h"
#include "vox.render/entity.h"
#include "vox.toolkit/controls/orbit_control.h"
#include "vox.toolkit/physics_debugger/physics_debug_subpass.h"

namespace vox {
namespace {
class ShowScript : public Script {
public:
    physics_debugger::PhysicsDebugSubpass *_debugger{nullptr};
    JPH::BodyManager::DrawSettings inSettings;

    explicit ShowScript(Entity *entity) : Script(entity) { inSettings.mDrawShape = true; }

    void onPhysicsUpdate() override {
        _debugger->Clear();
        PhysicsManager::GetSingleton().drawBodies(inSettings, _debugger);
    }
};

}  // namespace

bool PhysicsScaledTaperedCapsuleShapeApp::prepare(Platform &platform) {
    ForwardApplication::prepare(platform);

    auto scene = _sceneManager->currentScene();
    auto rootEntity = scene->getRootEntity();
    auto showScript = rootEntity->addComponent<ShowScript>();

    auto debugger = std::make_unique<physics_debugger::PhysicsDebugSubpass>(
            _renderContext.get(), _depthStencilTextureFormat, scene, _mainCamera);
    showScript->_debugger = debugger.get();
    _renderPass->addSubpass(std::move(debugger));

    return true;
}

void PhysicsScaledTaperedCapsuleShapeApp::loadScene() {
    auto scene = _sceneManager->currentScene();
    scene->ambientLight()->setDiffuseSolidColor(Color(1, 1, 1));
    auto rootEntity = scene->createRootEntity();

    auto cameraEntity = rootEntity->createChild();
    cameraEntity->transform->setPosition(30, 30, 30);
    cameraEntity->transform->lookAt(Point3F(0, 0, 0));
    _mainCamera = cameraEntity->addComponent<Camera>();
    cameraEntity->addComponent<control::OrbitControl>();

    JPH::BodyInterface &body_interface = PhysicsManager::GetSingleton().getBodyInterface();
    {
        PhysicsUtils::createFloor(body_interface);

        // Create tapered capsule
        RefConst<ShapeSettings> tapered_capsule_shape = new TaperedCapsuleShapeSettings(2.0f, 0.75f, 1.25f);

        // Original shape
        Body &body1 = *body_interface.CreateBody(BodyCreationSettings(tapered_capsule_shape, Vec3(-20, 10, 0),
                                                                      Quat::sIdentity(), EMotionType::Dynamic,
                                                                      PhysicsManager::Layers::MOVING));
        body_interface.AddBody(body1.GetID(), EActivation::Activate);

        // Uniformly scaled shape < 1
        Body &body2 = *body_interface.CreateBody(BodyCreationSettings(
                new ScaledShapeSettings(tapered_capsule_shape, Vec3::sReplicate(0.25f)), Vec3(-10, 10, 0),
                Quat::sIdentity(), EMotionType::Dynamic, PhysicsManager::Layers::MOVING));
        body_interface.AddBody(body2.GetID(), EActivation::Activate);

        // Uniformly scaled shape > 1
        Body &body3 = *body_interface.CreateBody(BodyCreationSettings(
                new ScaledShapeSettings(tapered_capsule_shape, Vec3::sReplicate(2.0f)), Vec3(0, 10, 0),
                Quat::sIdentity(), EMotionType::Dynamic, PhysicsManager::Layers::MOVING));
        body_interface.AddBody(body3.GetID(), EActivation::Activate);

        // Flipped in 2 axis
        Body &body4 = *body_interface.CreateBody(BodyCreationSettings(
                new ScaledShapeSettings(tapered_capsule_shape, Vec3(-1.5f, -1.5f, 1.5f)), Vec3(10, 10, 0),
                Quat::sIdentity(), EMotionType::Dynamic, PhysicsManager::Layers::MOVING));
        body_interface.AddBody(body4.GetID(), EActivation::Activate);

        // Inside out
        Body &body5 = *body_interface.CreateBody(BodyCreationSettings(
                new ScaledShapeSettings(tapered_capsule_shape, Vec3::sReplicate(-0.75f)), Vec3(20, 10, 0),
                Quat::sIdentity(), EMotionType::Dynamic, PhysicsManager::Layers::MOVING));
        body_interface.AddBody(body5.GetID(), EActivation::Activate);
    }
    scene->play();
}

}  // namespace vox
