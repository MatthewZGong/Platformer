/**
* Author: Matthew Gong
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 24
#define LEVEL_HEIGHT 5
const int E = -1;

int LEVEL_A_DATA[] =
{
    E, E, E, E, E, E, E, E,                        E, E, E, E,E,E, E, E, E, E, E, E, 1, 2, 2, 3,
    E, E, E, E, E, E, E, E,                        1, 2, 2, 3,E,E, E, E, E, E, E, E, E, E, E, E,
    21, 23, E,  E,E, E, E, E,                      E, E, E,E,E, E, E, E, 21, 22, 22, 23,E,E, E, E,
    4, 4, 22, 22, 22, 22, 22, 23,                      E, E,E,E, 21, 22, 22, 22, 4, 4, 4, 4, E, E,E, E,
    4, 4, 4, 4, 4, 4, 4, 4,                         E, E,E,E, 4, 4, 4, 4, 4, 4, 4, 4, E, E,E, E,
};

LevelA::LevelA(){
    g_number_of_enemies = 3;
    g_game_state.next_scene_id = Level3;
    g_game_state.state = 0;


}
LevelA::~LevelA()
{
    delete [] g_game_state.enemies;
    delete    g_game_state.player;
    delete    g_game_state.map;
    delete goal;
    Mix_FreeChunk(g_game_state.jump_sfx);
    Mix_FreeMusic(g_game_state.bgm);
}

void LevelA::initialise()
{
  
    g_game_state.state = 0;

    // ————— MAP SET-UP ————— //
    GLuint map_texture_id = Utility::load_texture(MAP_TILESET_FILEPATH);
    g_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_A_DATA, map_texture_id, 1.0f, 20, 9);


    // ––––– PLAYER ––––– //
    // Existing
    GLuint sprite_tileset_texture_id = Utility::load_texture(SPRITE_TILESET_FILEPATH);

    
    g_game_state.player = new Entity();
    g_game_state.player->set_position(glm::vec3(0.0f, 2.0f, 0.0f));
    g_game_state.player->set_movement(glm::vec3(0.0f));
    g_game_state.player->set_speed(1.5f);
    g_game_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    g_game_state.player->m_texture_id = sprite_tileset_texture_id;
    g_game_state.player->set_entity_type(PLAYER);

    g_game_state.player->m_animation_cols    = 9;
    g_game_state.player->m_animation_rows    = 3;
    g_game_state.player->m_animation_indices = new int[2] {6,7};
    g_game_state.player->m_animation_frames  = 2;
    g_game_state.player->m_animation_index   = 0;
    g_game_state.player->m_animation_time    = 0.0f;


    g_game_state.player->set_height(0.9f);
    g_game_state.player->set_width(0.9f);

    // Jumping
    g_game_state.player->set_jumping_power(6.0f);

    // ––––– ENEMY––––– //

    g_game_state.enemies = new Entity[g_number_of_enemies];
    //follow
    createBasicEnemy(sprite_tileset_texture_id, g_game_state.enemies ,glm::vec3(6.5f, 0.0f, 0.0f));
    //fly
    createFlyEnemy(sprite_tileset_texture_id, g_game_state.enemies+1, glm::vec3(12.0f, 2.0f, 0.0f));
    //ram
    createRamEnemy(sprite_tileset_texture_id, g_game_state.enemies+2, glm::vec3(23.0f, 2.0f, 0.0f));
    
    GLuint sprite_goal_tileset_texture_id = Utility::load_texture(MAP_TILESET_FILEPATH);
    goal = new Entity();
    createEndGoal(sprite_goal_tileset_texture_id, goal, glm::vec3(23.0f, 2.0f, 0.0f));

    
    // ––––– AUDIO STUFF ––––– //
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    g_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(g_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4.0f);

    g_game_state.jump_sfx = Mix_LoadWAV(BOUNCING_SFX_FILEPATH);

    
    // ––––– GENERAL ––––– //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void LevelA::update(float delta_time)
{
    g_game_state.player->update(delta_time, g_game_state.player, g_game_state.enemies, g_number_of_enemies, g_game_state.map);
    
    for (int i = 0; i < g_number_of_enemies; i++)
    {
        g_game_state.enemies[i].update(delta_time, g_game_state.player, 0, 0, g_game_state.map);
    }
    
    goal->update(delta_time, g_game_state.player, 0, 0, g_game_state.map);
    if(goal->get_dead())
        g_game_state.state = 1;
}


void LevelA::render(ShaderProgram *program)
{
    g_game_state.map->render(program);
    g_game_state.player->render(program);
    goal->render(program);
    for (int i = 0; i < g_number_of_enemies; i++)
    {
        g_game_state.enemies[i].render(program);
    }
}
