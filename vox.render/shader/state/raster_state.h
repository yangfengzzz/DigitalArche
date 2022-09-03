//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef raster_state_hpp
#define raster_state_hpp

#include <webgpu/webgpu_cpp.h>

namespace vox {
/**
 * Raster state.
 */
struct RasterState {
    /** Specifies whether or not front- and/or back-facing polygons can be culled. */
    wgpu::CullMode cullMode = wgpu::CullMode::Front;
    /** The multiplier by which an implementation-specific value is multiplied with to create a constant depth offset.
     */
    int32_t depthBias = 0;
    /** The scale factor for the variable depth offset for each polygon. */
    float depthBiasSlopeScale = 1.0;
    float depthBiasClamp = 0.01;

    void apply(wgpu::PrimitiveState& primitive, wgpu::DepthStencilState* depthStencil, bool frontFaceInvert) {
        platformApply(primitive, depthStencil, frontFaceInvert);
    }

    void platformApply(wgpu::PrimitiveState& primitive, wgpu::DepthStencilState* depthStencil, bool frontFaceInvert);
};

}  // namespace vox

#endif /* raster_state_hpp */
