TARGET = life
LIBS = -lSDL2 -lGL

CC = g++
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
SHADERS = $(wildcard src/shader/*.glsl)
COMMA = ,
.PHONY: clean, install, uninstall

$(TARGET): $(OBJECTS) $(SHADERS)
	$(CC) -o $@ $(OBJECTS) $(LIBS) -no-pie -Wl,--format=binary $(addprefix -Wl$(COMMA), $(SHADERS)) -Wl,--format=default

clean:
	$(RM) -r build/
	$(RM) -r $(TARGET)

install:

uninstall:

define OBJECT_RULE
build/$(shell $(CC) -MM $(1) | sed ':a;N;s/ \\\n / /g')
	mkdir -p build/
	$$(CC) -g -c -o $$@ $$<
endef
$(foreach src, $(SOURCES), $(eval $(call OBJECT_RULE,$(src))))
