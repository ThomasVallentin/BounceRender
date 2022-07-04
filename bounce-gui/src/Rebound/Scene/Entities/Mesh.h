//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_MESH_H
#define RBND_MESH_H

#include "Rebound/Scene/Entities/Xform.h"

namespace Rebound {

    class Mesh : public Xform {
    public:

        ENTITY_TYPE_FROM_BASES(Mesh, Xform)

        bool GetPositions(std::vector<glm::vec3> &positions);
        void SetPositions(const std::vector<glm::vec3> &positions);

        bool GetNormals(std::vector<glm::vec3> &normals);
        void SetNormals(const std::vector<glm::vec3> &normals);

        bool GetIndices(std::vector<uint32_t> &indices);
        void SetIndices(const std::vector<uint32_t> &indices);

    protected:
        Mesh() = default;

        Mesh(const EntityDataHandle &dataHandle, Scene *scene)
                : Xform(dataHandle, scene) {}

    private:
        friend Scene;
        friend Entity;

    };

}


#endif //RBND_MESH_H
