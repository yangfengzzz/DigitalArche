//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "particle_material.h"

namespace vox {
ParticleMaterial::ParticleMaterial(wgpu::Device& device):
BaseMaterial(device, Shader::find("particle")),
_particleDataProp(Shader::createProperty("u_particleData", ShaderDataGroup::Material)) {
    shaderData.setData(_particleDataProp, _particleData);

    setIsTransparent(true);
    setBlendMode(BlendMode::Additive);
}

float ParticleMaterial::minParticleSize() const {
    return _particleData.minParticleSize;
}

void ParticleMaterial::setMinParticleSize(float size) {
    _particleData.minParticleSize = size;
    shaderData.setData(_particleDataProp, _particleData);
}

float ParticleMaterial::maxParticleSize() const {
    return _particleData.maxParticleSize;
}

void ParticleMaterial::setMaxParticleSize(float size) {
    _particleData.maxParticleSize = size;
    shaderData.setData(_particleDataProp, _particleData);
}

ParticleMaterial::ColorMode ParticleMaterial::colorMode() const {
    return _particleData.colorMode;
}

void ParticleMaterial::setColorMode(ColorMode mode) {
    _particleData.colorMode = mode;
    shaderData.setData(_particleDataProp, _particleData);
}

Vector3F ParticleMaterial::birthGradient() const {
    return _particleData.birthGradient;
}

void ParticleMaterial::setBirthGradient(const Vector3F& gradient) {
    _particleData.birthGradient = gradient;
    shaderData.setData(_particleDataProp, _particleData);
}

Vector3F ParticleMaterial::deathGradient() const {
    return _particleData.deathGradient;
}

void ParticleMaterial::setDeathGradient(const Vector3F& gradient) {
    _particleData.deathGradient = gradient;
    shaderData.setData(_particleDataProp, _particleData);
}

float ParticleMaterial::fadeCoefficient() const {
    return _particleData.fadeCoefficient;
}

void ParticleMaterial::setFadeCoefficient(float coeff) {
    _particleData.fadeCoefficient = coeff;
    shaderData.setData(_particleDataProp, _particleData);
}

bool ParticleMaterial::debugDraw() const {
    return _particleData.debugDraw;
}

void ParticleMaterial::setDebugDraw(bool flag) {
    _particleData.debugDraw = flag;
    shaderData.setData(_particleDataProp, _particleData);
}

}