//
//  sampled_texture2D.hpp
//  vox.render
//
//  Created by 杨丰 on 2022/1/27.
//

#ifndef sampled_texture2D_hpp
#define sampled_texture2D_hpp

#include "sampled_texture.h"

namespace vox {
class SampledTexture2D : public SampledTexture {
public:
    /**
     * Create Texture2D.
     * @param device - Define the engine to use to render this texture
     * @param width - Texture width
     * @param height - Texture height
     * @param format - Texture format. default  `TextureFormat.R8G8B8A8`
     * @param mipmap - Whether to use multi-level texture
     */
    SampledTexture2D(wgpu::Device& device,
                     uint32_t width,
                     uint32_t height,
                     wgpu::TextureFormat format = wgpu::TextureFormat::RGBA8Sint,
                     bool mipmap = true);
};

}

#endif /* sampled_texture2D_hpp */
