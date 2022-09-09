SHELL=/usr/bin/zsh

SRC := ./src
BIN := ./bin
OBJ := ./bin/obj
TARGET := chip8

C_INCLUDE := $(SRC)/include
C_DRIVER_SRC := $(SRC)/system/main.c
C_DRIVER_OBJ = $(C_DRIVER_SRC:%.c=%.o)
C_DIR_LIST := error,memory,processor,screen,processor/opcode,resources,fonts
C_SRC := $(shell ls $(SRC)/{$(C_DIR_LIST)}/*.c)
C_OBJ = $(C_SRC:%.c=%.o)
CC := gcc
C_FLAGS := -D_POSIX_C_SOURCE -std=c99 -fstack-protector-all -iquote$(C_INCLUDE)
C_DEBUG := -O0 -pedantic -fsanitize=leak -Wall -Werror -pedantic -g2 -DDEBUG
C_RELEASE := -O2

SDL_FLAGS := `pkg-config --cflags --libs sdl2`

.PHONY: all clean debug release test_rom test_mem test_processor

debug: C_FLAGS := $(C_FLAGS) $(C_DEBUG)
debug: $(TARGET)

release: C_FLAGS := $(C_FLAGS) $(C_RELEASE)
release: $(TARGET)

test_opcode: C_FLAGS := $(C_FLAGS) $(C_DEBUG)
test_opcode: C_DRIVER_SRC := $(SRC)/system/test_opcode.c
test_opcode: $(TARGET)

test_rom: C_FLAGS := $(C_FLAGS) $(C_DEBUG)
test_rom: C_DRIVER_SRC := $(SRC)/system/test_rom.c
test_rom: $(TARGET)

test_mem: C_FLAGS := $(C_FLAGS) $(C_DEBUG)
test_mem: C_DRIVER_SRC := $(SRC)/system/test_mem.c
test_mem: $(TARGET)

test_processor: C_FLAGS := $(C_FLAGS) $(C_DEBUG)
test_processor: C_DRIVER_SRC := $(SRC)/system/test_processor.c
test_processor: $(TARGET)

$(TARGET): $(C_OBJ)
	$(CC) $(C_FLAGS) -c -o $(C_DRIVER_OBJ) $(C_DRIVER_SRC) $(SDL_FLAGS)
	$(CC) $(C_FLAGS) -o $@ $^ $(C_DRIVER_OBJ) $(SDL_FLAGS)
	@mv $^ $(C_DRIVER_OBJ) $(OBJ)
	@mv $@ $(BIN)

%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $< $(SDL_FLAGS)

clean:
	@if [[ -f "$(SRC)/*/*.o" ]]; then\
		@rm $(SRC)/*/*.o;\
	elif [[ -f "$(BIN)/$(TARGET)" ]]; then\
		rm $(BIN)/$(TARGET) $(OBJ)/*.o;\
	fi
