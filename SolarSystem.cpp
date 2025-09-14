#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>

// Простой симулятор части Солнечной системы: Солнце, Венера, Земля, Луна и Марс.
// - Отрисовываются орбиты (траектории)
// - Планеты движутся по круговым орбитам
// - Луна вращается вокруг Земли
// - Управление: пробел - пауза/пуск, +/- - ускорение/замедление времени, R - сброс скорости, Up/Down - зум
// Компиляция (Linux):
//   g++ solar_system_sfml.cpp -o solar -I/opt/sfml2/include -L/opt/sfml2/lib -lsfml-graphics -lsfml-window -lsfml-system

// Перед запуском необходимо в терминале прописать команду - export LD_LIBRARY_PATH=/opt/sfml2/lib:$LD_LIBRARY_PATH
// где вместо /opt/sfml2/lib должен стоять ваш путь с sfml2 библиотеками, к сожалениюя пока что не в силах это починить :(

static constexpr float PI = 3.14159265358979323846f;

struct Body {
    std::string name;
    float radius;                // визуальный радиус (пиксели)
    sf::Color color;
    float orbitRadius;           // расстояние до родителя (пиксели)
    float orbitalPeriodDays;     // период в земных днях (для вычисления скорости)
    float angle;                 // текущий угол (радианы)
    Body* parent;                // nullptr для Солнца

    sf::CircleShape shape;       // графическое представление
    std::vector<sf::Vertex> trail; // след (ограниченный размер)

    Body(const std::string& n, float r, sf::Color c, float orbitR, float periodDays, Body* p = nullptr)
        : name(n), radius(r), color(c), orbitRadius(orbitR), orbitalPeriodDays(periodDays), angle(0.f), parent(p)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setFillColor(color);
    }

    // Возвращает позицию центра тела в мировых координатах
    sf::Vector2f worldPosition(const sf::Vector2f& systemCenter) const {
        sf::Vector2f center = systemCenter;
        if (parent) {
            // родитель уже должен быть обновлён
            // предположим, что parent->shape.getPosition() содержит его положение
            center = parent->shape.getPosition();
        }
        float x = center.x + orbitRadius * std::cos(angle);
        float y = center.y + orbitRadius * std::sin(angle);
        return { x, y };
    }

    void addTrailPoint(const sf::Vector2f& pos, std::size_t maxPoints = 400) {
        trail.emplace_back(pos, color);
        if (trail.size() > maxPoints) trail.erase(trail.begin());
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Солнечная система (SFML)");
    window.setFramerateLimit(60);

    // Центр системы (Солнце)
    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Создаём тела: Солнце, Венера, Земля, Луна, Марс
    Body sun("Sun", 30.f, sf::Color(255, 200, 0), 0.f, 0.f, nullptr);
    // orbitRadius для солнца = 0, period = 0

    Body venus("Venus", 8.f, sf::Color(200, 150, 120), 110.f, 224.7f, &sun);
    Body earth("Earth", 10.f, sf::Color(100, 150, 255), 170.f, 365.25f, &sun);
    Body moon("Moon", 4.f, sf::Color(200, 200, 200), 28.f, 27.3f, &earth);
    Body mars("Mars", 7.f, sf::Color(220, 120, 80), 260.f, 687.f, &sun);

    std::vector<Body*> bodies = { &sun, &venus, &earth, &moon, &mars };

    // Предварительно выставим солнце в центр
    sun.shape.setPosition(center);

    // Визуальные окружности орбит (outline)
    auto makeOrbitShape = [&](float r)->sf::CircleShape {
        sf::CircleShape s(r);
        s.setOrigin(r, r);
        s.setFillColor(sf::Color::Transparent);
        s.setOutlineColor(sf::Color(120, 120, 120, 120));
        s.setOutlineThickness(1.f);
        s.setPosition(center);
        return s;
        };

    sf::CircleShape orbitVenus = makeOrbitShape(venus.orbitRadius);
    sf::CircleShape orbitEarth = makeOrbitShape(earth.orbitRadius);
    sf::CircleShape orbitMars = makeOrbitShape(mars.orbitRadius);
    // Лунная орбита отрисуется вокруг Земли и обновляется каждый кадр

    // Параметры симуляции
    double timeScale = 600000.0; // сколько секунд симуляции = 1 сек реального времени (регулируемо)
    bool paused = false;

    sf::Clock clock;

    // Подписи: попробуем загрузить шрифт (если в папке есть font.ttf)
    sf::Font font;
    bool haveFont = font.loadFromFile("font.ttf"); // пользователь может положить любой ttf с именем font.ttf

    sf::Text hud;
    if (haveFont) {
        hud.setFont(font);
        hud.setCharacterSize(14);
        hud.setFillColor(sf::Color::White);
        hud.setPosition(10.f, 10.f);
    }

    float zoom = 1.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) paused = !paused;
                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) timeScale *= 1.5; // +
                if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract) timeScale /= 1.5; // -
                if (event.key.code == sf::Keyboard::R) { timeScale = 600000.0; }
                if (event.key.code == sf::Keyboard::Up) { zoom *= 1.1f; }
                if (event.key.code == sf::Keyboard::Down) { zoom /= 1.1f; }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) zoom *= 1.06f; else zoom /= 1.06f;
            }
        }

        float dt = clock.restart().asSeconds();
        if (paused) dt = 0.f;

        // Проходим по телам и обновляем углы и позиции
        for (Body* b : bodies) {
            if (b->parent == nullptr) {
                // Солнце фиксировано в центре
                b->shape.setPosition(center);
                b->addTrailPoint(b->shape.getPosition());
                continue;
            }

            // Если период задан, используем реальные периоды (в днях) для вычисления угловой скорости
            if (b->orbitalPeriodDays > 0.f) {
                double periodSeconds = static_cast<double>(b->orbitalPeriodDays) * 86400.0; // сек в периоде
                double angularSpeed = (2.0 * PI) / periodSeconds; // радиан в секунду (реального времени)
                // умножаем на timeScale — сколько реальных сим-секунд проходит за 1 сек реального времени
                b->angle += static_cast<float>(angularSpeed * (double)dt * timeScale);
            }
            else {
                // на случай, если период не задан — ничего не делаем
            }

            sf::Vector2f pos = b->worldPosition(center);
            b->shape.setPosition(pos);
            b->addTrailPoint(pos);

            // Если это Земля — обновим лунную орбиту центр
        }

        // Очистка и отрисовка
        window.clear(sf::Color(5, 5, 20));

        // Применяем зум через view
        sf::View view = window.getDefaultView();
        view.setCenter(center);
        view.setSize(window.getDefaultView().getSize().x / zoom, window.getDefaultView().getSize().y / zoom);
        window.setView(view);

        // Орбиты (статичные)
        window.draw(orbitVenus);
        window.draw(orbitEarth);
        window.draw(orbitMars);

        // Лунная орбита — рисуется как окружность вокруг текущей позиции Земли
        sf::CircleShape orbitMoon(moon.orbitRadius);
        orbitMoon.setOrigin(moon.orbitRadius, moon.orbitRadius);
        orbitMoon.setFillColor(sf::Color::Transparent);
        orbitMoon.setOutlineColor(sf::Color(120, 120, 120, 120));
        orbitMoon.setOutlineThickness(1.f);
        orbitMoon.setPosition(earth.shape.getPosition());
        window.draw(orbitMoon);

        // Трассы (trail) - рисуем как линии
        for (Body* b : bodies) {
            if (b->trail.size() >= 2) {
                sf::VertexArray va(sf::LineStrip, b->trail.size());
                for (std::size_t i = 0; i < b->trail.size(); ++i) va[i] = b->trail[i];
                window.draw(va);
            }
        }

        // Сами тела
        for (Body* b : bodies) window.draw(b->shape);

        // HUD
        if (haveFont) {
            std::string info = "Space - play/pause   +/- - speed   R - reset speed   Up/Down - zoom\n";
            info += "timeScale = " + std::to_string((long long)timeScale) + " sim-sec/sec\n";
            info += "Bodies: Sun, Venus, Earth, Moon, Mars";
            hud.setString(info);
            // HUD рисуем в экранных (незумированных) координатах: временно сбросим view
            window.setView(window.getDefaultView());
            window.draw(hud);
            // восстановим зум-вью
            window.setView(view);
        }

        window.display();
    }

    return 0;
}
