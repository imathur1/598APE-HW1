FUNC := clang++
copt := -c 
OBJ_DIR := ./bin/
FLAGS := -O3 -lm -g -Werror -lprofiler -fopenmp -msse2 -mavx2 -I./include

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR),$(notdir $(CPP_FILES:.cpp=.obj)))

TEXTURE_CPP_FILES := $(wildcard src/Textures/*.cpp)
TEXTURE_OBJ_FILES := $(addprefix $(OBJ_DIR)Textures/,$(notdir $(TEXTURE_CPP_FILES:.cpp=.obj)))

ifndef PROFILE
    PROFILE := 0
endif

.PHONY: clean test view-profile

all:
	cd ./src && make
	$(FUNC) -DPROFILE=$(PROFILE) ./main.cpp -o ./main.exe ./src/*.obj ./src/Textures/*.obj $(FLAGS)

clean:
	cd ./src && make clean
	rm -f ./*.exe
	rm -f ./*.obj

test:
	./test.sh pianoroom

view-profile:
	~/go/bin/pprof -http "0.0.0.0:8080" main.exe ./my_profile.prof
