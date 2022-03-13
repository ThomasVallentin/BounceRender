//
// Created by tvallentin on 08/03/2022.
//

#ifndef BOUNCE_SCENE_H
#define BOUNCE_SCENE_H

#include "global.h"
#include "Bounce.h"
#include "materials/LambertMaterial.h"

#include <vector>
#include <map>

class Camera;

class Scene {
public:
    Scene() {
        rtcScene = rtcNewScene(Bounce::globalDevice);
    }

    static Scene Open(const std::string &filename);
    bool LoadTestGeometry();
    void Commit() { rtcCommitScene(rtcScene); }
    void Release() { rtcReleaseScene(rtcScene); }

public:
    RTCScene rtcScene;
    Material *defaultMaterial = new LambertMaterial();
    // std::vector<Material> materials;
    // std::map<size_t, Material*> bindings;
};


#endif //BOUNCE_SCENE_H
