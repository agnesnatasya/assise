#! /bin/bash

PATH=$PATH:.
PROJECT_ROOT=../..

MLFS_PROFILE=1 LD_PRELOAD=$PROJECT_ROOT/libfs/build/libmlfs.so ${@}
