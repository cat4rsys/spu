CC := g++
CFLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SOURCES := source/asm.cpp source/main.cpp source/input.cpp source/utilities.cpp
OBJ := build/asm.o build/main.o build/input.o build/utilities.o

BUILD := build

INCLUDES := include
OUTPUT := assemble

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@

build/asm.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/asm.cpp -o $@

build/main.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/main.cpp -o $@

build/input.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/input.cpp -o $@

build/utilities.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source/utilities.cpp -o $@

clean:
	rm build/*.o $(OUTPUT)
