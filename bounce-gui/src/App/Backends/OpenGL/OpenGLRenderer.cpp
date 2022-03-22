//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLRenderer.h"
#include "App/Renderer/Mesh.h"
#include "App/Renderer/Line.h"
#include "App/Core/Logging.h"

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

#include <map>

namespace Bounce::Gui {

    typedef std::map<std::shared_ptr<Material>, std::vector<RenderItem*>> BatchMap;
    typedef std::pair<std::shared_ptr<Material>, std::vector<RenderItem*>> BatchPair;

    void OpenGLRenderer::Flush() {
        // Clear background
        // TODO(tvallentin) Needs to be extracted to an OpenGL RendererAPI)
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BatchMap batchMap;

        // Pseudo "batch", grouping render items by elements
        // to avoid binding the same material multiple times
        for (const auto &item : s_renderItems) {
            auto material = item->GetMaterial();
            if ( batchMap.find(material) != batchMap.end() ) {
                batchMap[material].push_back(item);
            } else {
                batchMap.insert(BatchPair(material, std::vector<RenderItem*>{item}));
            }
        }

        // Iterating over groups of items by material, binding the material once
        // and rendering each item
        for (const auto &batch : batchMap) {
            BNC_DEBUG("Binding material");
            // Binding first material
            batch.first->Bind();

            BNC_DEBUG("Setting view proj matrix : %s",
                      glm::to_string(s_sceneData.viewProjectionMatrix).c_str());
            batch.first->GetShader()->SetMat4("u_viewProjMatrix",
                                              s_sceneData.viewProjectionMatrix);

            for (const auto &item: batch.second) {
                switch (item->GetType()) {
                    case DrawType::Mesh: {
                        const Mesh *mesh = (Mesh *) item;
                        mesh->Bind();
                        glDrawElements(GL_TRIANGLES,
                                       (int) mesh->GetElementCount(),
                                       GL_UNSIGNED_INT,
                                       nullptr);
                        break;
                    }

                    case DrawType::Line: {
                        const Line *line = (Line *) item;
                        line->Bind();
                        glDrawElements(GL_LINES,
                                       (int) line->GetElementCount(),
                                       GL_UNSIGNED_INT,
                                       nullptr);
                        break;
                    }

                    case DrawType::None:
                        continue;
                }
            }
        }
    }

    void OpenGLRenderer::SetRenderHints(const RenderHints &hints) {
        BNC_INFO("hints.displayMode : %d", hints.displayMode);
        switch (hints.displayMode) {
            case DisplayMode::SmoothShaded:
            case DisplayMode::HardShaded:    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
            case DisplayMode::Wireframe:     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        }

        switch (hints.lightingMode) {
            case LightingMode::DefaultLighting:
            case LightingMode::SceneLighting:
            case LightingMode::FlatLighting:     break;
        }

        s_renderHints = hints;
    }

}
