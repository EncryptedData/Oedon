//
// Created by Russell Johnson on 9/6/22.
//

#include "BlueprintView.h"
#include "BlueprintViewModel.h"

#include "nodes/CubeNode.h"
#include "nodes/MeshTransformNode.h"
#include "nodes/ConstantNode.h"
#include "nodes/LineLerper.h"

#include <algorithm>
#include <imgui_node_editor.h>

# define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace ed = ax::NodeEditor;

namespace Oedon::Editor
{
    // Function from imgui-node-editor github and was slightly modified
    void DrawIcon(ImDrawList* drawList, const ImVec2& a, const ImVec2& b, IconType type, bool filled, ImU32 color, ImU32 innerColor)
    {
        auto rect           = ImRect(a, b);
        auto rect_x         = rect.Min.x;
        auto rect_y         = rect.Min.y;
        auto rect_w         = rect.Max.x - rect.Min.x;
        auto rect_h         = rect.Max.y - rect.Min.y;
        auto rect_center_x  = (rect.Min.x + rect.Max.x) * 0.5f;
        auto rect_center_y  = (rect.Min.y + rect.Max.y) * 0.5f;
        auto rect_center    = ImVec2(rect_center_x, rect_center_y);
        const auto outline_scale  = rect_w / 24.0f;
        const auto extra_segments = static_cast<int>(2 * outline_scale); // for full circle

        if (type == IconType::Flow)
        {
            const auto origin_scale = rect_w / 24.0f;

            const auto offset_x  = 1.0f * origin_scale;
            const auto offset_y  = 0.0f * origin_scale;
            const auto margin     = (filled ? 2.0f : 2.0f) * origin_scale;
            const auto rounding   = 0.1f * origin_scale;
            const auto tip_round  = 0.7f; // percentage of triangle edge (for tip)
            //const auto edge_round = 0.7f; // percentage of triangle edge (for corner)
            const auto canvas = ImRect(
                    rect.Min.x + margin + offset_x,
                    rect.Min.y + margin + offset_y,
                    rect.Max.x - margin + offset_x,
                    rect.Max.y - margin + offset_y);
            const auto canvas_x = canvas.Min.x;
            const auto canvas_y = canvas.Min.y;
            const auto canvas_w = canvas.Max.x - canvas.Min.x;
            const auto canvas_h = canvas.Max.y - canvas.Min.y;

            const auto left   = canvas_x + canvas_w            * 0.5f * 0.3f;
            const auto right  = canvas_x + canvas_w - canvas_w * 0.5f * 0.3f;
            const auto top    = canvas_y + canvas_h            * 0.5f * 0.2f;
            const auto bottom = canvas_y + canvas_h - canvas_h * 0.5f * 0.2f;
            const auto center_y = (top + bottom) * 0.5f;
            //const auto angle = AX_PI * 0.5f * 0.5f * 0.5f;

            const auto tip_top    = ImVec2(canvas_x + canvas_w * 0.5f, top);
            const auto tip_right  = ImVec2(right, center_y);
            const auto tip_bottom = ImVec2(canvas_x + canvas_w * 0.5f, bottom);

            drawList->PathLineTo(ImVec2(left, top) + ImVec2(0, rounding));
            drawList->PathBezierCubicCurveTo(
                    ImVec2(left, top),
                    ImVec2(left, top),
                    ImVec2(left, top) + ImVec2(rounding, 0));
            drawList->PathLineTo(tip_top);
            drawList->PathLineTo(tip_top + (tip_right - tip_top) * tip_round);
            drawList->PathBezierCubicCurveTo(
                    tip_right,
                    tip_right,
                    tip_bottom + (tip_right - tip_bottom) * tip_round);
            drawList->PathLineTo(tip_bottom);
            drawList->PathLineTo(ImVec2(left, bottom) + ImVec2(rounding, 0));
            drawList->PathBezierCubicCurveTo(
                    ImVec2(left, bottom),
                    ImVec2(left, bottom),
                    ImVec2(left, bottom) - ImVec2(0, rounding));

            if (!filled)
            {
                if (innerColor & 0xFF000000)
                    drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size, innerColor);

                drawList->PathStroke(color, true, 2.0f * outline_scale);
            }
            else
                drawList->PathFillConvex(color);
        }
        else
        {
            auto triangleStart = rect_center_x + 0.32f * rect_w;

            auto rect_offset = -static_cast<int>(rect_w * 0.25f * 0.25f);

            rect.Min.x    += rect_offset;
            rect.Max.x    += rect_offset;
            rect_x        += rect_offset;
            rect_center_x += rect_offset * 0.5f;
            rect_center.x += rect_offset * 0.5f;

            if (type == IconType::Circle)
            {
                const auto c = rect_center;

                if (!filled)
                {
                    const auto r = 0.5f * rect_w / 2.0f - 0.5f;

                    if (innerColor & 0xFF000000)
                        drawList->AddCircleFilled(c, r, innerColor, 12 + extra_segments);
                    drawList->AddCircle(c, r, color, 12 + extra_segments, 2.0f * outline_scale);
                }
                else
                {
                    drawList->AddCircleFilled(c, 0.5f * rect_w / 2.0f, color, 12 + extra_segments);
                }
            }

            if (type == IconType::Square)
            {
                if (filled)
                {
                    const auto r  = 0.5f * rect_w / 2.0f;
                    const auto p0 = rect_center - ImVec2(r, r);
                    const auto p1 = rect_center + ImVec2(r, r);

#if IMGUI_VERSION_NUM > 18101
                    drawList->AddRectFilled(p0, p1, color, 0, ImDrawFlags_RoundCornersAll);
#else
                    drawList->AddRectFilled(p0, p1, color, 0, 15);
#endif
                }
                else
                {
                    const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                    const auto p0 = rect_center - ImVec2(r, r);
                    const auto p1 = rect_center + ImVec2(r, r);

                    if (innerColor & 0xFF000000)
                    {
#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRectFilled(p0, p1, innerColor, 0, ImDrawFlags_RoundCornersAll);
#else
                        drawList->AddRectFilled(p0, p1, innerColor, 0, 15);
#endif
                    }

#if IMGUI_VERSION_NUM > 18101
                    drawList->AddRect(p0, p1, color, 0, ImDrawFlags_RoundCornersAll, 2.0f * outline_scale);
#else
                    drawList->AddRect(p0, p1, color, 0, 15, 2.0f * outline_scale);
#endif
                }
            }

            if (type == IconType::Grid)
            {
                const auto r = 0.5f * rect_w / 2.0f;
                const auto w = ceilf(r / 3.0f);

                const auto baseTl = ImVec2(floorf(rect_center_x - w * 2.5f), floorf(rect_center_y - w * 2.5f));
                const auto baseBr = ImVec2(floorf(baseTl.x + w), floorf(baseTl.y + w));

                auto tl = baseTl;
                auto br = baseBr;
                for (int i = 0; i < 3; ++i)
                {
                    tl.x = baseTl.x;
                    br.x = baseBr.x;
                    drawList->AddRectFilled(tl, br, color);
                    tl.x += w * 2;
                    br.x += w * 2;
                    if (i != 1 || filled)
                        drawList->AddRectFilled(tl, br, color);
                    tl.x += w * 2;
                    br.x += w * 2;
                    drawList->AddRectFilled(tl, br, color);

                    tl.y += w * 2;
                    br.y += w * 2;
                }

                triangleStart = br.x + w + 1.0f / 24.0f * rect_w;
            }

            if (type == IconType::RoundSquare)
            {
                if (filled)
                {
                    const auto r  = 0.5f * rect_w / 2.0f;
                    const auto cr = r * 0.5f;
                    const auto p0 = rect_center - ImVec2(r, r);
                    const auto p1 = rect_center + ImVec2(r, r);

#if IMGUI_VERSION_NUM > 18101
                    drawList->AddRectFilled(p0, p1, color, cr, ImDrawFlags_RoundCornersAll);
#else
                    drawList->AddRectFilled(p0, p1, color, cr, 15);
#endif
                }
                else
                {
                    const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                    const auto cr = r * 0.5f;
                    const auto p0 = rect_center - ImVec2(r, r);
                    const auto p1 = rect_center + ImVec2(r, r);

                    if (innerColor & 0xFF000000)
                    {
#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRectFilled(p0, p1, innerColor, cr, ImDrawFlags_RoundCornersAll);
#else
                        drawList->AddRectFilled(p0, p1, innerColor, cr, 15);
#endif
                    }

#if IMGUI_VERSION_NUM > 18101
                    drawList->AddRect(p0, p1, color, cr, ImDrawFlags_RoundCornersAll, 2.0f * outline_scale);
#else
                    drawList->AddRect(p0, p1, color, cr, 15, 2.0f * outline_scale);
#endif
                }
            }
            else if (type == IconType::Diamond)
            {
                if (filled)
                {
                    const auto r = 0.607f * rect_w / 2.0f;
                    const auto c = rect_center;

                    drawList->PathLineTo(c + ImVec2( 0, -r));
                    drawList->PathLineTo(c + ImVec2( r,  0));
                    drawList->PathLineTo(c + ImVec2( 0,  r));
                    drawList->PathLineTo(c + ImVec2(-r,  0));
                    drawList->PathFillConvex(color);
                }
                else
                {
                    const auto r = 0.607f * rect_w / 2.0f - 0.5f;
                    const auto c = rect_center;

                    drawList->PathLineTo(c + ImVec2( 0, -r));
                    drawList->PathLineTo(c + ImVec2( r,  0));
                    drawList->PathLineTo(c + ImVec2( 0,  r));
                    drawList->PathLineTo(c + ImVec2(-r,  0));

                    if (innerColor & 0xFF000000)
                        drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size, innerColor);

                    drawList->PathStroke(color, true, 2.0f * outline_scale);
                }
            }
            else
            {
                const auto triangleTip = triangleStart + rect_w * (0.45f - 0.32f);

                drawList->AddTriangleFilled(
                        ImVec2(ceilf(triangleTip), rect_y + rect_h * 0.5f),
                        ImVec2(triangleStart, rect_center_y + 0.15f * rect_h),
                        ImVec2(triangleStart, rect_center_y - 0.15f * rect_h),
                        color);
            }
        }
    }

    static ImColor GetPinColor(PinCompat compat)
    {
        switch (compat)
        {
            case PinCompat::Mesh:
                return ImColor(255, 154, 34, 255);
            case PinCompat::Points:
                return ImColor(248, 255, 1, 255);
            default:
                return ImColor(255, 255, 255, 255);
        }
    }

    static void DrawIconShim(IconType type, PinCompat compat, bool isPinConnected, ImVec2 size = ImVec2(18.0f, 18.0f))
    {
        if(ImGui::IsRectVisible(size))
        {
            auto cursorPos = ImGui::GetCursorScreenPos();
            auto drawList = ImGui::GetWindowDrawList();

            DrawIcon(drawList, cursorPos, cursorPos + size, IconType::Circle, isPinConnected, GetPinColor(compat), ImColor(0.0f, 0.0f, 0.0f, 0.0f));
        }
        ImGui::Dummy(size);
    }

    static void DrawPin(const std::shared_ptr<PinVM>& pin)
    {
        const IconType icon = Circle;
        bool isConnected = !pin->connections.empty();

        ed::BeginPin(pin->id, pin->type == PinType::Input ? ax::NodeEditor::PinKind::Input : ax::NodeEditor::PinKind::Output);



        if(pin->type == PinType::Input)
        {
            ed::PinPivotAlignment(ImVec2(0.0f, 0.5f));
            ed::PinPivotSize(ImVec2(0.0f, 0.0f));

            DrawIconShim(icon, pin->compat, isConnected);
            ImGui::SameLine();
        }

        ImGui::Text(pin->label.c_str());

        if(pin->type == PinType::Output)
        {
            ed::PinPivotAlignment(ImVec2(1.0f, 0.5f));
            ed::PinPivotSize(ImVec2(0.0f, 0.0f));

            ImGui::SameLine();
            DrawIconShim(icon, pin->compat, isConnected);
        }

        ed::EndPin();
    }

    static void DrawNode(const std::shared_ptr<NodeVM>& node)
    {
        ed::BeginNode(node->id);

        ImGui::Text(node->name.c_str());

        size_t inputCount = node->inputPins.size();
        size_t outputCount = node->outputPins.size();

        size_t largestCount = std::max(inputCount, outputCount);

        for(size_t i = 0; i < largestCount; i++)
        {
            if(i < inputCount)
            {
                DrawPin(node->inputPins[i]);
            }
            else
            {
                ImGui::Text("   ");
            }

            if(i < outputCount)
            {
                ImGui::SameLine();
                DrawPin(node->outputPins[i]);
            }
        }

        ed::EndNode();
    }

    static void DrawConnection(const std::shared_ptr<ConnectionVM>& connection)
    {
        int linkId = connection->id;
        int inputPinId = connection->input->id;
        int outputPinId = connection->output->id;

        ed::Link(linkId, inputPinId, outputPinId, GetPinColor(connection->output->compat));
    }

    static void HandleConnectionCreation(BlueprintViewModel* vm)
    {
        if(ed::BeginCreate())
        {
            ed::PinId inputPinId;
            ed::PinId outputPinId;

            if(ed::QueryNewLink(&inputPinId, &outputPinId))
            {
                auto a = vm->FindPinWithId(outputPinId.Get());
                auto b = vm->FindPinWithId(inputPinId.Get());


                if(a && b &&
                    a->compat == b->compat &&
                    a->type != b->type &&
                    a->node != b->node)
                {
                    if(ed::AcceptNewItem())
                    {
                        std::shared_ptr<PinVM> inputPin;
                        std::shared_ptr<PinVM> outputPin;

                        if(a->type == PinType::Input)
                        {
                            inputPin = a;
                            outputPin = b;
                        }
                        else
                        {
                            inputPin = b;
                            outputPin = a;
                        }

                        vm->BreakPinConnections(inputPin);
                        // Don't break the connection on output only add

                        auto connection = vm->CreateConnection(inputPin, outputPin);
                        inputPin->connections.push_back(connection);
                        outputPin->connections.push_back(connection);

                        DrawConnection(connection);
                    }
                }
            }
        }
        ed::EndCreate();
    }

    static void HandleConnectionDeletion(BlueprintViewModel* vm)
    {
        if(ed::BeginDelete())
        {
            ed::LinkId deletedLinkId;
            while(ed::QueryDeletedLink(&deletedLinkId))
            {
                if(ed::AcceptDeletedItem())
                {
                    auto connection = vm->FindConnectionWithId(deletedLinkId.Get());
                    vm->DestroyConnection(connection);
                }
            }
        }
        ed::EndDelete();
    }

    static void HandleNodeDeletion(BlueprintViewModel* vm)
    {
        if(ed::BeginDelete())
        {
            ed::NodeId deletedNodeId;

            while(ed::QueryDeletedNode(&deletedNodeId))
            {
                if(ed::AcceptDeletedItem())
                {
                    auto node = vm->FindNodeWithId(deletedNodeId.Get());

                    vm->DestroyNode(node);
                }
            }
        }
    }

    static void HandleSelectedNodeEvent(BlueprintViewModel* vm)
    {
        if(ed::GetSelectedNodes(nullptr, 0) == 0)
        {
            vm->selectedNode.reset();
            return;
        }

        for(const auto& node : vm->nodes)
        {
            if(ed::IsNodeSelected(node->id))
            {
                if(!vm->selectedNode || vm->selectedNode != node->id)
                {
                    vm->selectedNode = node->id;

                    vm->ProcessNodes(node);

                    NodeSelectionChangedEvent event;
                    event.node = node;

                    vm->eventDispatcher->Fire(event);
                }
            }
        }
    }

    void BlueprintView::View(BlueprintViewModel* vm)
    {
        const char* nodes[] = {
                "Cube",
                "Mesh Transform",
                "Constant Value",
                "Line Lerper",
        };

        ImGui::Text("Node: ");
        ImGui::SameLine();
        ImGui::Combo("##CreateNode", &_createNodeSelected, nodes, sizeof(nodes) / sizeof(nodes[0]));

        ImGui::SameLine();
        if(ImGui::Button("Create Node"))
        {
            switch (_createNodeSelected)
            {
                case 0:
                {
                    vm->BuildNode<CubeNode>();
                    break;
                }
                case 1:
                {
                    vm->BuildNode<MeshTransformNode>();
                    break;
                }
                case 2:
                {
                    vm->BuildNode<ConstantNode>();
                    break;
                }
                case 3:
                {
                    vm->BuildNode<LineLerper>();
                    break;
                }
            }
        }

        ed::SetCurrentEditor(vm->editorContext);
        ed::Begin("BlueprintEditor");

        for(auto& node : vm->nodes)
        {
            DrawNode(node);
        }

        for(auto& connection : vm->connections)
        {
            DrawConnection(connection);
        }

        HandleConnectionCreation(vm);
        HandleConnectionDeletion(vm);

        HandleNodeDeletion(vm);

        HandleSelectedNodeEvent(vm);

        ed::End();
        ed::SetCurrentEditor(nullptr);
    }
}
