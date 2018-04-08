#include <gb/gb.h>

#include "sprites.h"
#include "constants.h"

typedef unsigned char uint8_t;

uint8_t playerX = 80;
uint8_t playerY = 80;
uint8_t playerDirection = 0;

uint8_t playerTurnCooldown = 0;

void update_player_tiles();

void init()
{
    SPRITES_8x8;
    DISPLAY_OFF;

    // Let palette 1 have light grey as the transparent color:
    OBP1_REG = 0xe1;
    
    // load images here:
    set_sprite_data(PLAYER_TILE_START, sizeof(PLAYER_TILES) / 8, PLAYER_TILES);
    set_sprite_data(BULLET_TILES_START, 2, BULLET_TILES);
    set_sprite_data(ENEMY_TILES_START, ENEMY_TILES_COUNT, ENEMY_TILES);    

    update_player_tiles();

    DISPLAY_ON;

    SHOW_BKG;
    SHOW_SPRITES;
}

void update_player_tiles()
{
    uint8_t i = 0;
    uint8_t offsets[] = 
        {0, 2, 8, 10,
        1, 3, 9, 11,
        4, 6, 12, 14,
        5, 7, 13, 15};

    for(i = 0; i < 16; i++)
    {
        set_sprite_tile(PLAYER_SPRITE_START + i, PLAYER_TILE_START + playerDirection * 16 + offsets[i]);
        set_sprite_prop(PLAYER_SPRITE_START + i, S_PALETTE);
    }
}

void turn_player(uint8_t pad)
{
    if(playerTurnCooldown > 0) {
        playerTurnCooldown--;
        return;
    }

    if(pad & J_A) {
        if (playerDirection == 7) {
            playerDirection = 0;
        } else {
            playerDirection++;
        }
        update_player_tiles();
        playerTurnCooldown = TURN_COOLDOWN_TIME;
    } if(pad & J_B) {
        if (playerDirection == 0) {
            playerDirection = 7;
        } else {
            playerDirection--;
        }
        update_player_tiles();
        playerTurnCooldown = TURN_COOLDOWN_TIME;
    }

}

void draw_player()
{
    uint8_t x, y, i;
    i = PLAYER_SPRITE_START;
    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            move_sprite(i, playerX + x*8, playerY + y*8);
            i++;
        }
    }

}

void main(void)
{
    init();
    while(1) {
        // check input
        uint8_t pad = joypad();
        
        turn_player(pad);
        draw_player();
        
        // do collision detection
        wait_vbl_done();
    }
}
