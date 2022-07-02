//
// Created by tvallentin on 08/03/2022.
//

#ifndef BOUNCE_SCENE_H
#define BOUNCE_SCENE_H

#include "Bounce.h"
#include "Materials/LambertMaterial.h"


namespace Bounce {

    class Camera;

    class Scene {
    public:
        Scene();

        static Scene Open(const std::string &filename);

        bool LoadTestGeometry();

        void Commit() { rtcCommitScene(rtcScene); }

        void Release() { rtcReleaseScene(rtcScene); }

    public:
        RTCScene rtcScene;
        Material *defaultMaterial = new LambertMaterial(Color3f(0.6, 0.8, 1.0));
        // std::vector<Material> materials;
        // std::map<size_t, Material*> bindings;
    };

}

#endif //BOUNCE_SCENE_H
