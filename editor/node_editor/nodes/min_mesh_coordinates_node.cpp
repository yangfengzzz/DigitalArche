//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#include "min_mesh_coordinates_node.h"
#include "cpu_node_editor.h"

namespace vox {
namespace editor {
MinMeshCoordinatesNode::MinMeshCoordinatesNode() {
    headerColor = ImColor(VALUE_NODE_COLOR);
    outputPins.push_back(new NodeEditorPin(NodeEditorPinType::Output));
    outputPins.push_back(new NodeEditorPin(NodeEditorPinType::Output));
    outputPins.push_back(new NodeEditorPin(NodeEditorPinType::Output));
}

NodeOutput MinMeshCoordinatesNode::evaluate(NodeInputParam input, NodeEditorPin *pin) {
    int id = pin->id;
    
    if (outputPins[0]->id == id)
        return NodeOutput({input.minX});
    else if (outputPins[1]->id == id)
        return NodeOutput({input.minY});
    else if (outputPins[2]->id == id)
        return NodeOutput({input.minZ});
    return NodeOutput();
}

void MinMeshCoordinatesNode::onRender() {
    drawHeader("Minimum Mesh Coordinates");
    ImGui::Dummy(ImVec2(150, 10));
    ImGui::SameLine();
    ImGui::Text("Min X");
    outputPins[0]->render();
    ImGui::Dummy(ImVec2(150, 10));
    ImGui::SameLine();
    ImGui::Text("Min Y");
    outputPins[1]->render();
    ImGui::Dummy(ImVec2(150, 10));
    ImGui::SameLine();
    ImGui::Text("Min Z");
    outputPins[2]->render();
}

}
}
