/*
 * main.c
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */

#include "flashEmulator/flashEmulator.h"

int main(int argc, char *argv[]) {
    struct fe_sector * sector1 = flashEmulator_create(1, 1024*128);
    struct fe_sector * sector2 = flashEmulator_create(2, 1024*128);

    flashEmulator_erase(sector1);
    flashEmulator_erase(sector2);


    flashEmulator_write_word(sector1, 0, 0xAABBCCDD);
    flashEmulator_write_word(sector1, 1024, 0xAABBCCDD);

    flashEmulator_write_half(sector2, 0, 0xAABB);
    flashEmulator_write_half(sector2, 2, 0xFEFE);

    flashEmulator_write_byte(sector1, 4, 0x01);
    flashEmulator_write_byte(sector2, 4, 0x02);

    flashEmulator_destory(sector1);
    flashEmulator_destory(sector2);

    return 0;
}
