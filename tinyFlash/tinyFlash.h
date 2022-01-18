/*
 * tinyFlash.h
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */
#ifndef TINYFLASH_TINYFLASH_H_
#define TINYFLASH_TINYFLASH_H_

#include <stdbool.h>
#include <inttypes.h>

enum
{
    TF_KEY_SECTOR_HEADER = 0,
};

struct tf_sector
{
    uint32_t sector_id;
    uint32_t sector_size;
    intptr_t sector_address;
};

struct tf_sector_tbl
{
    struct tf_sector sectors[2];
};



/*Port Functions*/
struct tf_sector_tbl * tinyFlash_sector_tbl_get(void);
void tinyFlash_sector_erase(uint32_t sector_id);
void tinyFlash_sector_write_words(uint32_t sector_id, uint32_t offset, uint32_t * words, uint32_t num);
void tinyFlash_sector_write_halfs(uint32_t sector_id, uint32_t offset, uint16_t * halfs, uint32_t num);
void tinyFlash_sector_write_bytes(uint32_t sector_id, uint32_t offset, uint8_t * bytes,  uint32_t num);

/*Interface*/
void tinyFlash_init(void);
void tinyFlash_write(uint32_t key, uint8_t * buf, uint32_t size);
bool tinyFlash_read(uint32_t key, uint8_t * buf, uint32_t size);

#endif /* TINYFLASH_TINYFLASH_H_ */
