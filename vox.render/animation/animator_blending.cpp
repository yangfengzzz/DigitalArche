//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "vox.render/animation/animator_blending.h"
#include "vox.simd_math/soa_transform.h"

namespace vox {
AnimatorBlending::AnimatorBlending(const animation::Skeleton& skeleton) : _skeleton(skeleton) {
    _blended_locals.resize(_skeleton.num_soa_joints());
    _blend_job.output = make_span(_blended_locals);
    _blend_job.rest_pose = _skeleton.joint_rest_poses();
}

AnimatorClip& AnimatorBlending::addAnimatorClip(const char* _filename) {
    _clips.emplace_back(_filename);
    AnimatorClip& clip = _clips.back();
    clip._setNumSoaJoints(_skeleton.num_soa_joints());
    clip._setNumJoints(_skeleton.num_joints());
    return clip;
}

void AnimatorBlending::update(float dt) {
    _layers.clear();
    _additive_layers.clear();

    for (auto & clip : _clips) {
        clip.update(dt);

        animation::BlendingJob::Layer layer{};
        layer.transform = make_span(clip._locals);
        if (clip.blendMode == AnimatorClip::BlendMode::Normal) {
            _layers.push_back(layer);
        } else {
            _additive_layers.push_back(layer);
        }
    }
    _blend_job.layers = make_span(_layers);
    _blend_job.additive_layers = make_span(_additive_layers);
    _blend_job.Run();
}

float AnimatorBlending::threshold() const { return _blend_job.threshold; }

void AnimatorBlending::setThreshold(float value) { _blend_job.threshold = value; }

}  // namespace vox