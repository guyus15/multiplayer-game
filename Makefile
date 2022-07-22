CC = gcc

BIN = bin
TEST_BIN = tests/bin

DOCS = docs
DOC_CONFIG = doxygen.config

libs:
	cd lib/unitc && make build

dirs:
	mkdir -p ./$(BIN)

test: libs
	mkdir -p $(TEST_BIN)
	$(CC) src/packet.c tests/packet_test.c -o $(TEST_BIN)/packet_test -L lib/unitc/lib -lunitc -I include/ -I lib/unitc/include/

docs:
	cd lib/doxygen && cmake -G "Unix Makefiles"
	cd lib/doxygen && make
	lib/doxygen/bin/doxygen $(DOC_CONFIG)

server: dirs
	$(CC) src/packet.c src/player.c src/server/*.c -o $(BIN)/server -I include/ -I lib/glfw/include/ -L lib/glfw/build/src -lglfw3 -lm

client: dirs
	$(CC) src/packet.c src/game.c src/glad/glad.c src/client/*.c -o $(BIN)/client -I include/ -I lib/glfw/include/ -L lib/glfw/build/src -lglfw3 -lm

clean:
	rm -rf $(BIN) $(TEST_BIN) $(DOCS)
