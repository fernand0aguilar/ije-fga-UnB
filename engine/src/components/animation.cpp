#include"components/animation.hpp"

using namespace engine;

Animation::~Animation(){

}

bool Animation::init(){
    
    Log::instance.info("Iniciando componente de animacao");

    if(main_path == ""){
        Log::instance.error("Caminho inválido!");
        return false;
    }

    SDL_Surface *image = IMG_Load(main_path.c_str());

    if(image == NULL){
        // SDL_IMG_ERROR("Could not load image from path !" << main_path);
    }

    main_texture = SDL_CreateTextureFromSurface(Game::instance.main_canvas, image);

    if(main_texture == NULL){
        // SDL_ERROR("Could not create texture from image");
        return false;
    }

    //Pegando os sizes padrões da imagem, por isso precisa ser desenhada no tamanho desejado
    main_game_object->set_size(image->w, image->h);

    SDL_FreeSurface(image);

    //divide imagem
    //ler matriz de imagems em um arquivo
    int cont = 0;
    for (int h = 0; h < image->h && cont < m_num_image; h += m_heightDiv) {
        for(int w = 0; w < image->w && cont < m_num_image; w += m_widthDiv){
            SDL_Rect *rect = new SDL_Rect();
            rect->x = w;
            rect->y = h;
            rect->w = m_widthDiv;
            rect->h = m_heightDiv;
            imageVector.push_back(rect);
            cont++;
        }
    }

    main_animation[BEGIN] = 0;
    main_animation[END] = imageVector.size();
    
    
    return true;
}

void Animation::setAnimation(std::string animationName,int begin,int end){
    int animationsFrame[2];
    animationsFrame[0] = begin;
    animationsFrame[1] =  end;

    memcpy(animationMap[animationName],animationsFrame,sizeof(int)*2);
}

bool Animation::useAnimation(std::string animationName){

    main_animation[BEGIN] = (animationMap[animationName])[BEGIN];
    main_animation[END] = (animationMap[animationName])[END]; 
    main_frame = main_animation[BEGIN];

    return true;
}

void Animation::setDelay(int delay){
    this->delay = delay;
}

void Animation::draw(){


    SDL_Rect *renderQuad = new SDL_Rect();
    renderQuad->x = main_game_object->main_positionX;
    renderQuad->y = main_game_object->main_positionY;
    renderQuad->w = imageVector[main_frame]->w;
    renderQuad->h = imageVector[main_frame]->h;


    if(Game::instance.timer->getTicks() - timestep >= delay){
        main_frame++;
        timestep = Game::instance.timer->getTicks();
    }

    if(main_frame == main_animation[END]){
            main_frame = main_animation[BEGIN];
    }

    
    SDL_RenderCopy(Game::instance.main_canvas, main_texture, imageVector[main_frame] , renderQuad);
}