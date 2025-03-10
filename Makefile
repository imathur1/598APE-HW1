FUNC := clang++
copt := -c 
OBJ_DIR := ./bin/
FLAGS := -O2 -lm -g -Werror -lprofiler -march=native -fopenmp -I./include

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
	./test.sh pianoroom 500 500 24
	./test.sh globe 1000 1000 24
	./test.sh elephant 200 200

view-profile:
	~/go/bin/pprof -http "0.0.0.0:8080" main.exe ./my_profile.prof
