#pragma once

#include <SFML/Graphics.hpp>

namespace mt
{

class particle {

    private:
        sf::CircleShape* m_circle;

        float m_x, m_y;
        float m_vx, m_vy;
        float m_lifespan;
        float m_max_lifespan = 3; //In seconds

        float m_color[4]  = { 255.0f, 255.0f, 255.0f, 255.0f };
        float m_color_dif = ( 255.0f / m_max_lifespan) * 2;

    private:

        void update_color(double dt) {
            
            if (m_color[1] - m_color_dif * dt >= 0) {

                //m_color[0] -= m_color_dif * dt * (m_max_lifespan - m_lifespan);
                m_color[1] -= m_color_dif * dt;
                m_color[2] -= m_color_dif * dt;
                m_color[3] -= m_color_dif * dt;

                if (m_color[1] > 0) {
                    m_circle->setFillColor(sf::Color((sf::Uint8)m_color[0], (sf::Uint8)m_color[1], (sf::Uint8)m_color[2], (sf::Uint8)m_color[3]));
                }
            }

        }

    public:

        particle(int x, int y) {
            m_lifespan = m_max_lifespan;
            m_x = x;
            m_y = y;
            m_vx = (float)(rand() % 1000)/10.f - 50.f;
            m_vy = (float)(rand() % 1000)/10.f - 50.f;

            m_circle = new sf::CircleShape(3);
            m_circle->setPosition(m_x, m_y);
        }

        ~particle() {
            delete m_circle;
        }

        void update_particle(double dt) {
            m_vx = m_vx - m_vx * dt;
            m_vy = m_vy - m_vy * dt;
            m_x += m_vx * dt;
            m_y += m_vy * dt;

            m_circle->setPosition(m_x, m_y);
            m_lifespan -= dt;
            update_color(dt);
        }

        float check_lifespan() {
            return m_lifespan;
        }

        sf::CircleShape* return_particle_shape() {
            return m_circle;
        }

};

}