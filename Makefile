CC = gcc

BIN = bin
TEST_BIN = tests/bin

DOCS = docs
DOC_CONFIG = doxygen.config

OPTIONS = -Wall -Wpedantic -Werror

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
	$(CC) src/*.c src/server/*.c -o $(BIN)/server -I include/ -I lib/glfw/include/ -L lib/glfw/build/src -lglfw3 -lm $(OPTIONS)

client: dirs
	$(CC) src/glad/glad.c -c -I include/
	$(CC) src/*.c src/client/*.c glad.o -o $(BIN)/client -I include/ -I lib/glfw/include/ -L lib/glfw/build/src -lglfw3 -lm $(OPTIONS)
	rm glad.o

clean:
	rm -rf $(BIN) $(TEST_BIN) $(DOCS)
