//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "buffer_mesh.h"

namespace vox {
size_t BufferMesh::instanceCount() {
    return _instanceCount;
}

void BufferMesh::setInstanceCount(size_t newValue) {
    _instanceCount = newValue;
}

const std::vector<std::optional<Buffer>>& BufferMesh::vertexBufferBindings() {
    return _vertexBufferBindings;
}

const std::optional<IndexBufferBinding>& BufferMesh::indexBufferBinding() {
    return _indexBufferBinding;
}

const std::vector<wgpu::VertexBufferLayout>& BufferMesh::vertexBufferLayouts() {
    return _vertexBufferLayouts;
}

void BufferMesh::setVertexLayouts(const std::vector<wgpu::VertexBufferLayout>& layouts) {
    _setVertexLayouts(layouts);
}

void BufferMesh::setVertexBufferBinding(const Buffer& buffer, size_t index) {
    if (_vertexBufferBindings.size() <= index) {
        _vertexBufferBindings.reserve(index + 1);
        for (size_t i = _vertexBufferBindings.size(); i < index; i++) {
            _vertexBufferBindings.push_back(std::nullopt);
        }
    }
    _setVertexBufferBinding(index, buffer);
}

void BufferMesh::setVertexBufferBindings(const std::vector<Buffer>& vertexBufferBindings, size_t firstIndex) {
    auto count = vertexBufferBindings.size();
    auto needLength = firstIndex + count;
    if (_vertexBufferBindings.size() < needLength) {
        _vertexBufferBindings.reserve(needLength);
        for (size_t i = _vertexBufferBindings.size(); i < needLength; i++) {
            _vertexBufferBindings.push_back(std::nullopt);
        }
    }
    for (size_t i = 0; i < count; i++) {
        _setVertexBufferBinding(firstIndex + i, vertexBufferBindings[i]);
    }
}

void BufferMesh::setIndexBufferBinding(const Buffer& buffer, wgpu::IndexFormat format) {
    _setIndexBufferBinding(IndexBufferBinding(buffer, format));
}

void BufferMesh::setIndexBufferBinding(std::optional<IndexBufferBinding> bufferBinding) {
    _setIndexBufferBinding(bufferBinding);
}

}
