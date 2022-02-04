//
//  collider_shape.hpp
//  vox.render
//
//  Created by 杨丰 on 2021/12/2.
//

#ifndef collider_shape_hpp
#define collider_shape_hpp

#include "../physics.h"
#include "transform3.h"
#include <vector>

namespace vox {
namespace physics {
class ColliderShape {
public:
    ColliderShape();
    
    Collider *collider();
    
public:
    void setLocalPose(const Transform3F &pose);
    
    Transform3F localPose() const;
    
    void setPosition(const Vector3F &pos);
    
    Vector3F position() const;
    
    virtual void setWorldScale(const Vector3F &scale) = 0;
    
public:
    void setMaterial(PxMaterial *materials);
    
    PxMaterial *material();
    
public:
    void setQueryFilterData(const PxFilterData &data);
    
    PxFilterData queryFilterData();
    
    uint32_t uniqueID();
    
public:
    void setFlag(PxShapeFlag::Enum flag, bool value);
    
    void setFlags(PxShapeFlags inFlags);
    
    PxShapeFlags getFlags() const;
    
    bool trigger();
    
    void setTrigger(bool isTrigger);
    
    bool sceneQuery();
    
    void setSceneQuery(bool isQuery);
    
protected:
    friend class Collider;
    
    PxShape *_nativeShape = nullptr;
    std::shared_ptr<PxGeometry> _nativeGeometry = nullptr;
    PxMaterial *_nativeMaterial = nullptr;
    
    Collider *_collider = nullptr;
    
    Vector3F _scale = Vector3F(1, 1, 1);
    Transform3F _pose;
    static constexpr float halfSqrt = 0.70710678118655;
};

}
}
#endif /* collider_shape_hpp */