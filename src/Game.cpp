#include <Game.hpp>
#include <iomanip>

namespace mt
{
    Game::~Game()
    {
        if (m_window != nullptr)
            delete m_window;
    }

    void Game::SetCaption(const std::string& caption)
    {
        m_caption = caption;
    }

    void Game::SetResolution(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    void Game::Setup()
    {
        m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_caption);
        m_window->sf::Window::setFramerateLimit(60);
    }

    void Game::Run()
    {
        std::vector<mt::particle*> particles;

        bool mouse_was_pressed = false; //For click check
        bool mouse_pressed = false; //For click check

        sf::Clock timer;
        sf::Mouse mouse;

        sf::Time dt;


        while (m_window->isOpen())
        {

            dt = timer.restart();

            mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            sf::Vector2i mouse_pos = mouse.getPosition(*m_window);

            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }


            if (mouse_pressed && !mouse_was_pressed) //On click
            {
                for (int i = 0; i < 20; i++) {
                    particles.emplace_back(new mt::particle(mouse_pos.x, mouse_pos.y));
                }
            }


            for (int i = particles.size() - 1; i >= 0; i--) {
                particles[i]->update_particle(dt.asSeconds());

                if (particles[i]->check_lifespan() <= 0) {
                    //particles[i]->~particle();
                    delete particles[i];
                    particles.erase(particles.begin() + i);
                }

            }

            m_window->clear();

            for (int i = particles.size() - 1; i >= 0; i--) {
                m_window->draw(*particles[i]->return_particle_shape());
            }

            particles.shrink_to_fit();

            m_window->display();


            mouse_was_pressed = mouse_pressed;

            //std::cout << dt.asSeconds() << "\n";
            //std::cout << particles.capacity() << "\n";


        }

    }
}

