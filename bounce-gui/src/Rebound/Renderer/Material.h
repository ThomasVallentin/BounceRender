//
// Created by Thomas Vallentin on 22/05/2022.
//

#ifndef RBND_MATERIAL_H
#define RBND_MATERIAL_H

#include <cstdint>

namespace Rebound {

    typedef uint32_t MaterialHandle;

    class Material {
    public:
        Material() = default;
        virtual ~Material() = default;

        // TODO: Implement utility function to get the general parameters of the material
        //  (double sided, etc...)

    };

}

#endif //RBND_MATERIAL_H
