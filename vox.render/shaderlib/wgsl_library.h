//
//  wgsl_library.hpp
//  vox.render
//
//  Created by 杨丰 on 2022/1/28.
//

#ifndef wgsl_library_hpp
#define wgsl_library_hpp

#include <functional>
#include "shader/shader_macro_collection.h"

namespace vox {
class WGSL;

enum class UniformType {
    Vec2f32,
    Vec2i32,
    Vec2u32,
    Vec3f32,
    Vec3i32,
    Vec3u32,
    Vec4f32,
    Vec4i32,
    Vec4u32,
    Mat2x2f32,
    Mat3x2f32,
    Mat4x2f32,
    Mat2x3f32,
    Mat3x3f32,
    Mat4x3f32,
    Mat2x4f32,
    Mat3x4f32,
    Mat4x4f32,
};

std::string uniformTypeToString(UniformType type);


class WGSLUniformBinding {
public:
    WGSLUniformBinding(WGSL* source, const std::string& name, UniformType type,
                       uint32_t group = 0);
    
    void operator()();
    
private:
    std::string _name;
    UniformType _type;
    uint32_t _group;
    
    WGSL* _source{nullptr};
};

class WGSLPatchTest {
public:
    WGSLPatchTest(WGSL* source);
    
    void operator()(const ShaderMacroCollection& macros);
    
private:
    WGSLUniformBinding _uPMatirx;
    WGSLUniformBinding _uMVMatrix;
    
    WGSL* _source{nullptr};
};


}

#endif /* wgsl_library_hpp */