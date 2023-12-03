/**
* Author: Matthew Gong
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "Scene.h"


void createBasicEnemy(GLuint& sprite_tileset_texture_id, Entity* enemy, glm::vec3 position){
    //follow
    enemy->set_entity_type(ENEMY);
    enemy->set_ai_type(GUARD);
    enemy->set_ai_state(IDLE);
    enemy->m_texture_id = sprite_tileset_texture_id;
    enemy->set_position(position);
    enemy->set_movement(glm::vec3(0.0f));
    enemy->set_speed(0.5f);
    enemy->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    //set_animation
    enemy->m_animation_cols = 9;
    enemy->m_animation_rows  = 3;
    enemy->m_animation_indices = new int[2] {2,3};
    enemy->m_animation_frames = 2;
    enemy->m_animation_index = 0;
    enemy->m_animation_time = 0.0f;
}
void createFlyEnemy(GLuint& sprite_tileset_texture_id, Entity* enemy, glm::vec3 position){
    enemy->set_entity_type(ENEMY);
    enemy->set_ai_type(FLY);
    enemy->set_ai_state(IDLE);
    enemy->m_texture_id = sprite_tileset_texture_id;
    enemy->set_position(position);
    enemy->set_movement(glm::vec3(0.0f));
    enemy->set_speed(0.5f);
    enemy->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    //set animation
    enemy->m_animation_cols    = 9;
    enemy->m_animation_rows    = 3;
    enemy->m_animation_indices = new int[3] {24,25,26};
    enemy->m_animation_frames  = 3;
    enemy->m_animation_index   = 0;
    enemy->m_animation_time    = 0.0f;
}

void createRamEnemy(GLuint& sprite_tileset_texture_id, Entity* enemy, glm::vec3 position){
    enemy->set_entity_type(ENEMY);
    enemy->set_ai_type(RAM);
    enemy->set_ai_state(IDLE);
    enemy->m_texture_id = sprite_tileset_texture_id;
    enemy->set_position(position);
    enemy->set_movement(glm::vec3(0.0f));
    enemy->set_speed(0.5f);
    enemy->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    //set animation
    enemy->m_animation_cols = 9;
    enemy->m_animation_rows = 3;
    enemy->m_animation_indices = new int[2] {21,22};
    enemy->m_animation_frames = 2;
    enemy->m_animation_index = 0;
    enemy->m_animation_time = 0.0f;
}

void createEndGoal(GLuint& sprite_tileset_texture_id, Entity* goal, glm::vec3 position){
    goal->set_entity_type(END_GOAL);
    goal->m_texture_id = sprite_tileset_texture_id;
    goal->set_position(position);
    goal->set_movement(glm::vec3(0.0f));
    goal->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    //set animation
    goal->m_animation_cols = 20;
    goal->m_animation_rows = 9;
    goal->m_animation_indices = new int[2] {111,112};
    goal->m_animation_frames = 2;
    goal->m_animation_index = 0;
    goal->m_animation_time = 0.0f;
}
