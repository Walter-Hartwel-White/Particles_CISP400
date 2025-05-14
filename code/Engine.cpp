#include "Engine.h"
#include "Particle.h"
#include <iostream>

Engine::Engine() {
	VideoMode vm(sf::VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	m_Window.create(vm, "wowzers", Style::Default);
}

void Engine::run() {
	sf::Clock clock;
	float dt;
	Particle particle();

	//unit testing
		cout << "Starting Particle unit tests..." << endl;
		Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
		p.unitTests();
		cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {
		sf::Time time = clock.restart();
		dt = time.asSeconds(); 

		input();
		update(dt);
		draw();
	}
}

void Engine::input() {
	Vector2i coor;

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	Event event;
	while (m_Window.pollEvent(event)) {
		coor.x = event.mouseButton.x;
		coor.y = event.mouseButton.y;

		if (event.type == Event::Closed) m_Window.close();

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left) {
				for (int i = 0; i < NUM_PARTICLES; i++) {
					Particle particle(m_Window, rand() % 50 + 25, coor);
					m_particles.push_back(particle);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds) {
	for (auto thingers = m_particles.begin(); thingers != m_particles.end(); ) {
		if ((*thingers).getTTL() > 0.0) {
			(*thingers).update(dtAsSeconds);
			++thingers;
		}
		else {
			thingers = m_particles.erase(thingers);
		}
	}
}

void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++) m_Window.draw(m_particles.at(i));
	m_Window.display();
}