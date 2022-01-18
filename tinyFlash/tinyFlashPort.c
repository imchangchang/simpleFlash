/*
 * tinyFlashPort.c
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */
#include "tinyFlash.h"
#include <stdlib.h>

struct tf_sector_tbl * tinyFlash_sector_tbl_get(void)
{
    return NULL;
}
void tinyFlash_sector_erase(uint32_t sector_id)
{

}
void tinyFlash_sector_write_words(uint32_t sector_id, uint32_t offset, uint32_t * words, uint32_t num)
{

}
void tinyFlash_sector_write_halfs(uint32_t sector_id, uint32_t offset, uint16_t * halfs, uint32_t num)
{

}
void tinyFlash_sector_write_bytes(uint32_t sector_id, uint32_t offset, uint8_t * bytes,  uint32_t num)
{

}
