#version 450

#include "base/common.h"

layout(location = Position) in vec3 POSITION;

#ifdef HAS_UV
    layout(location = UV_0) in vec2 TEXCOORD_0;
#endif

//----------------------------------------------------------------------------------------------------------------------
#ifdef HAS_SKIN
    layout(location = Joints_0) in vec4 JOINTS_0;
    layout(location = Weights_0) in vec4 WEIGHTS_0;

    #ifdef HAS_JOINT_TEXTURE
        layout(set = 0, binding = 2) uniform sampler2D u_jointSampler;
        layout(set = 0, binding = 3) uniform u_jointCount {
            float joint_count;
        };

        mat4 getJointMatrix(sampler2D smp, float index) {
            float base = index / joint_count;
            float hf = 0.5 / joint_count;
            float v = base + hf;

            vec4 m0 = texture2D(smp, vec2(0.125, v));
            vec4 m1 = texture2D(smp, vec2(0.375, v));
            vec4 m2 = texture2D(smp, vec2(0.625, v));
            vec4 m3 = texture2D(smp, vec2(0.875, v));

            return mat4(m0, m1, m2, m3);
        }
    #else
        layout(set = 0, binding = 4) uniform u_jointMatrix {
            mat4 joint_matrix[JOINTS_NUM];
        };
    #endif
#endif

//----------------------------------------------------------------------------------------------------------------------
#ifdef HAS_VERTEXCOLOR
    layout(location = Color_0) in vec4 COLOR_0;
#endif

layout(set = 0, binding = 5) uniform u_cameraData {
    mat4 view_mat;
    mat4 proj_mat;
    mat4 vp_mat;
    mat4 view_inv_mat;
    mat4 proj_inv_mat;
    vec3 camera_pos;
};

layout(set = 0, binding = 6) uniform u_rendererData {
    mat4 local_mat;
    mat4 model_mat;
    mat4 normal_mat;
};

layout(set = 0, binding = 7) uniform u_tilingOffset {
    vec4 tiling_offset;
};

//----------------------------------------------------------------------------------------------------------------------
#ifndef OMIT_NORMAL
    #ifdef HAS_NORMAL
        layout(location = Normal) in vec3 NORMAL;
    #endif

    #ifdef HAS_TANGENT
        layout(location = Tangent) in vec4 TANGENT;
    #endif
#endif

//----------------------------------------------------------------------------------------------------------------------
#ifdef HAS_BLENDSHAPE
    #ifndef HAS_BLENDSHAPE_TEXTURE
        layout(location = 10) in vec3 POSITION_BS0;
        layout(location = 11) in vec3 POSITION_BS1;
        layout(location = 12) in vec3 POSITION_BS2;
        layout(location = 13) in vec3 POSITION_BS3;

        #ifdef HAS_BLENDSHAPE_NORMAL
            layout(location = 16) in vec3 NORMAL_BS0;
            layout(location = 17) in vec3 NORMAL_BS1;
            layout(location = 18) in vec3 NORMAL_BS2;
            layout(location = 19) in vec3 NORMAL_BS3;
        #endif

        #ifdef HAS_BLENDSHAPE_TANGENT
            layout(location = 20) in vec3 TANGENT_BS0;
            layout(location = 21) in vec3 TANGENT_BS1;
            layout(location = 22) in vec3 TANGENT_BS2;
            layout(location = 23) in vec3 TANGENT_BS3;
        #endif
    #endif
    layout(set = 0, binding = 8) uniform u_blendShapeWeights {
        float blend_shape_weights[4];
    };
#endif

//----------------------------------------------------------------------------------------------------------------------
layout (location = 0) out vec2 v_uv;

void main() {
    vec4 position = vec4(POSITION, 1.0);

    #ifdef HAS_BLENDSHAPE
        #ifdef HAS_BLENDSHAPE_TEXTURE

        #else
            position.xyz += POSITION_BS0 * blend_shape_weights[0];
            position.xyz += POSITION_BS1 * blend_shape_weights[1];
            position.xyz += POSITION_BS2 * blend_shape_weights[2];
            position.xyz += POSITION_BS3 * blend_shape_weights[3];

            #ifndef OMIT_NORMAL
                #if defined(HAS_NORMAL) && defined(HAS_BLENDSHAPE_NORMAL)
                    normal.xyz += NORMAL_BS0 * blend_shape_weights[0];
                    normal.xyz += NORMAL_BS1 * blend_shape_weights[1];
                    normal.xyz += NORMAL_BS2 * blend_shape_weights[2];
                    normal.xyz += NORMAL_BS3 * blend_shape_weights[3];
                #endif

                #if defined(HAS_TANGENT) && defined(NORMAL_TEXTURE) && defined(HAS_BLENDSHAPE_TANGENT)
                    tangent.xyz += TANGENT_BS0 * blend_shape_weights[0];
                    tangent.xyz += TANGENT_BS1 * blend_shape_weights[1];
                    tangent.xyz += TANGENT_BS2 * blend_shape_weights[2];
                    tangent.xyz += TANGENT_BS3 * blend_shape_weights[3];
                #endif
            #endif
        #endif
    #endif

    //------------------------------------------------------------------------------------------------------------------
    #ifdef HAS_SKIN
        #ifdef HAS_JOINT_TEXTURE
            mat4 skinMatrix =
            WEIGHTS_0.x * getJointMatrix(jointSampler, JOINTS_0.x) +
            WEIGHTS_0.y * getJointMatrix(jointSampler, JOINTS_0.y) +
            WEIGHTS_0.z * getJointMatrix(jointSampler, JOINTS_0.z) +
            WEIGHTS_0.w * getJointMatrix(jointSampler, JOINTS_0.w);
        #else
            mat4 skinMatrix =
            WEIGHTS_0.x * joint_matrix[int(JOINTS_0.x)] +
            WEIGHTS_0.y * joint_matrix[int(JOINTS_0.y)] +
            WEIGHTS_0.z * joint_matrix[int(JOINTS_0.z)] +
            WEIGHTS_0.w * joint_matrix[int(JOINTS_0.w)];
        #endif

        position = skinMatrix * position;

        #if defined(HAS_NORMAL) && !defined(OMIT_NORMAL)
            normal = vec4(skinMatrix * vec4(normal, 0.0)).xyz;
            #if defined(HAS_TANGENT) && defined(NORMAL_TEXTURE)
                tangent.xyz = vec4(skinMatrix * vec4(tangent.xyz, 0.0)).xyz;
            #endif
        #endif
    #endif

    //------------------------------------------------------------------------------------------------------------------
    #ifdef HAS_UV
        v_uv = TEXCOORD_0;
    #else
        // may need this calculate normal
        v_uv = vec2(0., 0.);
    #endif

    #ifdef NEED_TILINGOFFSET
        v_uv = v_uv * tiling_offset.xy + tiling_offset.zw;
    #endif

    //------------------------------------------------------------------------------------------------------------------
    gl_Position = vp_mat * model_mat * position;
}