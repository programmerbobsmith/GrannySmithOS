# MakeFile for GrannySmithOS

NAME = MONTEREY
ICON = icon.png
DESCRIPTION = "GrannySmithOS v 12.1.1"
COMPRESSED = YES
COMPRESSED_MODE = zx7
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

include $(shell cedev-config --makefile)