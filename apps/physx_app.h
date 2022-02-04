//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef physx_app_hpp
#define physx_app_hpp

#include "forward_application.h"

namespace vox {
class PhysXApp : public ForwardApplication {
public:
    void loadScene(uint32_t width, uint32_t height) override;
};
 
}

#endif /* physx_app_hpp */