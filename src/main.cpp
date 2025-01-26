#include <iostream>
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include "custom_physics.hpp"
#include "resource_loader.hpp"

int testLoop(){
	if (!ResourceLoader::initialize("resources.dat")) {
		SPDLOG_ERROR( "Failed to initialize resources" );
        return -1;
    }

	sf::RenderWindow window(sf::VideoMode({640,480}), L"메이플 모작");

	// 창의 아이콘 설정
	if (const auto* iconData = ResourceLoader::get()->getResource("icon.png")) {
		sf::Image icon;
		if (icon.loadFromMemory(iconData->data(), iconData->size())) {
			window.setIcon(icon);
		}
    }
	else {
		SPDLOG_ERROR("Icon Load error!");
	}
	SPDLOG_INFO("program start!");

	sf::Time sysTime;

	sf::Clock clock;
	clock.restart();
	float savedTime = 0.0f;
	float deltaTime = 0.0f;
	int accumFrameCount = 0;
	
	sf::View currentView(sf::FloatRect({0, 0,}, {320, 240}));

	sf::Font font;
	if(const auto* fontData = ResourceLoader::get()->getResource("fonts/NanumGothic.ttf")) {
		if(!font.openFromMemory(fontData->data(),fontData->size())) {
			SPDLOG_ERROR("font load error!");
		}
	}

	sf::Texture characterTexture;
	if(const auto* chTxData = ResourceLoader::get()->getResource("sprites/character_dummy.png")) {
		if(!characterTexture.loadFromMemory(chTxData->data(),chTxData->size(), false, sf::IntRect({0,0},{43,68}))){
			SPDLOG_ERROR("texture load error!");
		}
	}

	characterTexture.setSmooth(false);

	sf::Sprite sprite(characterTexture);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2,bounds.size.y});
	sprite.setPosition({160.0f,120.0f});
	sprite.setScale({0.5f, 0.5f});

	sf::Text fpsText(font);
	fpsText.setCharacterSize(24);
	fpsText.setScale(sf::Vector2f(0.5f,0.5f));
	fpsText.setString("0.0");

	window.setView(currentView);
	window.setVerticalSyncEnabled(false);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
			{
				SPDLOG_INFO("window closed");
                window.close();
			}
        }
			
		deltaTime = clock.restart().asSeconds();
		savedTime += deltaTime;
		accumFrameCount++;

		if(savedTime > 0.2f)
		{
			
			float fps = 1.0f / (savedTime / accumFrameCount);
			accumFrameCount = 0;
			savedTime = 0.0f;

			int fpsRounded = (int)fps;

			std::wstring setstring = std::to_wstring(fpsRounded) + L" 프레임";
			fpsText.setString(setstring);
		}

		fpsText.setPosition(sf::Vector2f(0.0f, 0.0f));

		window.clear();
		window.draw(sprite);
		window.draw(fpsText);
        window.display();
	}

	return 0;
}

int main() 
{
	return testLoop();
}