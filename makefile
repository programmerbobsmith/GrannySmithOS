# MakeFile for GrannySmithOS

NAME = MACTEST #MONTERY
ICON = icon.png
DESCRIPTION = "GrannySmithOS v 12.1.1"
COMPRESSED = YES
COMPRESSED_MODE = zx7
#ARCHIVED = YES # DEBUG

CFLAGS = -Wall -Wextra -Oz -Wno-error=implicit-function-declaration
CXXFLAGS = -Wall -Wextra -Oz -Wno-error=implicit-function-declaration

include $(shell cedev-config --makefile)
