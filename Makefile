all: main

run: main
	@echo "=============="
	@cd build && ./pcstatus

main:	clean
	g++ -o build/pcstatus src/Logger.cpp src/Sender.cpp src/Client.cpp src/TokenManager.cpp src/main.cpp -lcurl

clean:
	rm -f build/pcstatus
