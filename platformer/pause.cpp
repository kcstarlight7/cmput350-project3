void pauseScreen(Engine& engine, std::string resourcePath) { 
	std::shared_ptr<ECSEngine::SceneView<COMPONENTS>> scene = engine.MakeScene();
    sf::Vector2f windowSize(scene->GetWindowManager().GetWindowBounds().width,
                            scene->GetWindowManager().GetWindowBounds().height);
    float factor = windowSize.x / 1920;

    // ADDING BACKGROUND
    ECSEngine::EntityID pauseBgEntity = scene->GetEntityManager().CreateEntity("PauseBackground");
    ECSEngine::SpriteID pauseBgSprite =
        scene->GetSpriteManager().RegisterSolidColorTexture(sf::Color(0, 0, 0, (255.f * 0.8)));

}