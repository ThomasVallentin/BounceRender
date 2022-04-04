//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Xform.h"

namespace Rebound {

    std::vector<AttributeSpec> Xform::GetDefaultAttributes() {
        auto specs = Entity::GetDefaultAttributes();
        specs.emplace_back("transform", AttributeValue::Cast<Matrix4>(
                {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}));

        return specs;
    }

}
