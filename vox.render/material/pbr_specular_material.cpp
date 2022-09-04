//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "vox.render/material/pbr_specular_material.h"

#include "vox.render/shader/internal_variant_name.h"
#include "vox.render/shader/shader_manager.h"

namespace vox {
const Color& PBRSpecularMaterial::specularColor() const { return _pbrSpecularData.specularColor; }

void PBRSpecularMaterial::setSpecularColor(const Color& newValue) {
    _pbrSpecularData.specularColor = newValue;
    shaderData.setData(PBRSpecularMaterial::_pbrSpecularProp, _pbrSpecularData);
}

float PBRSpecularMaterial::glossiness() const { return _pbrSpecularData.glossiness; }

void PBRSpecularMaterial::setGlossiness(float newValue) {
    _pbrSpecularData.glossiness = newValue;
    shaderData.setData(PBRSpecularMaterial::_pbrSpecularProp, _pbrSpecularData);
}

SampledTexture2DPtr PBRSpecularMaterial::specularGlossinessTexture() { return _specularGlossinessTexture; }

void PBRSpecularMaterial::setSpecularGlossinessTexture(const SampledTexture2DPtr& newValue) {
    _specularGlossinessTexture = newValue;
    shaderData.setSampledTexture(PBRSpecularMaterial::_specularGlossinessTextureProp,
                                 PBRSpecularMaterial::_specularGlossinessSamplerProp, newValue);
    if (newValue) {
        shaderData.addDefine(HAS_SPECULARGLOSSINESSMAP);
    } else {
        shaderData.removeDefine(HAS_SPECULARGLOSSINESSMAP);
    }
}

PBRSpecularMaterial::PBRSpecularMaterial(wgpu::Device& device, const std::string& name)
    : PBRBaseMaterial(device, name),
      _pbrSpecularProp("u_pbrSpecularData"),
      _specularGlossinessTextureProp("_specularGlossinessTexture"),
      _specularGlossinessSamplerProp("_specularGlossinessSampler") {
    vertex_source_ = ShaderManager::GetSingleton().LoadShader("base/blinn-phong.vert");
    fragment_source_ = ShaderManager::GetSingleton().LoadShader("base/pbr.frag");
    shaderData.setData(PBRSpecularMaterial::_pbrSpecularProp, _pbrSpecularData);
}

}  // namespace vox
