all: main

run: main
	@echo "=============="
	@cd build && ./main

main:	clean
	g++ -o build/main src/Logger.cpp src/Sender.cpp src/Client.cpp src/TokenManager.cpp src/main.cpp -lcurl

clean:
	rm -f build/main
