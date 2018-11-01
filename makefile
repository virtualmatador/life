TARGET = life
LIBS = -lSDL2 -lGL

DEBUG := $(if $(shell git symbolic-ref --short HEAD | grep master), , -g)
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(SOURCES))
SHADERS := $(wildcard src/shader/*.glsl)

CC = g++
COMMA = ,

.PHONY: clean, install, uninstall

$(TARGET): $(OBJECTS) $(SHADERS)
	$(CC) -o $@ $(OBJECTS) $(LIBS) -no-pie -Wl,--format=binary $(addprefix -Wl$(COMMA), $(SHADERS)) -Wl,--format=default

clean:
	$(RM) -r build/
	$(RM) -r $(TARGET)

install:
		sudo cp $(TARGET) /usr/local/sbin/

uninstall:
		sudo $(RM) /usr/local/sbin/$(TARGET)

define OBJECT_RULE
build/$(subst $() \,,$(shell $(CC) -MM $(1)))
	mkdir -p build/
	$$(CC) $(DEBUG) -c -o $$@ $$<
endef
$(foreach src, $(SOURCES), $(eval $(call OBJECT_RULE,$(src))))
