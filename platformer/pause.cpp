void pauseScreen(Engine& engine, std::string resourcePath) { 
	std::shared_ptr<ECSEngine::SceneView<COMPONENTS>> scene = engine.MakeScene();
    sf::Vector2f windowSize(scene->GetWindowManager().GetWindowBounds().width,
                            scene->GetWindowManager().GetWindowBounds().height);
    float factor = windowSize.x / 1920;

    // ADDING BACKGROUND
    ECSEngine::EntityID pauseBgEntity = scene->GetEntityManager().CreateEntity("PauseBackground");
    ECSEngine::SpriteID pauseBgSprite =
        scene->GetSpriteManager().RegisterSolidColorTexture(sf::Color(0, 0, 0, (255.f * 0.7)));
    scene->GetSpriteManager().ResizeAndGetColorSprite(pauseBgSprite, {windowSize.x, windowSize.y});
    ECSEngine::SpriteComponent pauseBgSpriteComp;
    pauseBgSpriteComp.textureID = pauseBgSprite;
    pauseBgSpriteComp.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), 1, 1);
    pauseBgSpriteComp.worldSpace = false;
    pauseBgSpriteComp.layer = 0;
    ECSEngine::LocationComponent pauseBgLocComp;
    pauseBgLocComp.loc = {0, 0};

    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(pauseBgEntity, pauseBgSpriteComp);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(pauseBgEntity,
                                                                         pauseBgLocComp);
    // BACKGROUND ADDED

    // ADDING TITLE
    ECSEngine::EntityID titleEntityid = scene->GetEntityManager().CreateEntity("TitleText");
    ECSEngine::SpriteID titleSpriteid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "pause.png", ECSEngine::Rect(ECSEngine::Point2D(0, 0), 621, 169));

    scene->GetSpriteManager().GetSprite(titleSpriteid).setScale({factor, factor});
    ECSEngine::SpriteComponent titleSpriteComponent;
    titleSpriteComponent.textureID = titleSpriteid;
    titleSpriteComponent.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 0), 621, 169);
    titleSpriteComponent.worldSpace = false;
    titleSpriteComponent.layer = 1;
    ECSEngine::LocationComponent titleLocComp;
    titleLocComp.loc = {(windowSize.x - 621 * factor) / 2, windowSize.y * 0.15f};

    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(titleEntityid,
                                                                       titleSpriteComponent);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(titleEntityid,
                                                                         titleLocComp);
    // TITLE END

    // ADDING BUTTONS
    ECSEngine::EntityID button1Entity = scene->GetEntityManager().CreateEntity("PauseButton1");
    ECSEngine::EntityID button2Entity = scene->GetEntityManager().CreateEntity("PauseButton2");
    ECSEngine::EntityID button3Entity = scene->GetEntityManager().CreateEntity("PauseButton3");
    ECSEngine::EntityID buttonText1Entity = scene->GetEntityManager().CreateEntity("PauseButtonText1");
    ECSEngine::EntityID buttonText2Entity = scene->GetEntityManager().CreateEntity("PauseButtonText2");
    ECSEngine::EntityID buttonText3Entity = scene->GetEntityManager().CreateEntity("PauseButtonText3");

    ECSEngine::SpriteID unselectedButtonid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150));
    ECSEngine::SpriteID selectedButtonid = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "menu-resource.png", ECSEngine::Rect(ECSEngine::Point2D(5, 302), 370, 209));
    scene->GetSpriteManager().GetSprite(unselectedButtonid).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(selectedButtonid).setScale({factor, factor});

    ECSEngine::SpriteID text1Sprite = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "pause-resource.png", ECSEngine::Rect(ECSEngine::Point2D(0, 1), 258, 65));
    ECSEngine::SpriteID text2Sprite = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "pause-resource.png", ECSEngine::Rect(ECSEngine::Point2D(0, 71), 250, 69));
    ECSEngine::SpriteID text3Sprite = scene->GetSpriteManager().RegisterTexture(
        resourcePath + "pause-resource.png", ECSEngine::Rect(ECSEngine::Point2D(0, 142), 133, 71));

    // MENU COMP SETUP
    ECSEngine::MenuComponent menuComp;
    menuComp.key = "PauseMenu";
    menuComp.menuLength = 3;
    menuComp.buttonEntities.push_back(button1Entity);
    menuComp.buttonEntities.push_back(button2Entity);
    menuComp.buttonEntities.push_back(button3Entity);
    menuComp.textEntities.push_back(buttonText1Entity);
    menuComp.textEntities.push_back(buttonText2Entity);
    menuComp.textEntities.push_back(buttonText3Entity);
    menuComp.text.push_back(text1Sprite);
    menuComp.text.push_back(text2Sprite);
    menuComp.text.push_back(text3Sprite);
    menuComp.buttons[0] = unselectedButtonid;
    menuComp.buttons[1] = selectedButtonid;
    menuComp.startTopLeft = {776.f, 388.f};
    menuComp.spacingPx = 209;
    // MENU COMP SETUP END

    ECSEngine::SpriteComponent spriteCompButton1;
    spriteCompButton1.textureID = unselectedButtonid;
    spriteCompButton1.bounds = ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150);
    spriteCompButton1.worldSpace = false;
    spriteCompButton1.layer = 1;
    ECSEngine::LocationComponent locCompButton1;
    //locCompButton1.loc = {menuComp.startTopLeft.x * factor, menuComp.startTopLeft.y * factor};
    locCompButton1.loc = {776 * factor, 388 * factor};
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(button1Entity,
                                                                       spriteCompButton1);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(button1Entity,
                                                                         locCompButton1);

    ECSEngine::SpriteComponent spriteCompButton2;
    spriteCompButton2.textureID = unselectedButtonid;
    spriteCompButton2.bounds = ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150);
    spriteCompButton2.worldSpace = false;
    spriteCompButton2.layer = 1;
    ECSEngine::LocationComponent locCompButton2;
    locCompButton2.loc = {776 * factor, 
                          (menuComp.startTopLeft.y + menuComp.spacingPx) * factor};
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(button2Entity,
                                                                       spriteCompButton2);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(button2Entity,
                                                                         locCompButton2);

    ECSEngine::SpriteComponent spriteCompButton3;
    spriteCompButton3.textureID = unselectedButtonid;
    spriteCompButton3.bounds = ECSEngine::Rect(ECSEngine::Point2D(10, 4), 360, 150);
    spriteCompButton3.worldSpace = false;
    spriteCompButton3.layer = 1;
    ECSEngine::LocationComponent locCompButton3;
    locCompButton3.loc = {menuComp.startTopLeft.x * factor,
                          (menuComp.startTopLeft.y + (menuComp.spacingPx * 2)) * factor};
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(button3Entity,
                                                                       spriteCompButton3);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(button3Entity,
                                                                         locCompButton3);
    // BUTTON TEXTS
    ECSEngine::SpriteComponent spriteCompText1;
    spriteCompText1.textureID = text1Sprite;
    spriteCompText1.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 1), 258, 65);
    spriteCompText1.worldSpace = false;
    spriteCompText1.layer = 2;
    ECSEngine::LocationComponent locCompText1;
    locCompText1.loc = {(menuComp.startTopLeft.x + 180.f - 129.f) * factor,
                        (menuComp.startTopLeft.y + 75.f - 32.5f) * factor};
    scene->GetSpriteManager().GetSprite(text1Sprite).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(text1Sprite).setOrigin({129.f, 32.5f});
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(buttonText1Entity,
                                                                       spriteCompText1);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(buttonText1Entity,
                                                                         locCompText1);

    ECSEngine::SpriteComponent spriteCompText2;
    spriteCompText2.textureID = text2Sprite;
    spriteCompText2.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 71), 250, 69);
    spriteCompText2.worldSpace = false;
    spriteCompText2.layer = 2;
    ECSEngine::LocationComponent locCompText2;
    locCompText2.loc = {(menuComp.startTopLeft.x + 180.f - 125.f) * factor,
                        ((menuComp.startTopLeft.y + menuComp.spacingPx) + 75.f - 34.5f) * factor};
    scene->GetSpriteManager().GetSprite(text2Sprite).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(text2Sprite).setOrigin({125.f, 34.5f});
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(buttonText2Entity,
                                                                       spriteCompText2);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(buttonText2Entity,
                                                                         locCompText2);

    ECSEngine::SpriteComponent spriteCompText3;
    spriteCompText3.textureID = text3Sprite;
    spriteCompText3.bounds = ECSEngine::Rect(ECSEngine::Point2D(0, 142), 133, 71);
    spriteCompText3.worldSpace = false;
    spriteCompText3.layer = 2;
    ECSEngine::LocationComponent locCompText3;
    locCompText3.loc = {(menuComp.startTopLeft.x + 180.f - 66.5f) * factor,
        ((menuComp.startTopLeft.y + (menuComp.spacingPx * 2)) + 75.f - 35.5f) * factor};
    scene->GetSpriteManager().GetSprite(text3Sprite).setScale({factor, factor});
    scene->GetSpriteManager().GetSprite(text3Sprite).setOrigin({66.5f, 35.5f});
    scene->GetEntityManager().AddComponent<ECSEngine::SpriteComponent>(buttonText3Entity,
                                                                       spriteCompText3);
    scene->GetEntityManager().AddComponent<ECSEngine::LocationComponent>(buttonText3Entity,
                                                                         locCompText3);
    // COMPLETE ADDING BUTTONS
    
    ECSEngine::InputComponent inputComp(pauseBgEntity);
    inputComp.delay = 60;
    inputComp.sleepFrame = 60;
    scene->GetEntityManager().AddComponent<ECSEngine::MenuComponent>(pauseBgEntity, menuComp);
    scene->GetEntityManager().AddComponent<ECSEngine::InputComponent>(pauseBgEntity, inputComp);


    scene->GetSystemManager().AddSystem(std::make_unique <ECSEngine::InputSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::SpriteSystem<COMPONENTS>>());
    scene->GetSystemManager().AddSystem(std::make_unique<ECSEngine::MenuSystem<COMPONENTS>>());


    engine.AddScene(scene);
}