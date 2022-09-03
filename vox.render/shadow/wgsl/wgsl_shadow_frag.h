//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include "vox.render/shaderlib/wgsl_encoder.h"

namespace vox {
class WGSLShadowFrag {
public:
    WGSLShadowFrag();

    void operator()(WGSLEncoder& encoder, const ShaderMacroCollection& macros);

    void operator()(std::string& source, const ShaderMacroCollection& macros);
};

}  // namespace vox