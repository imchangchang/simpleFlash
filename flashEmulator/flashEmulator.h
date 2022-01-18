/*
 * flashEmulator.h
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */
#ifndef FLASHEMULATOR_FLASHEMULATOR_H_
#define FLASHEMULATOR_FLASHEMULATOR_H_

#include <inttypes.h>

struct fe_sector
{
    uint32_t sector_id;
    intptr_t start_address;
    uint32_t size;
    uint8_t * data_area;
};


struct fe_sector * flashEmulator_create(uint32_t sector_id, uint32_t size);
void flashEmulator_destory(struct fe_sector * sector);

void flashEmulator_erase(struct fe_sector* sector);
void flashEmulator_write_word(struct fe_sector* sector, uint32_t offset, uint32_t word);
void flashEmulator_write_half(struct fe_sector* sector, uint32_t offset, uint16_t half);
void flashEmulator_write_byte(struct fe_sector* sector, uint32_t offset, uint8_t byte);

#endif /* FLASHEMULATOR_FLASHEMULATOR_H_ */
