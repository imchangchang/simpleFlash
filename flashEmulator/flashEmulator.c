/*
 * flashEmulator.c
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "flashEmulator.h"

struct fe_sector* flashEmulator_create(uint32_t sector_id, uint32_t size) {
    struct fe_sector *sector = (struct fe_sector*) malloc(sizeof(struct fe_sector));
    assert(sector);

    sector->data_area = (uint8_t*) malloc(size);
    assert(sector->data_area);

    sector->sector_id = sector_id;
    sector->size = size;
    sector->start_address = (intptr_t)sector->data_area;

    return sector;
}

void flashEmulator_destory(struct fe_sector *sector) {
    assert(sector);
    assert(sector->data_area);

    free(sector->data_area);
    free(sector);
}

void flashEmulator_erase(struct fe_sector *sector) {
    assert(sector);
    assert(sector->data_area);

    memset(sector->data_area, 0xff, sector->size);

}
void flashEmulator_write_word(struct fe_sector *sector, uint32_t offset, uint32_t word) {
    assert(sector);
    assert(sector->data_area);

    uint32_t * dest = (uint32_t*)(sector->start_address + offset);
    *dest = word;

}
void flashEmulator_write_half(struct fe_sector *sector, uint32_t offset, uint16_t half) {
    assert(sector);
    assert(sector->data_area);
    uint16_t * dest = (uint16_t*)(sector->start_address + offset);
    *dest = half;

}
void flashEmulator_write_byte(struct fe_sector *sector, uint32_t offset, uint8_t byte) {
    assert(sector);
    assert(sector->data_area);
    uint8_t * dest = (uint8_t*)(sector->start_address + offset);
    *dest = byte;

}
