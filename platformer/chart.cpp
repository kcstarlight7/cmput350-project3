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

    chartComp.noteTexID = scene->GetSpriteManager().RegisterSolidColorTexture(sf::Color::Cyan);

    sf::Vector2f windowSize(scene->GetWindowManager().GetWindowBounds().width,
                            scene->GetWindowManager().GetWindowBounds().height);

    // spawner creation
    ECSEngine::EntityID noteSpawner = scene->GetEntityManager().CreateEntity("noteSpawner");

    ECSEngine::LocationComponent noteSpawnerLoc;
    noteSpawnerLoc.loc = ECSEngine::Point2D((windowSize.x / 2) - ((windowSize.x * 0.6) / 2), 0);

    ECSEngine::SpriteComponent noteSpawnerSprite;
    noteSpawnerSprite.worldSpace = true;
    noteSpawnerSprite.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), windowSize.x * 0.6, 20);
    noteSpawnerSprite.textureID =
        scene->GetSpriteManager().RegisterSolidColorTexture(sf::Color::Blue);
    scene->GetSpriteManager().ResizeAndGetColorSprite(noteSpawnerSprite.textureID,
                                                      ECSEngine::Point2D(windowSize.x * 0.6, 20.f));

    scene->GetEntityManager().AddComponent<ECSEngine::ChartComponent>(noteSpawner, chartComp);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(noteSpawner, noteSpawnerLoc);
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(noteSpawner, noteSpawnerSprite);

    // judgement bar creation
    ECSEngine::EntityID judgeLine = scene->GetEntityManager().CreateEntity("judgeLine");

    ECSEngine::LocationComponent judgeLineLoc;
    judgeLineLoc.loc = ECSEngine::Point2D((windowSize.x / 2) - ((windowSize.x * 0.6) / 2), windowSize.y * 0.8f);

    ECSEngine::SpriteComponent judgeLineSprite;
    judgeLineSprite.worldSpace = true;
    judgeLineSprite.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), windowSize.x * 0.6, 5);
    judgeLineSprite.textureID =
        scene->GetSpriteManager().RegisterSolidColorTexture(sf::Color::Yellow);
    scene->GetSpriteManager().ResizeAndGetColorSprite(judgeLineSprite.textureID,
                                                      ECSEngine::Point2D(windowSize.x * 0.6, 5));

    ECSEngine::CollisionComponent judgeLineCollision;
    judgeLineCollision.collisionBox =
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), windowSize.x * 0.6, 5);

    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(judgeLine,
                                                                         judgeLineLoc);
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(judgeLine, judgeLineSprite);
    scene->GetEntityManager().AddComponent<ECSEngine::CollisionComponent>(judgeLine, judgeLineCollision);


    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::SpriteSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::MovementSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::ChartSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::CollisionSystem<COMPONENTS>>());

    engine.AddScene(scene);
}