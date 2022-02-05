//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef wgsl_blend_shape_vert_hpp
#define wgsl_blend_shape_vert_hpp

#include "shaderlib/wgsl_encoder.h"

namespace vox {
class WGSLBlendShapeVert {
public:
    WGSLBlendShapeVert(const std::string& input, const std::string& output);
    
    void operator()(std::string& source, const ShaderMacroCollection& macros);
    
private:
    const std::string _input;
    const std::string _output;
};

}

#endif /* wgsl_blend_shape_vert_hpp */
