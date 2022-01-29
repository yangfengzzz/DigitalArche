//
//  internal_macro_name.h
//  DigitalArche
//
//  Created by 杨丰 on 2022/1/29.
//

#ifndef internal_macro_name_h
#define internal_macro_name_h

namespace vox {
// int have no verb, other will use:
// HAS_ : Resouce
// OMMIT_ : Omit Resouce
// NEED_ : Shader Operation
// IS_ : Shader control flow
// _COUNT: type int constant
enum MacroName {
    HAS_UV = 0,
    HAS_NORMAL,
    HAS_TANGENT,
    HAS_VERTEXCOLOR,
    
    // Blend Shape
    HAS_BLENDSHAPE,
    HAS_BLENDSHAPE_TEXTURE,
    HAS_BLENDSHAPE_NORMAL,
    HAS_BLENDSHAPE_TANGENT,
    
    // Skin
    HAS_SKIN,
    HAS_JOINT_TEXTURE,
    JOINTS_COUNT,
    
    // Material
    NEED_ALPHA_CUTOFF,
    NEED_WORLDPOS,
    NEED_TILINGOFFSET,
    HAS_DIFFUSE_TEXTURE,
    HAS_SPECULAR_TEXTURE,
    HAS_EMISSIVE_TEXTURE,
    HAS_NORMAL_TEXTURE,
    OMIT_NORMAL,
    HAS_BASE_TEXTURE,
    HAS_BASE_COLORMAP,
    HAS_EMISSIVEMAP,
    HAS_OCCLUSIONMAP,
    HAS_SPECULARGLOSSINESSMAP,
    HAS_METALROUGHNESSMAP,
    IS_METALLIC_WORKFLOW,
    
    // Light
    DIRECT_LIGHT_COUNT,
    POINT_LIGHT_COUNT,
    SPOT_LIGHT_COUNT,
    
    // Enviroment
    HAS_SH,
    HAS_SPECULAR_ENV,
    HAS_DIFFUSE_ENV,
    
    // Particle Render
    HAS_PARTICLE_TEXTURE,
    NEED_ROTATE_TO_VELOCITY,
    NEED_USE_ORIGIN_COLOR,
    NEED_SCALE_BY_LIFE_TIME,
    NEED_FADE_IN,
    NEED_FADE_OUT,
    IS_2D,
    
    // Shadow
    SHADOW_MAP_COUNT,
    CUBE_SHADOW_MAP_COUNT,

    TOTAL_COUNT
};

}

#endif /* internal_macro_name_h */