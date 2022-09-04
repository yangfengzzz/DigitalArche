//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include "vox.render/rendering/subpass.h"
#include "vox.render/texture/sampled_texturecube.h"

namespace vox {
class SkyboxSubpass : public Subpass {
public:
    SkyboxSubpass(RenderContext* renderContext,
                  wgpu::TextureFormat depthStencilTextureFormat,
                  Scene* scene,
                  Camera* camera);

    void prepare() override;

    void draw(wgpu::RenderPassEncoder& passEncoder) override;

public:
    void createSphere(float radius);

    void createCuboid();

    /**
     * Texture cube map of the sky box material.
     */
    SampledTextureCubePtr textureCubeMap();

    void setTextureCubeMap(SampledTextureCubePtr v);

private:
    enum class SkyBoxType { Cuboid, Sphere };
    SkyBoxType _type;
    ModelMeshPtr _mesh{nullptr};
    SampledTextureCubePtr _cubeMap{nullptr};
    Buffer _vpMatrix;

    ShaderSource vert_shader_;
    ShaderSource frag_shader_;

    wgpu::RenderPipelineDescriptor _forwardPipelineDescriptor;
    wgpu::DepthStencilState _depthStencil;
    wgpu::FragmentState _fragment;
    wgpu::ColorTargetState _colorTargetState;

    std::vector<wgpu::BindGroupLayoutEntry> _bindGroupLayoutEntry;
    wgpu::BindGroupLayoutDescriptor _bindGroupLayoutDescriptor;
    wgpu::BindGroupLayout _bindGroupLayout;

    std::vector<wgpu::BindGroupEntry> _bindGroupEntries{};
    wgpu::BindGroupDescriptor _bindGroupDescriptor;

    wgpu::PipelineLayoutDescriptor _pipelineLayoutDescriptor;
    wgpu::PipelineLayout _pipelineLayout;

    wgpu::RenderPipeline _renderPipeline;

    wgpu::TextureFormat _depthStencilTextureFormat;
};

}  // namespace vox