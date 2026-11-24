

#define COMPONENTS                                                                             \
    ECSEngine::LocationComponent, ECSEngine::MovementComponent, ECSEngine::CollisionComponent, \
        ECSEngine::SpriteComponent, ECSEngine::SpawnComponent, ECSEngine::CameraComponent,     \
        ECSEngine::CameraFollower, ECSEngine::InputComponent, ECSEngine::GravityComponent,     \
        ECSEngine::CameraShake, ECSEngine::ScoreComponent, ECSEngine::RespawnComponent
using Engine = ECSEngine::ECSEngine<COMPONENTS>;

void startMenu(Engine& engine, std::string resourcePath) { 
    std::shared_ptr<ECSEngine::SceneView<COMPONENTS>> scene = engine.MakeScene();
    sf::Vector2f windowSize(scene->GetWindowManager().GetWindowBounds().width,
                            scene->GetWindowManager().GetWindowBounds().height);
    // scene->GetSoundManager().RegisterSound(resourcePath + "menu-bgm.ogg", "menu-bgm");
    // scene->GetSoundManager().RegisterSound(resourcePath + "menu-interact.ogg", "menu-interact");
    
    // ADDING MENU BACKGROUND
    ECSEngine::EntityID bgEntityid = scene->GetEntityManager().CreateEntity("MenuBackground");
    ECSEngine::SpriteID bgSpriteid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-background.png",
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), 1920, 1080));
    scene->GetSpriteManager()
        .GetSprite(bgSpriteid)
        .setScale({windowSize.x / 1920, windowSize.y / 1080});
    ECSEngine::SpriteComponent spriteComponent;
    spriteComponent.textureID = bgSpriteid;
    spriteComponent.bounds =
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), 1920, 1080);
    spriteComponent.worldSpace = false;
    ECSEngine::LocationComponent locComp;
    locComp.loc = {0, 0};
    
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(bgEntityid, spriteComponent);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(bgEntityid, locComp);
    // MENU BG END

    // ADDING TITLE
    ECSEngine::EntityID titleEntityid = scene->GetEntityManager().CreateEntity("TitleText");
    ECSEngine::SpriteID titleSpriteid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "title.png",
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), 598, 174));
    scene->GetSpriteManager()
        .GetSprite(titleSpriteid)
        .setScale({598 * (598 / windowSize.x), 174 * (174 / windowSize.y)});
    ECSEngine::SpriteComponent titleSpriteComponent;
    titleSpriteComponent.textureID = titleSpriteid;
    titleSpriteComponent.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), 598, 174);
    titleSpriteComponent.worldSpace = false;
    ECSEngine::LocationComponent titleLocComp;
    //center of window - half of sprite size

    titleLocComp.loc = {0, 0};

    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(titleEntityid,
                                                                       titleSpriteComponent);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(titleEntityid,
                                                                         titleLocComp);
    // TITLE END

    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::InputSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::SpriteSystem<COMPONENTS>>());

    engine.AddScene(scene);

}