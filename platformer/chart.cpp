#include <fstream>

void chartScene(Engine& engine, std::string chartPath) {
    std::shared_ptr<ECSEngine::SceneView<COMPONENTS>> scene = engine.MakeScene();
    ECSEngine::ChartComponent chartComp;
    
    std::vector<std::filesystem::path> chartFolders;
    std::string token;
    /*
    for (const auto& entry : std::filesystem::directory_iterator(resourcePath + "charts")) {
        chartFolders.push_back(entry.path());
    }
    */
    std::ifstream chartFile(chartPath);
    float bpm = 0;
    float bpmDivision = 0;
    while (getline(chartFile, token, ',')) {
        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());

        //std::cout << token << '\n';

        int tokenPos = 0;

        std::vector<bool> lane(4, false);
        std::vector<bool> hold(4, false);
        std::vector<float> holdDivision(4, 0);
        std::vector<float> holdLength(4, 0);

        if (token[tokenPos] == '(') {
            tokenPos++;
            std::string sNum = "";
            for (int bracketPos = tokenPos; token[bracketPos] != ')'; bracketPos++) {
                sNum += token[bracketPos];
                tokenPos++;
            }
            tokenPos++;

            bpm = std::stof(sNum);
        }

        if (token[tokenPos] == '{') {
            tokenPos++;
            std::string sNum = "";
            for (int bracketPos = tokenPos; token[bracketPos] != '}'; bracketPos++) {
                sNum += token[bracketPos];
                tokenPos++;
            }
            tokenPos++;

            bpmDivision = std::stof(sNum);
        }

        // read lane
        while (token[tokenPos] >= '0' && token[tokenPos] <= '4') {
            int curLaneIndex = token[tokenPos] - '0' - 1;
            lane[curLaneIndex] = true;
            tokenPos++;

            if (token[tokenPos] == 'h') {
                hold[curLaneIndex] = true;
                tokenPos += 2;

                std::string sNum = "";
                for (int bracketPos = tokenPos; token[bracketPos] != ':'; bracketPos++) {
                    sNum += token[bracketPos];
                    tokenPos++;
                }

                tokenPos++;
                holdDivision[curLaneIndex] = std::stof(sNum);

                sNum = "";
                for (int bracketPos = tokenPos; token[bracketPos] != ']'; bracketPos++) {
                    sNum += token[bracketPos];
                    tokenPos++;
                }

                holdLength[curLaneIndex] = std::stof(sNum);
                tokenPos++;
            }

            if (token[tokenPos] == '/') {
                tokenPos++;
            }
        }

        

        ECSEngine::ChartNote note;
        note.bpm = bpm;
        note.subdivision = bpmDivision;
        note.lane = lane;
        note.hold = hold;
        note.holdLength = holdLength;
        note.holdSubdivision = holdDivision;

        chartComp.data.push_back(note);
    }
    ECSEngine::EntityID noteSpawner = scene->GetEntityManager().CreateEntity("noteSpawner");
    scene->GetEntityManager().AddComponent<ECSEngine::ChartComponent>(noteSpawner, chartComp);

    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::ChartSystem<COMPONENTS>>());
    engine.AddScene(scene);
}