//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLRenderer.h"
#include "App/Renderer/Mesh.h"
#include "App/Renderer/Line.h"
#include "App/Logging.h"

#include <glad/glad.h>

#include <map>

namespace Bounce::Gui {

    typedef std::map<std::shared_ptr<Material>, std::vector<RenderItem*>> BatchMap;
    typedef std::pair<std::shared_ptr<Material>, std::vector<RenderItem*>> BatchPair;

    void OpenGLRenderer::Flush() {
        // Clear background
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);

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
            // Binding first material
            batch.first->Bind();

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

}
