//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLRenderer.h"
#include "Rebound/Renderer/Hop/Mesh.h"
#include "Rebound/Renderer/Hop/Line.h"
#include "Rebound/Core/Logging.h"

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

#include <map>

namespace Hop {

    typedef std::map<std::shared_ptr<Material>, std::vector<DrawItem*>> BatchMap;
    typedef std::pair<std::shared_ptr<Material>, std::vector<DrawItem*>> BatchPair;

    void OpenGLRenderer::Flush() {
        // Clear background
        // TODO(tvallentin) Needs to be extracted to an OpenGL RendererAPI)
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BatchMap batchMap;

        // Pseudo "batch", grouping render items by elements
        // to avoid binding the same material multiple times
        for (const auto &item : s_DrawItems) {
            auto material = item->GetMaterial();
            if ( batchMap.find(material) != batchMap.end() ) {
                batchMap[material].push_back(item);
            } else {
                batchMap.insert(BatchPair(material, std::vector<DrawItem*>{item}));
            }
        }

        // Iterating over groups of items by material, binding the material once
        // and rendering each item
        for (const auto &batch : batchMap) {
            HOP_DEBUG("Binding material");
            // Binding first material
            batch.first->Bind();

            HOP_DEBUG("Setting view proj matrix : %s",
                      glm::to_string(s_sceneData.viewProjectionMatrix).c_str());
            batch.first->GetShader()->SetMat4("u_viewProjMatrix",
                                              s_sceneData.viewProjectionMatrix);

            for (const auto &item: batch.second) {
                switch (item->GetType()) {
                    case DrawType::Mesh: {
                        const DrawItems::Mesh *mesh = (DrawItems::Mesh *) item;
                        mesh->Bind();
                        glDrawElements(GL_TRIANGLES,
                                       (int) mesh->GetElementCount(),
                                       GL_UNSIGNED_INT,
                                       nullptr);
                        break;
                    }

                    case DrawType::Line: {
                        const DrawItems::Line *line = (DrawItems::Line *) item;
                        line->Bind();
                        glDrawElements(GL_LINE_STRIP,
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
        HOP_INFO("hints.displayMode : %d", hints.displayMode);
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

    void OpenGLRenderer::Render(RenderIndex *index, Rebound::Camera *camera) {

    }

}
