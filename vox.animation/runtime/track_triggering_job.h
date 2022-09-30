//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#pragma once

#include "vox.animation/runtime/export.h"
#include "vox.base/macros.h"
#include <cassert>

namespace vox::animation {

class FloatTrack;

// Track edge triggering job implementation. Edge triggering wording refers to
// signal processing, where a signal edge is a transition from low to high or
// from high to low. It is called an "edge" because of the square wave which
// represents a signal has edges at those points. A rising edge is the
// transition from low to high, a falling edge is from high to low.
// TrackTriggeringJob detects when track curve crosses a threshold value,
// triggering dated events that can be processed as state changes.
// Only FloatTrack is supported, because comparing to a threshold for other
// track types isn't possible.
// The job execution actually performs a lazy evaluation of edges. It builds an
// iterator that will process the next edge on each call to ++ operator.
struct VOX_ANIMATION_DLL TrackTriggeringJob {
    TrackTriggeringJob();

    // Validates job parameters.
    [[nodiscard]] bool Validate() const;

    // Validates and executes job. Execution is lazy. Iterator operator ++ is
    // actually doing the processing work.
    [[nodiscard]] bool Run() const;

    // Input range. 0 is the beginning of the track, 1 is the end.
    // from and to can be of any sign, any order, and any range. The job will
    // perform accordingly:
    // - if difference between from and to is greater than 1, the iterator will
    // loop multiple times on the track.
    // - if from is greater than to, then the track is processed backward (rising
    // edges in forward become falling ones).
    float from;
    float to;

    // Edge detection threshold value.
    // A rising edge is detected as soon as the track value becomes greater than
    // the threshold.
    // A falling edge is detected as soon as the track value becomes smaller or
    // equal than the threshold.
    float threshold;

    // Track to sample.
    const FloatTrack* track;

    // Job output iterator.
    class Iterator;
    Iterator* iterator;

    // Returns an iterator referring to the past-the-end element. It should only
    // be used to test if iterator loop reached the end (using operator !=), and
    // shall not be dereferenced.
    [[nodiscard]] Iterator end() const;

    // Structure of an edge as detected by the job.
    struct Edge {
        float ratio;  // Ratio at which track value crossed threshold.
        bool rising;  // true is edge is rising (getting higher than threshold).
    };
};

// Iterator implementation. Calls to ++ operator will compute the next edge. It
// should be compared (using operator !=) to job's end iterator to test if the
// last edge has been reached.
class VOX_ANIMATION_DLL TrackTriggeringJob::Iterator {
public:
    Iterator() : job_(nullptr), outer_(0.f), inner_(0) {}

    // Evaluate next edge.
    // Calling this function on an end iterator results in an assertion in debug,
    // an undefined behavior otherwise.
    const Iterator& operator++();
    Iterator operator++(int) {
        Iterator prev = *this;
        ++*this;
        return prev;
    }

    // Compare with other iterators.
    bool operator!=(const Iterator& _it) const {
        return inner_ != _it.inner_ || outer_ != _it.outer_ || job_ != _it.job_;
    }
    bool operator==(const Iterator& _it) const {
        return job_ == _it.job_ && outer_ == _it.outer_ && inner_ == _it.inner_;
    }

    // Dereferencing operators.
    const Edge& operator*() const {
        assert(*this != job_->end() && "Can't dereference end iterator.");
        return edge_;
    }
    const Edge* operator->() const {
        assert(*this != job_->end() && "Can't dereference end iterator.");
        return &edge_;
    }

private:
    friend struct TrackTriggeringJob;

    // Constructors used by the job.
    explicit Iterator(const TrackTriggeringJob* _job);
    struct End {};
    Iterator(const TrackTriggeringJob* _job, End)
        : job_(_job), outer_(0.f), inner_(-2) {  // Can never be reached while looping.
    }

    // Job this iterator works on.
    const TrackTriggeringJob* job_;

    // Current value of the outer loop, aka a ratio cursor between from and to.
    float outer_;

    // Current value of the inner loop, aka a key frame index.
    ptrdiff_t inner_;

    // Latest evaluated edge.
    Edge edge_{};
};

// end() job function inline implementation.
inline TrackTriggeringJob::Iterator TrackTriggeringJob::end() const { return Iterator(this, Iterator::End()); }
}  // namespace vox::animation
