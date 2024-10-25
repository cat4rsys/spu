debug := 0
secure := 0

CC := g++
CFLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SOURCES := source/log.cpp source/spu.cpp source/main.cpp source/stack.cpp source/utilities.cpp
OBJ := build/log.o build/spu.o build/main.o build/stack.o build/utilities.o

BUILD := build

INCLUDES := include
OUTPUT := spu

ifeq ($(debug), 1)
CFLAGS += -D DEBUG
endif

ifeq ($(secure), 1)
CFLAGS += -D SECURE
endif

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@

build/log.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/log.cpp -o $@

build/spu.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/spu.cpp -o $@

build/main.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/main.cpp -o $@

build/stack.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/stack.cpp -o $@

build/utilities.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/utilities.cpp -o $@

clean:
	rm build/*.o $(OUTPUT) main_logfile.htm func_logfile.htm
