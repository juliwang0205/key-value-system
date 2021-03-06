/*============================================================================
# Author: Wade Leng
# E-mail: wade.hit@gmail.com
# Last modified: 2011-12-16 15:18
# Filename: sync.h
# Description: 
============================================================================*/
#ifndef KVS_SYNC
#define KVS_SYNC

#include "type.h"

int sync_init(char* pathname, int file_len, char* sync_log);
int sync_read(char* mem, int size, OFFSET_T disk_offset);
int sync_write(const char* mem, int size, OFFSET_T disk_offset);
int sync_flush();
int sync_exit();

#endif
