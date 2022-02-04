//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "wgsl_pbr_frag.h"
#include <fmt/core.h>

namespace vox {
WGSLPbrFrag::WGSLPbrFrag(const std::string& input, const std::string& output):
_input(input),
_output(output) {
}

void WGSLPbrFrag::operator()(std::string& source, const ShaderMacroCollection& macros) {
    source += fmt::format("var geometry = GeometricContext({}.v_pos, getNormal(), normalize(u_cameraPos - {}.v_pos));\n", _input, _input);
    source += "var material = getPhysicalMaterial(u_baseColor, u_metal, u_roughness, u_specularColor, u_glossiness, u_alphaCutoff);\n";
    source += "var reflectedLight = ReflectedLight( vec3<f32>(0.0, 0.0, 0.0), vec3<f32>(0.0, 0.0, 0.0), vec3<f32>(0.0, 0.0, 0.0), vec3<f32>(0.0, 0.0, 0.0) );\n";
    source += "var dotNV = saturate( dot( geometry.normal, geometry.viewDir ) );\n";
    
    // Direct Light
    source += "addTotalDirectRadiance(geometry, material, reflectedLight);\n";
    
    // IBL diffuse
    if (macros.contains(HAS_SH)) {
        source += "var irradiance = getLightProbeIrradiance(u_env_sh, geometry.normal);\n";
        source += "irradiance *= u_envMapLight.diffuseIntensity;\n";
    } else {
        source += "var irradiance = u_envMapLight.diffuse * u_envMapLight.diffuseIntensity;\n";
        source += "irradiance *= PI;\n";
    }
    source += "reflectedLight.indirectDiffuse += irradiance * BRDF_Diffuse_Lambert( material.diffuseColor );\n";
    
    // IBL specular
    source += "var radiance = getLightProbeRadiance( geometry, material.roughness, int(u_envMapLight.mipMapLevel), u_envMapLight.specularIntensity);\n";
    source += "reflectedLight.indirectSpecular += radiance * envBRDFApprox(material.specularColor, material.roughness, dotNV );\n";

    // Occlusion
    if (macros.contains(HAS_OCCLUSIONMAP)) {
        source += fmt::format("var ambientOcclusion = (textureSample(u_occlusionTexture, u_occlusionSampler, {}.v_uv).r - 1.0) * u_occlusionStrength + 1.0;\n", _input);
        source += "reflectedLight.indirectDiffuse = reflectedLight.indirectDiffuse * ambientOcclusion;\n";
        if (macros.contains(HAS_SPECULAR_ENV)) {
            source += "reflectedLight.indirectSpecular = reflectedLight.indirectSpecular * computeSpecularOcclusion(ambientOcclusion, material.roughness, dotNV);\n";
        }
    }
    
    // Emissive
    source += "var emissiveRadiance = u_emissiveColor;\n";
    if (macros.contains(HAS_EMISSIVEMAP)) {
        source += fmt::format("var emissiveColor = textureSample(u_emissiveTexture, u_emissiveSampler, {}.v_uv);\n", _input);
        source += "emissiveRadiance *= emissiveColor.rgb;\n";
    }
    
    // Total
    source += "var totalRadiance =    reflectedLight.directDiffuse +\n";
    source += "                        reflectedLight.indirectDiffuse +\n";
    source += "                        reflectedLight.directSpecular +\n";
    source += "                        reflectedLight.indirectSpecular +\n";
    source += "                        emissiveRadiance;\n";
}

}