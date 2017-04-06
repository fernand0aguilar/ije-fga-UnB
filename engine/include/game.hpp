#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <unordered_map>
#include <utility>

#include "sdl2core.hpp"
#include "logger.hpp"

#include "Timer.hpp"
#include "scene.hpp"

namespace engine{

    class Game{
    public:
        Game(std::string name, std::pair<int,int>window_size)
        :main_name(name), main_window_size(window_size),
        main_window(NULL), main_canvas(NULL),
        main_background_color({0xff, 0xff, 0xff, 0xff}),
        current_scene(NULL){};

        //Game loop
        void run();

        //Inicializa SDL
        bool startSDL();

        //Cria janela
        bool createWindow();

        //Destroi janela
        void destroyWindow();

        //Desliga SDL
        void offSDL();

        //Adiciona nova cena na lista de cenas
        bool add_scene(Scene &scene);

        //Muda a cena que está acontecendo
        bool change_scene(const std::string &id);
        SDL_Renderer* main_canvas;

        Timer *timer;

    private:
        SDL_Window *main_window;

        std::string main_name;
        std::pair<int,int> main_window_size;
        // SDL_Renderer* main_canvas;

        SDL_Color main_background_color;

        std::unordered_map <std::string, Scene *> scenes_list;

        Scene *current_scene;

    protected:
        Log log;
    };
}

#endif
