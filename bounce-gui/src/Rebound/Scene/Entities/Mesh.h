//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_MESH_H
#define RBND_MESH_H

#include "Rebound/Scene/Entities/Xform.h"

namespace Rebound {

    class Mesh : public Xform {
    public:

        ENTITY_TYPE_FROM_BASES(Mesh, Type::Find<Xform>())

        std::vector<glm::vec3> GetPositions();
        void SetPositions(const std::vector<glm::vec3> &positions);

        std::vector<glm::vec3> GetNormals();
        void SetNormals(const std::vector<glm::vec3> &normals);

        std::vector<uint32_t> GetIndices();
        void SetIndices(const std::vector<uint32_t> &indices);

        static std::vector<AttributeSpec> GetDefaultAttributes();

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
