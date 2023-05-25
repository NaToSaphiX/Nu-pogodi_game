#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

class setSound {
public:
    SoundBuffer c, e, g, p;
    Sound cah, egg, gameover, pass;

    setSound() {
        c.loadFromFile("catch.ogg");
        e.loadFromFile("egg.ogg");
        g.loadFromFile("gameover.ogg");
        p.loadFromFile("pass.ogg");

        cah.setBuffer(c);
        egg.setBuffer(e);
        gameover.setBuffer(g);
        pass.setBuffer(p);
    }
};

setSound sound;

class Player {
public:
    Sprite sprite, arm;
    bool left, up;
    int ay = 0, engine = 0;

    Player(Texture& p, Texture& p2) {
        sprite.setTexture(p);
        arm.setTexture(p2);
        arm.setOrigin(54, 47);
    }

    void upate() {
        if (left) {
            sprite.setTextureRect(IntRect(0, 0, 134, 201));
            sprite.setPosition(360, 200);

            if (up) {
                arm.setRotation(0);
                ay = 0;
            }
            else {
                arm.setRotation(-30);
                ay = 50;
            }

            arm.setTextureRect(IntRect(0, 0, 108, 93));
            arm.setPosition(280 + 54, 200 + 47 + ay);
        }
        else {
            sprite.setTextureRect(IntRect(134, 0, -134, 201));
            sprite.setPosition(510, 200);

            if (up) {
                arm.setRotation(0);
                ay = 0;
            }
            else {
                arm.setRotation(30);
                ay = 50;
            }

            arm.setTextureRect(IntRect(108, 0, -108, 93));
            arm.setPosition(610 + 54, 200 + 47 + ay);
        }

        if (left && up)
            engine = 0;
        else if (left && !up)
            engine = 1;
        else if (!left && up)
            engine = 2;
        else if (!left && !up)
            engine = 3;
    }
};

bool newgo = false;

class Egg {
public:
    Sprite sprite[5];
    FloatRect rect[5];
    bool vid[5];
    int t = 1000, next = 0;

    void set(Texture& image, int& nom) {
        vid[0] = true;
        for (int i = 1; i < 5; i++)
            vid[i] = false;
        
        for (int i = 0; i < 5; i++) {
            if (nom == 1) {
                rect[i].left = 191 + 10 + i * 25;
                rect[i].top = 181 - 10 + i * 13;
            }
            else if (nom == 2) {
                rect[i].left = 181 + 10 + i * 25;
                rect[i].top = 271 - 10 + i * 13;
            }
            else if (nom == 3) {
                rect[i].left = 811 - (10 + i * 25);
                rect[i].top = 185 - 10 + i * 13;
            }
            else if (nom == 4) {
                rect[i].left = 811 - (10 + i * 25);
                rect[i].top = 275 - 10 + i * 13;
            }
        }

        for (int i = 0; i < 5; i++) {
            sprite[i].setTexture(image);
            sprite[i].setOrigin(11, 9);

            if (nom < 3)
                sprite[i].setRotation(30 * i);
            else
                sprite[i].setRotation(-30 * i);
            sprite[i].setPosition(rect[i].left, rect[i].top);
        }
    }

    void update() {
        t--;

        if (t == 0) {
            vid[next] = false;
            next++;
            if (next < 5)
                vid[next] = true;
            else
                newgo = true;

            t = 1000;

            sound.egg.play();
        }
    }
};

class Score {
public:
    Sprite sprite[2];
    int frame;
    int s[2];

    Score(Texture& image) {
        for (int i = 0; i < 2; i++) {
            sprite[i].setTexture(image);
            sprite[i].setPosition(670 + 30 * i, 70);

            s[i] = 0;
        }

        frame = 0;
    }

    void update() {
        if (frame < 10)
            s[1] = frame;
        else {
            s[0] = frame / 10;
            s[1] = frame % 10;
        }

        for (int i = 0; i < 2; i++)
            sprite[i].setTextureRect(IntRect(25 * s[i], 0, 25, 46));
    }
};

class Upast {
public:
    Sprite sprite;
    bool vid;
    int anim = 1, t = 1000;

    void set(Texture& image) {
        sprite.setTexture(image);

        vid = false;
    }

    void update(bool right) {
        t--;

        if (t == 0) {
            anim++;
            t = 1000;
        }

        if (anim == 1) {
            if (right) {
                sprite.setTextureRect(IntRect(0, 0, 52, 66));
                sprite.setPosition(650, 350);
            }
            else {
                sprite.setTextureRect(IntRect(52, 0, -52, 66));
                sprite.setPosition(300, 350);
            }
        }
        if (anim == 2) {
            if (right) {
                sprite.setTextureRect(IntRect(0, 0, 87, 66));
                sprite.setPosition(650, 350);
            }
            else {
                sprite.setTextureRect(IntRect(87, 0, -87, 66));
                sprite.setPosition(265, 350);
            }
        }
        if (anim == 3) {
            if (right) {
                sprite.setTextureRect(IntRect(87, 0, 22, 66));
                sprite.setPosition(750, 350);
            }
            else {
                sprite.setTextureRect(IntRect(109, 0, -22, 66));
                sprite.setPosition(230, 350);
            }
        }
        if (anim == 4) {
            if (right) {
                sprite.setTextureRect(IntRect(109, 0, 22, 66));
                sprite.setPosition(780, 350);
            }
            else {
                sprite.setTextureRect(IntRect(131, 0, -22, 66));
                sprite.setPosition(195, 350);
            }
        }
        if (anim == 5) {
            if (right) {
                sprite.setTextureRect(IntRect(131, 0, 22, 66));
                sprite.setPosition(802, 350);
            }
            else {
                sprite.setTextureRect(IntRect(153, 0, -22, 66));
                sprite.setPosition(160, 350);
            }
        }
    }
};

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1000, 500), "Well wait!");

    Texture f;
    f.loadFromFile("fon.png");
    Sprite fon(f);
    
    Texture p, r;
    p.loadFromFile("player.png");
    r.loadFromFile("arm.png");
    Player player(p, r);

    Texture eg;
    eg.loadFromFile("egg.png");
    int nom[4];
    Egg egg[4];
    for (int i = 0; i < 4; i++) {
        nom[i] = i + 1;
        egg[i].set(eg, nom[i]);
    }
    int fal = rand() % 4;

    Texture s;
    s.loadFromFile("score.png");
    Score score(s);

    Texture up;
    up.loadFromFile("fal.png");
    Upast upast;
    upast.set(up);

    Texture l;
    l.loadFromFile("lose.png");
    Sprite lose[3];
    for (int i = 0; i < 3; i++) {
        lose[i].setTexture(l);
        lose[i].setPosition(400 + 70 * i, 70);
    }
    int prop = 0;

    Texture go;
    go.loadFromFile("gameover.png");
    Sprite gameover(go);
    gameover.setPosition(380, 120);

    bool game = true, right = true, over = false;

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (pos.x < 500)
            player.left = true;
        else
            player.left = false;

        if (pos.y > 250)
            player.up = false;
        else
            player.up = true;

        if (newgo) {
            if (fal == player.engine) {
                score.frame++;

                sound.cah.play();
            }
            else {
                upast.vid = true;
                game = false;

                if (fal > 1)
                    right = true;
                else
                    right = false;

                sound.pass.play();
            }
            
            fal = rand() % 4;

            for (int i = 0; i < 4; i++)
                egg[i].next = 0;

            newgo = false;
        }

        if (!game && upast.anim == 6 && !over) {
            prop++;
            
            if (prop != 3) {
                game = true;
                upast.anim = 1;
            }
            else {
                over = true;
                sound.gameover.play();
            }
        }

        if (game) {
            player.upate();
            for (int i = 0; i < 4; i++)
                if (fal == i)
                    egg[i].update();
        }
        else
            upast.update(right);
        score.update();
        window.clear(Color::White);
        window.draw(fon);
        window.draw(player.sprite);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (egg[j].vid[i] && fal == j)
                    window.draw(egg[j].sprite[i]);
        window.draw(player.arm);
        for (int i = 0; i < 2; i++)
            window.draw(score.sprite[i]);
        for (int i = 0; i < prop; i++)
            window.draw(lose[i]);
        if (upast.vid && !game)
            window.draw(upast.sprite);
        if (over)
            window.draw(gameover);
        window.display();
    }

    return 0;
}