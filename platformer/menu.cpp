void startMenu(Engine& engine, std::string resourcePath) { 
    std::shared_ptr<ECSEngine::SceneView<COMPONENTS>> scene = engine.MakeScene();
    sf::Vector2f windowSize(scene->GetWindowManager().GetWindowBounds().width,
                            scene->GetWindowManager().GetWindowBounds().height);
    float factor = windowSize.x / 1920;
    // scene->GetSoundManager().RegisterSound(resourcePath + "menu-bgm.ogg", "menu-bgm");
    // scene->GetSoundManager().RegisterSound(resourcePath + "menu-interact.ogg", "menu-interact");
    
    // ADDING MENU BACKGROUND
    ECSEngine::EntityID bgEntityid = scene->GetEntityManager().CreateEntity("MenuBackground");
    ECSEngine::SpriteID bgSpriteid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-background.png",
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), 1920, 1080));
    scene->GetSpriteManager().GetSprite(bgSpriteid).setScale({factor, factor});
    ECSEngine::SpriteComponent spriteComponent;
    spriteComponent.textureID = bgSpriteid;
    spriteComponent.bounds =
        ECSEngine::Rect(ECSEngine::Point2D(0, 0), 1920, 1080);
    spriteComponent.worldSpace = false;
    spriteComponent.layer = 0;
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
    
    scene->GetSpriteManager().GetSprite(titleSpriteid).setScale({factor, factor});
    ECSEngine::SpriteComponent titleSpriteComponent;
    titleSpriteComponent.textureID = titleSpriteid;
    titleSpriteComponent.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), 598, 174);
    titleSpriteComponent.worldSpace = false;
    titleSpriteComponent.layer = 1;
    ECSEngine::LocationComponent titleLocComp;
    titleLocComp.loc = {(windowSize.x - 598 * factor) / 2, windowSize.y*0.15f};

    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(titleEntityid,
                                                                       titleSpriteComponent);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(titleEntityid,
                                                                         titleLocComp);
    // TITLE END

    // ADDING BUTTONS
    ECSEngine::EntityID topButtonEntityid = scene->GetEntityManager().CreateEntity("TopButton");
    ECSEngine::EntityID bottomButtonEntityid = scene->GetEntityManager().CreateEntity("BottomButton");
    ECSEngine::EntityID topTextEntityid = scene->GetEntityManager().CreateEntity("TopText");
    ECSEngine::EntityID bottomTextEntityid = scene->GetEntityManager().CreateEntity("BottomText");

    ECSEngine::SpriteID unselectedButtonid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150));
    ECSEngine::SpriteID selectedButtonid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(5, 302), 370, 209));
    ECSEngine::SpriteID topText = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(1, 155), 168, 65));
    ECSEngine::SpriteID bottomText = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(1, 228), 259, 73));
    scene->GetSpriteManager().GetSprite(unselectedButtonid).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(selectedButtonid).setScale({factor, factor});

    ECSEngine::SpriteComponent spriteCompButton1;
    spriteCompButton1.textureID = unselectedButtonid;
    spriteCompButton1.bounds = ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150);
    spriteCompButton1.worldSpace = false;
    spriteCompButton1.layer = 1;
    ECSEngine::LocationComponent locCompButton1;
    locCompButton1.loc = {776 * factor, 477 * factor};
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(topButtonEntityid, spriteCompButton1);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(topButtonEntityid, locCompButton1);

    ECSEngine::SpriteComponent spriteCompButton2;
    spriteCompButton2.textureID = unselectedButtonid;
    spriteCompButton2.bounds = ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150);
    spriteCompButton2.worldSpace = false;
    spriteCompButton2.layer = 1;
    ECSEngine::LocationComponent locCompButton2;
    locCompButton2.loc = {776 * factor, 765 * factor};
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(bottomButtonEntityid,
                                                                       spriteCompButton2);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(bottomButtonEntityid,
                                                                         locCompButton2);

    ECSEngine::SpriteComponent spriteCompText1;
    spriteCompText1.textureID = topText;
    spriteCompText1.bounds = ECSEngine::Rect(ECSEngine::Point2D(1, 155), 168, 65);
    spriteCompText1.worldSpace = false;
    spriteCompText1.layer = 2;
    ECSEngine::LocationComponent locCompText1;
    locCompText1.loc = {(776.f + 180.f - 84.f) * factor, (477.f + 75.f - 32.5f) * factor};
    scene->GetSpriteManager().GetSprite(topText).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(topText).setOrigin({84.f, 32.5f});
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(topTextEntityid,
                                                                       spriteCompText1);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(topTextEntityid,
                                                                         locCompText1);

    ECSEngine::SpriteComponent spriteCompText2;
    spriteCompText2.textureID = bottomText;
    spriteCompText2.bounds = ECSEngine::Rect(ECSEngine::Point2D(1, 228), 259, 73);
    spriteCompText2.worldSpace = false;
    spriteCompText2.layer = 2;
    ECSEngine::LocationComponent locCompText2;
    locCompText2.loc = {(776.f + 180.f - 129.5f) * factor, (765.f + 75.f - 36.5f) * factor};
    scene->GetSpriteManager().GetSprite(bottomText).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(bottomText).setOrigin({129.5f, 36.5f});
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(bottomTextEntityid,
                                                                       spriteCompText2);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(bottomTextEntityid,
                                                                         locCompText2);

    ECSEngine::MenuComponent menuComp;
    menuComp.key = "StartMenu";
    menuComp.menuLength = 2;
    menuComp.buttonEntities.push_back(topButtonEntityid);
    menuComp.buttonEntities.push_back(bottomButtonEntityid);
    menuComp.textEntities.push_back(topTextEntityid);
    menuComp.textEntities.push_back(bottomButtonEntityid);
    menuComp.text.push_back(topText);
    menuComp.text.push_back(bottomText);
    menuComp.buttons[0] = unselectedButtonid;
    menuComp.buttons[1] = selectedButtonid;
    menuComp.startTopLeft = {776, 477};
    menuComp.spacingPx = 288;

    ECSEngine::InputComponent inputComp(bgEntityid);
    inputComp.delay = 60;
    inputComp.sleepFrame = 60;

    scene->GetEntityManager().AddComponent<ECSEngine::MenuComponent>(bgEntityid, menuComp);
    scene->GetEntityManager().AddComponent<ECSEngine::InputComponent>(bgEntityid, inputComp);

    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::InputSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::SpriteSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::MenuSystem<COMPONENTS>>());

    engine.AddScene(scene);

}