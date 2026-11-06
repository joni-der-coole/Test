TARGET = payload_launcher
CFILES = main.c

all:
	mkdir -p bin
	$(CC) $(CFILES) $(LDFLAGS) -o bin/$(TARGET).elf

clean:
	rm -rf bin
