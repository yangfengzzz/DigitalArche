//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "depth_state.h"

namespace vox {
void DepthState::platformApply(wgpu::DepthStencilState *depthStencil) {
    if (enabled && depthStencil) {
        // apply compare func.
        depthStencil->depthCompare = compareFunction;

        // apply write enabled.
        depthStencil->depthWriteEnabled = writeEnabled;
    }
}

}  // namespace vox
