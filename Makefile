CC = gcc

BIN = bin
TEST_BIN = tests/bin

DOCS = docs
DOC_CONFIG = doxygen.config

OPTIONS = -Wall -Wpedantic -Werror

SERVER_OBJS = src/player.c src/packet.c src/input.c src/server/*.c

GLFW = -I lib/glfw/include/ -L lib/glfw/build/src -lglfw3 -lm -ldl -pthread
CGLM = -I lib/cglm/include/ -L lib/cglm/build/ -lcglm

libs:
	cd lib/unitc && make build
	cd lib/cglm && mkdir -p build && cd build && cmake .. && make
	cd lib/doxygen && cmake -G "Unix Makefiles"
	cd lib/doxygen && make

dirs:
	mkdir -p ./$(BIN)

test: libs
	mkdir -p $(TEST_BIN)
	$(CC) src/packet.c tests/packet_test.c -o $(TEST_BIN)/packet_test -L lib/unitc/lib -lunitc -I include/ -I lib/unitc/include/

docs:
	lib/doxygen/bin/doxygen $(DOC_CONFIG)

server: dirs
	$(CC) $(SERVER_OBJS) -o $(BIN)/server -I include/ $(GLFW) $(CGLM) $(OPTIONS)

client: dirs
	$(CC) src/glad/glad.c -c -I include/
	$(CC) src/*.c src/client/*.c src/rendering/*.c src/utils/*.c glad.o -o $(BIN)/client -I include/ $(GLFW) $(CGLM) $(OPTIONS)
	rm glad.o

clean:
	rm -rf $(BIN) $(TEST_BIN) $(DOCS)
