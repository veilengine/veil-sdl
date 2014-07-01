CPP_FILES = $(shell find src/ -type f -name '*.cpp')
OBJ_FILES = $(CPP_FILES:src/%.cpp=obj/%.o)
CXX_FLAGS = -g -Wall -std=c++11 -I./include -I../veil/include
RM_RF := rm -rf
RM_F := rm -f

# all also makes the game
.PHONY: all
all: static

lib:
	@mkdir $@

obj/%.o: src/%.cpp
	@-mkdir -p $(dir $@)
	$(CXX) -c -fPIC $(CXX_FLAGS) -o $@ $<

.PHONY: static
static: lib lib/libveilsdl.a
lib/libveilsdl.a: $(OBJ_FILES)
	$(AR) rcs $@ $^

.PHONY: shared
shared: lib lib/libveilsdl.so
lib/libveilsdl.so: $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -shared -o $@ $^

.PHONY: clean
clean:
	@-$(RM_RF) lib obj
