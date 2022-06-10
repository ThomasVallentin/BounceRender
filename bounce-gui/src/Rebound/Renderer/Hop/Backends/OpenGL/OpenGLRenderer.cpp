//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLRenderer.h"

#include "Rebound/Renderer/Hop/Material.h"
#include "Rebound/Renderer/Hop/DrawItem.h"
#include "Rebound/Renderer/Hop/Mesh.h"
#include "Rebound/Renderer/Hop/Line.h"

#include "Rebound/Renderer/Camera.h"

#include "Rebound/Core/Logging.h"

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

#include <unordered_map>


namespace Hop {

    typedef std::unordered_map<std::shared_ptr<Material>, std::vector<std::shared_ptr<DrawItem>>> BatchMap;
    typedef std::pair<std::shared_ptr<Material>, std::vector<std::shared_ptr<DrawItem>>> BatchPair;

    void OpenGLRenderer::Render(RenderDelegate *delegate, Rebound::Camera *camera) {
        // Clear background
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BatchMap batchMap;

        // TODO: Pseudo "batch", grouping render items by elements
        //       to avoid binding the same material multiple times.
        //       This need to be extracted to a separate class that handle Batches properly and
        //       manage batch invalidation when the Scene changes.
        Rebound::RenderScene* renderScene = delegate->GetRenderScene();
        for (const auto &it : renderScene->GetRenderIndex()) {

            for (const auto& item : it.second->GetDrawItems()) {
                std::shared_ptr<Rebound::Material> material = renderScene->GetMaterial(item->GetMaterialHandle());
                if (!material) {
                    material = delegate->GetDefaultMaterial();
                }

                // Casting the Rebound objects to Hop objects
                auto hopItem = std::dynamic_pointer_cast<DrawItem>(item);
                auto hopMaterial = std::dynamic_pointer_cast<Material>(material);

                if ( batchMap.find(hopMaterial) != batchMap.end() ) {
                    batchMap[hopMaterial].push_back(hopItem);
                } else {
                    batchMap.insert(BatchPair(hopMaterial,
                                              std::vector<std::shared_ptr<DrawItem>>{hopItem}));
                }
            }
        }

        // Send the render hints to OpenGL
        ApplyRenderHints(delegate->GetRenderHints());

        // Iterating over groups of items by material, binding the material once
        // and rendering each item
        for (const auto &batch : batchMap) {
            RBND_DEBUG("Binding material");
            // Binding first material
            batch.first->Bind();

            RBND_DEBUG("Setting view proj matrix : %s",
                      glm::to_string(camera->GetViewProjectionMatrix()).c_str());
            batch.first->GetShader()->SetMat4("u_viewProjMatrix",
                                              camera->GetViewProjectionMatrix());

            for (const auto &item: batch.second) {
                GLenum drawMode;

                switch (item->GetType()) {
                    case DrawType::Mesh: {
                        drawMode = GL_TRIANGLES; break;
                    }
                    case DrawType::Line: {
                        drawMode = GL_LINE_STRIP; break;
                    }
                    case DrawType::None:
                        continue;
                }

                item->Bind();
                glDrawElements(drawMode,
                               (int) item->GetElementCount(),
                               GL_UNSIGNED_INT,
                               nullptr);
            }
        }
    }

    void OpenGLRenderer::ApplyRenderHints(const RenderHints &hints) {
        switch (hints.displayMode) {
            case DisplayMode::SmoothShaded:
            case DisplayMode::HardShaded:    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
            case DisplayMode::Wireframe:     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        }

        // TODO: Apply hints.lightingMode
    }

}
