//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "apps/physics_samples/constraints/swing_twist_constraint_app.h"

#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/GroupFilterTable.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>

#include "apps/physics_samples/physics_utils.h"
#include "vox.render/camera.h"
#include "vox.render/entity.h"
#include "vox.toolkit/controls/orbit_control.h"
#include "vox.toolkit/physics_debugger/physics_debug_subpass.h"

namespace vox {
namespace {
class ShowScript : public Script {
public:
    physics_debugger::PhysicsDebugSubpass* _debugger{nullptr};
    JPH::BodyManager::DrawSettings inSettings;

    explicit ShowScript(Entity* entity) : Script(entity) { inSettings.mDrawShape = true; }

    void onPhysicsUpdate() override {
        _debugger->Clear();
        PhysicsManager::GetSingleton().drawBodies(inSettings, _debugger);
        PhysicsManager::GetSingleton().drawConstraints(_debugger);
    }
};

}  // namespace

bool PhysicsSwingTwistConstraintApp::prepare(Platform& platform) {
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

void PhysicsSwingTwistConstraintApp::loadScene() {
    auto scene = _sceneManager->currentScene();
    scene->ambientLight()->setDiffuseSolidColor(Color(1, 1, 1));
    auto rootEntity = scene->createRootEntity();

    auto cameraEntity = rootEntity->createChild();
    cameraEntity->transform->setPosition(30, 30, 30);
    cameraEntity->transform->lookAt(Point3F(0, 0, 0));
    _mainCamera = cameraEntity->addComponent<Camera>();
    cameraEntity->addComponent<control::OrbitControl>();

    JPH::BodyInterface& body_interface = PhysicsManager::GetSingleton().getBodyInterface();
    {
        PhysicsUtils::createFloor(body_interface);

        float half_cylinder_height = 1.5f;

        const int cChainLength = 10;

        // Build a collision group filter that disables collision between adjacent bodies
        Ref<GroupFilterTable> group_filter = new GroupFilterTable(cChainLength);
        for (CollisionGroup::SubGroupID i = 0; i < cChainLength - 1; ++i) group_filter->DisableCollision(i, i + 1);

        Body* prev = nullptr;
        Quat rotation = Quat::sRotation(Vec3::sAxisZ(), 0.5f * JPH_PI);
        Vec3 position(0, 25, 0);
        for (int i = 0; i < cChainLength; ++i) {
            position += Vec3(2.0f * half_cylinder_height, 0, 0);

            Body& segment = *body_interface.CreateBody(
                    BodyCreationSettings(new CapsuleShape(half_cylinder_height, 0.5f), position,
                                         Quat::sRotation(Vec3::sAxisX(), 0.25f * JPH_PI * i) * rotation,
                                         i == 0 ? EMotionType::Static : EMotionType::Dynamic,
                                         i == 0 ? PhysicsManager::Layers::NON_MOVING : PhysicsManager::Layers::MOVING));
            segment.SetCollisionGroup(CollisionGroup(group_filter, 0, CollisionGroup::SubGroupID(i)));
            body_interface.AddBody(segment.GetID(), EActivation::Activate);
            if (i != 0) segment.SetAllowSleeping(false);

            if (prev != nullptr) {
                Ref<SwingTwistConstraintSettings> settings = new SwingTwistConstraintSettings;
                settings->mPosition1 = settings->mPosition2 = position + Vec3(-half_cylinder_height, 0, 0);
                settings->mTwistAxis1 = settings->mTwistAxis2 = Vec3::sAxisX();
                settings->mPlaneAxis1 = settings->mPlaneAxis2 = Vec3::sAxisY();
                settings->mNormalHalfConeAngle = sNormalHalfConeAngle;
                settings->mPlaneHalfConeAngle = sPlaneHalfConeAngle;
                settings->mTwistMinAngle = sTwistMinAngle;
                settings->mTwistMaxAngle = sTwistMaxAngle;

                Ref<SwingTwistConstraint> constraint =
                        static_cast<SwingTwistConstraint*>(settings->Create(*prev, segment));
                PhysicsManager::GetSingleton().addConstraint(constraint);
                mConstraints.push_back(constraint);
            }

            prev = &segment;
        }
    }
    scene->play();
}

}  // namespace vox
