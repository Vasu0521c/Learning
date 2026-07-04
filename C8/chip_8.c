#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

#include "raylib/src/raylib.h"

#define F 15

const int height = 1024;
const int widght  = 728;

typedef uint8_t byte;
typedef uint16_t bytes;

byte delay_timer = 0;
byte sound_timer = 0;

byte stack[12];
byte sp = 0;

byte memory[4096];
byte registers[16];

bytes program_counter = 0x200;

bytes virtual_window[64][32];

struct decoded_opcode{
    byte  regis_x;
    byte  regis_y;
    byte  regis_n;
    byte  regis_nn;
    bytes regis_nnn;
    bytes mem_address;
};

byte keys[] = {

    KEY_F,
    KEY_ONE,
    KEY_W,
    KEY_E,
    KEY_A,
    KEY_Z,
    KEY_S,
    KEY_Q,
    KEY_D,
    KEY_C,
    KEY_SPACE,
    KEY_TWO,
    KEY_THREE,
    KEY_G,
    KEY_V
};

const byte sprite_address[] = {

    0xF0, 0x90, 0x90, 0x90, 0xF0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xF0, 0x01, 0xF0, 0x80, 0xF0,
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    0x90, 0x90, 0xF0, 0x10, 0x10,
    0xF0, 0x80, 0xF0, 0x10, 0xF0,
    0xF0, 0x80, 0xF0, 0x90, 0xF0,
    0xF0, 0x10, 0x20, 0x40, 0x40,
    0xF0, 0x90, 0xF0, 0x90, 0xF0,
    0xF0, 0x90, 0xF0, 0x10, 0xF0,
    0xF0, 0x90, 0xF0, 0x90, 0x90,
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    0xF0, 0x80, 0xF0, 0x80, 0xF0,
    0xF0, 0x80, 0xF0, 0x80, 0x80
};

void operation_0(bytes opcode, struct decoded_opcode op) {

    switch(opcode) {
        case 0x00E0:
            ClearBackground(BLACK);
            break;
        case 0x00EE:
            sp--;
            program_counter = stack[sp];
            stack[sp] = 0;
            break;
    }
}

void operation_1(bytes opcode, struct decoded_opcode op) {

    program_counter = op.regis_nnn;
}

void operation_2(bytes opcode, struct decoded_opcode op) {

    stack[sp] = program_counter;
    sp++;
    program_counter = op.regis_nnn;
}

void operation_3(bytes opcode, struct decoded_opcode op) {

    if(registers[op.regis_x] == op.regis_nn) {
        program_counter += 2;
    }
}

void operation_4(bytes opcode, struct decoded_opcode op) {

    if(registers[op.regis_x] != op.regis_nn)
        program_counter += 2;
}

void operation_5(bytes opcode, struct decoded_opcode op) {

    if (op.regis_n == 0x0) {
        if(registers[op.regis_x] == registers[op.regis_y])
            program_counter += 2;
    }
}

void operation_6(bytes opcode, struct decoded_opcode op) {

    registers[op.regis_x] = op.regis_nn;
}

void operation_7(bytes opcode, struct decoded_opcode op) {

    registers[op.regis_x] += op.regis_nn;
}

void operation_8(bytes opcode, struct decoded_opcode op) {

    switch(op.regis_n) {
        case 0x0:
            registers[op.regis_x]  = registers[op.regis_y];
            break;
        case 0x1:
            registers[op.regis_x] |= registers[op.regis_y];
            break;
        case 0x2:
            registers[op.regis_x] &= registers[op.regis_y];
            break;
        case 0x3:
            registers[op.regis_x] ^= registers[op.regis_y];
            break;
        case 0x4:
            registers[F]          = ((registers[op.regis_x] + registers[op.regis_y]) > 255);
            registers[op.regis_x] += registers[op.regis_y];
            break;
        case 0x5:
            registers[F]          = ((registers[op.regis_x] - registers[op.regis_y]) > 0);
            registers[op.regis_x] -= registers[op.regis_y];
            break;
        case 0x6:
            registers[F]          = registers[op.regis_x] & 0x0F;
            registers[op.regis_x] >>= 1;
            break;
        case 0x7:
            registers[F]          = ((registers[op.regis_y] - registers[op.regis_x]) > 0);
            registers[op.regis_x]  = registers[op.regis_y] - registers[op.regis_x];
            break;
        case 0xE:
            registers[F]          = registers[op.regis_x] & 0x0F;
            registers[op.regis_x] <<= 1;
            break;
    }
}

void operation_9(bytes opcode, struct decoded_opcode op) {

    if (op.regis_n == 0x0) {
        if(registers[op.regis_x] != op.regis_y)
            program_counter += 2;
    }
}

void operation_A(bytes opcode, struct decoded_opcode op) {

    op.mem_address = op.regis_nnn;
}

void operation_B(bytes opcode, struct decoded_opcode op) {

    program_counter = op.regis_nnn + registers[0];
}

void operation_C(bytes opcode, struct decoded_opcode op) {

    registers[op.regis_x] = (rand() % 255) & op.regis_nn;
}

void operation_D(bytes opcode, struct decoded_opcode op) {

    byte i        = memory[op.mem_address];
    int x         = op.regis_x;
    int y         = op.regis_y;
    int a         = 0;
    int r         = 0;
    registers[F]  = 0;
    while(r < op.regis_n && x < 64) {
        while(y < 32) {
            a                    = virtual_window[x][y];
            virtual_window[x][y] = sprite_address[i];
            if (a == 1 && virtual_window[x][y] == 0)
                registers[F] = 1;
            y++;
            i++;
        }
        y = 0;
        r++;
    }
}

void operation_E(bytes opcode, struct decoded_opcode op) {

    switch(op.regis_nn) {
        case 0x9E:
            if(IsKeyPressed(registers[op.regis_x]))
                program_counter += 2;
            break;
        case 0xA1:
            if(IsKeyUp(registers[op.regis_x]))
                program_counter += 2;
            break;
    }
}

void operation_F(bytes opcode, struct decoded_opcode op) {

    byte *hell     = &(memory[op.mem_address]);
    byte *hell_b   = registers;
    switch(op.regis_nn) {
        case 0x07:
            registers[op.regis_x] = delay_timer;
            break;
        case 0x0A:
            registers[op.regis_x] = GetKeyPressed();
            break;
        case 0x15:
            delay_timer = registers[op.regis_x];
            break;
        case 0x18:
            sound_timer = registers[op.regis_x];
            break;
        case 0x1E:
            op.mem_address += registers[op.regis_x];
            break;
        case 0x29:
            op.mem_address = sprite_address[op.regis_x];
            break;
        case 0x33:
            bytes x                 = sprite_address[op.regis_x];
            memory[op.mem_address + 2] = x % 10;
            x                      /= 10;
            memory[op.mem_address + 1] = x % 10;
            x                      /= 10;
            memory[op.mem_address + 0] = x;
            break;
        case 0x55:
            memcpy(hell, hell_b, op.regis_x);
            break;
        case 0x65:
            memcpy(hell_b, hell, op.regis_x);
            break;
    }
}

void test_start(byte* memory) {

    struct decoded_opcode op;
    bytes opcode = memory[program_counter];
    opcode       = opcode << 8;
    opcode       = opcode | memory[program_counter + 1];
    program_counter += 2;
    op.regis_x   = (opcode & 0x0F00) >> 8;
    op.regis_y   = (opcode & 0x00F0) >> 4;
    op.regis_n   = opcode & 0x000F;
    op.regis_nn  = opcode & 0x00FF;
    op.regis_nnn = opcode & 0x0FFF;
    switch(opcode >> 12) {
        case 0x0:
            operation_0(opcode, op);
            break;
        case 0x1:
            operation_1(opcode, op);
            break;
        case 0x2:
            operation_2(opcode, op);
            break;
        case 0x3:
            operation_3(opcode, op);
            break;
        case 0x4:
            operation_4(opcode, op);
            break;
        case 0x5:
            operation_5(opcode, op);
            break;
        case 0x6:
            operation_6(opcode, op);
            break;
        case 0x7:
            operation_7(opcode, op);
            break;
        case 0x8:
            operation_8(opcode, op);
            break;
        case 0x9:
            operation_9(opcode, op);
            break;
        case 0xA:
            operation_A(opcode, op);
            break;
        case 0xB:
            operation_B(opcode, op);
            break;
        case 0xC:
            operation_C(opcode, op);
            break;
        case 0xD:
            operation_D(opcode, op);
            break;
        case 0xE:
            operation_E(opcode, op);
            break;
        case 0xF:
            operation_F(opcode, op);
            break;
        default:
            break;
    }
}

void draw_in_screen() {

    int i,j;
    i = 0;
    j = 0;
    while(i < 64) {
        while(j < 32) {
            if(virtual_window[i][j] != 0)
                DrawRectangle(i, j, 10, 10, WHITE);
            j++;
        }
        j = 0;
        i++;
    }
}

int main() {

    FILE *game = fopen("../C8/2-ibm-logo.ch8", "rb");
    char *game_name = "IBM Logo";
    memcpy(memory, sprite_address, 80);
    fseek(game, 0L, SEEK_END);
    bytes size = ftell(game);
    fseek(game, 0L, SEEK_SET);
    fread(memory + program_counter, 1, size, game);
    InitWindow(height, widght, game_name);
    InitAudioDevice();
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        test_start(memory);
        BeginDrawing();
        ClearBackground(BLACK);
        draw_in_screen();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
