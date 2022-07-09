CC = gcc

BIN = bin
TEST_BIN = tests/bin

libs:
	cd lib/unitc && make build

dirs:
	mkdir ./$(BIN)

test: libs
	mkdir -p $(TEST_BIN)
	$(CC) src/packet.c tests/packet_test.c -o $(TEST_BIN)/packet_test -L lib/unitc/lib -lunitc -I include/ -I lib/unitc/include/

clean:
	rm -rf $(BIN) $(TEST_BIN)
