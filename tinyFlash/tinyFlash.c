/*
 * tinyFlash.c
 *
 * Copyright (c) 2022, cgeng, <imchangchang@gmail.com>
 * Created on: 2022-01-19 
 */
#include "tinyFlash.h"
#include "tinyFlashUtils.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TF_MAGIC (0xccefefcc)

struct tf_item {
    uint32_t magic;
    uint32_t key;
    uint32_t deleted;
    uint32_t real_len; /*real length in flash, include padding*/
    uint32_t len;
    uint32_t crc32;
    uint32_t payload[1];
};

struct tf_sector_hdr {
    uint32_t empty;
    uint32_t inuse;
};

struct tf_data {
    struct tf_sector_tbl *tbl;
    uint32_t inuse_sector;
} g_tf;

static uint32_t get_item_rlen(struct tf_item *item) {
    return sizeof(struct tf_item) + item->real_len - sizeof(uint32_t);
}
static uint32_t get_item_rlen_by_datalen(uint32_t len) {
    if (len % 4 == 0) {
        return sizeof(struct tf_item) + len - sizeof(uint32_t);
    } else {
        len += (4 - (len % 4));
        return sizeof(struct tf_item) + len - sizeof(uint32_t);
    }
}

static bool is_valid_item(struct tf_item *item) {
    return true;
}
static bool is_undelete_item(struct tf_item *item) {
    return item->deleted == 0xffffffff;
}

static struct tf_item* find_key(uint32_t key, struct tf_sector *sector) {
    intptr_t start_address = sector->sector_address;
    uint32_t offset = 0;
    struct tf_item *item = (struct tf_item*) (start_address + offset);

    while (item->magic == TF_MAGIC) {
        if (item->key == key && is_valid_item(item) && is_undelete_item(item)) {
            return item;
        }
        offset += get_item_rlen(item);
        if (offset >= sector->sector_size)
            break;
        item = (struct tf_item*) (start_address + offset);
    }
    return NULL;
}
static uint32_t find_write_pos(struct tf_sector *sector, uint32_t data_len) {
    intptr_t start_address = sector->sector_address;
    uint32_t offset = 0;
    struct tf_item *item = (struct tf_item*) (start_address + offset);

    while (item->magic == TF_MAGIC) {
        offset += get_item_rlen(item);
        if (offset >= sector->sector_size)
            return 0;
    }

    uint32_t rlen = get_item_rlen_by_datalen(data_len);
    if (rlen + offset >= sector->sector_size)
        return 0;
    return (start_address + offset);
}

static bool write_key(struct tf_sector *sector, uint32_t key, uint8_t *buf, uint32_t size) {
    intptr_t write_address = find_write_pos(sector, size);
    if (write_address == 0) {
        return false;
    }

    struct tf_item item;
    item.magic = TF_MAGIC;
    item.deleted = 0xffffffff;
    item.key = key;
    item.real_len = get_item_rlen_by_datalen(size);
    item.len = size;
    item.crc32 = tinyFlash_calc_crc32(TF_MAGIC, buf, size);

    uint32_t write_offset = write_address - sector->sector_address;
    uint32_t write_num = sizeof(struct tf_item) / sizeof(uint32_t) - 1;
    tinyFlash_sector_write_words(sector->sector_id, write_offset, (uint32_t *)&item, write_num);

    write_offset += write_num * sizeof(uint32_t);
    uint32_t pad_buf = 0;
    uint32_t pad_len = item.real_len - item.len;
    if (pad_len == 0) {
        tinyFlash_sector_write_words(sector->sector_id, write_offset, (uint32_t *)buf, item.real_len / sizeof(uint32_t));
    } else {
        uint32_t copy_idx = 0;
        uint32_t copy_len = sizeof(uint32_t) - pad_len;

        if (item.real_len > 4) {
            tinyFlash_sector_write_words(sector->sector_id, write_offset, (uint32_t *)buf, item.real_len / sizeof(uint32_t) - 1);
            copy_idx = size - sizeof(uint32_t);
        } else {
            copy_idx = 0;
        }
        memcpy(&pad_buf, &buf[copy_idx], copy_len);
        tinyFlash_sector_write_words(sector->sector_id, write_offset, (uint32_t *)&pad_buf, 1);
    }

    return true;

}
static void format_sector(struct tf_sector *sector) {
    struct tf_sector_hdr hdr = { .empty = 0x00000000, .inuse = 0xFFFFFFFF, };
    tinyFlash_sector_erase(sector->sector_id);
    write_key(sector, TF_KEY_SECTOR_HEADER,(uint8_t*) &hdr, sizeof(hdr));
}

void tinyFlash_init(void) {
    g_tf.tbl = tinyFlash_sector_tbl_get();
    struct tf_item *sector_1_hdr = find_key(TF_KEY_SECTOR_HEADER, &g_tf.tbl->sectors[0]);
    struct tf_item *sector_2_hdr = find_key(TF_KEY_SECTOR_HEADER, &g_tf.tbl->sectors[1]);

    if (sector_1_hdr == NULL || sector_2_hdr == NULL) {
        format_sector(&g_tf.tbl->sectors[0]);
        format_sector(&g_tf.tbl->sectors[1]);
    }

}

void tinyFlash_write(uint32_t key, uint8_t *buf, uint32_t size) {

}
bool tinyFlash_read(uint32_t key, uint8_t *buf, uint32_t size) {
    return false;
}
