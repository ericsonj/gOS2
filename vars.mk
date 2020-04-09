PROJECT         = gOS2
PROJECT_OUT     = Release/Objects

CC         := gcc
CXX        := g++
LD         := gcc
AR         := ar
AS         := as
OBJCOPY    := objcopy
SIZE       := size
OBJDUMP    := objdump

# MACROS
COMPILER_FLAGS += -D_DEFAULT_SOURCE
# MACHINE-OPTS
COMPILER_FLAGS += 
# OPTIMIZE-OPTS
COMPILER_FLAGS += 
# OPTIONS
COMPILER_FLAGS += 
# DEBUGGING-OPTS
COMPILER_FLAGS += -g3 
# PREPROCESSOR-OPTS
COMPILER_FLAGS += -MP -MMD 
# WARNINGS-OPTS
COMPILER_FLAGS += 
# CONTROL-C-OPTS
COMPILER_FLAGS += -std=c99 
# GENERAL-OPTS
COMPILER_FLAGS += 
# LIBRARIES
COMPILER_FLAGS += `pkg-config --libs glib-2.0` `pkg-config --libs --cflags gio-2.0` 

# LINKER-SCRIPT
LDFLAGS += 
# MACHINE-OPTS
LDFLAGS += 
# GENERAL-OPTS
LDFLAGS += 
# LINKER-OPTS
LDFLAGS += 
# LIBRARIES
LDFLAGS += `pkg-config --libs glib-2.0` `pkg-config --libs --cflags gio-2.0` 
