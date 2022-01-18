/*
 * tinyFlashUtils.h
 *
 * Copyright (c) 2022, NAME, <EMAIL>
 * Created on: 2022-01-19 
 */
#ifndef TINYFLASH_TINYFLASHUTILS_H_
#define TINYFLASH_TINYFLASHUTILS_H_

#include <inttypes.h>
#include <stdio.h>

uint32_t tinyFlash_calc_crc32(uint32_t crc, const void *buf, size_t size);

#endif /* TINYFLASH_TINYFLASHUTILS_H_ */
