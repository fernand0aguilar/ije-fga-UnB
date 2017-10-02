/**
    \file monsterAI.cpp
    This file implements the MonsterAI class
*/
#include "monsterAI.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>

unsigned int time_damage;

const int PLAYER_DISTANCE = 850;
const int PLAYER_ATTACK_DISTANCE = 150;

/**
    This method initiates the Class MonsterAI in the game
    \return return a true value that make the MonsterAI active
*/
bool MonsterAI::init() {

    _main_game_object->main_positionY = ground - _main_game_object->main_height;
    _main_game_object->main_positionX = 400;
    horizontal_motion_units = ( rand() % 3 ) + 1;
    life_points = 2;

    return true;

}

/**
    This method is responsible for updating the monster in walk and attack que monster in the game.
*/
void MonsterAI::update() {

    m_monster_controler->play_animation("monster_walk", true);
    apply_gravity();

    move_monster();
    receive_damage();
    process_position();
    jump_monster();


    if( _main_game_object->main_positionX < 0 ||
        _main_game_object->main_positionX +
        _main_game_object->main_width > 800 ) {
        _main_game_object->setState(GameObject::State::disabled);
    }

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "player") ) {
        m_monster_controler->play_animation("monster_attack");
    }

}
/**
    This method is responsible for possibility the monster to see player in the game
    \return return true for prayer see and false see not player
*/

bool MonsterAI::sees_player() {

    if( fabs(_main_game_object->main_positionX - m_player->main_positionX) <=
        PLAYER_DISTANCE - 100 ) {
        return true;
    }
    else {
        return false;
    }

}


/**
    This method is responsible for possibility the monster jump in the game

*/

void MonsterAI::jump_monster() {

    // Monster jump

    bool isOnGround = Game::instance.collision_manager->checkCollision(m_player,
                      "ground");

    if( sees_player() && isOnGround &&
        _main_game_object->main_positionY > m_player->main_positionY ) {
        vertical_position -= jump_size;
    }

}

/**
    This method is responsible for move monster in direction the player in the game

*/

void MonsterAI::move_monster() {

    bool seeing_player = sees_player();

    if( seeing_player && !has_damage &&
        m_player->main_positionX > _main_game_object->main_positionX ) {
        m_monster_controler->flipping(true);
        _main_game_object->main_positionX += horizontal_motion_units;
    }

    if( seeing_player && !has_damage &&
        m_player->main_positionX < _main_game_object->main_positionX ) {
        m_monster_controler->flipping(false);
        _main_game_object->main_positionX -= horizontal_motion_units;
    }

}

/**
    This method is responsible for incrementar the vertical position que monster im game
*/

void MonsterAI::process_position() {

     // std::cout<<dy<<std::endl;

    _main_game_object->main_positionY += vertical_position; // Current velocity components.

}

/**
    This method is responsible for increment the vertical position of the monster
*/

void MonsterAI::apply_gravity() {

    /*
        if(_main_game_object->main_positionY > (ground -
             _main_game_object->main_height)){
            _main_game_object->main_positionY = ground -
            _main_game_object->main_height;
        }
    */

    if( !has_ground() ) {
        vertical_position += gravity;
    }
    else {
        vertical_position = 0;
    }

}

/**
    This method is responsible for if you have floor to monster floor
*/

bool MonsterAI::has_ground() {

    ground_obj = Game::instance.collision_manager->checkCollision(
                 _main_game_object, "ground");

    if( ground_obj && vertical_position >= 0 ) {
        if( vertical_position > 0 ) {
            _main_game_object->main_positionY = ground_obj->main_positionY -
            _main_game_object->main_height;
        }

        return true;
    }

    return false;

}


/**
    This method is responsible for damage monster in the game for
*/

void MonsterAI::receive_damage() {

    bullet = Game::instance.collision_manager->checkCollision(
             _main_game_object, "bullet");

    if( Game::instance.collision_manager->checkCollision(
        _main_game_object, "attack_box") || bullet ) {

        m_monster_controler->play_animation("monster_damage");

        if( bullet ) {
            bullet->setState(GameObject::State::disabled);
        }

        has_damage = true;
        if( side == RIGHT ) {

            // _main_game_object->main_positionX -= 10;

        }
        if( side == LEFT ) {

            // _main_game_object->main_positionX += 10;

        }
        if( Game::instance.timer->getTicks() > time_damage ) {
            life_points--;
            time_damage = Game::instance.timer->getTicks() + 1000;
        }
        if( life_points <= 0 ) {
            _main_game_object->setState(GameObject::State::disabled);
            life_points = 3;

            // Game::instance.change_scene("Win Scene");

        }
    }
    else {
        has_damage = false;
    }

}

void MonsterAI::bullet_damage() {}

MonsterAI::~MonsterAI() {}
