default: build

build: build_dir
	avr-gcc -Os -mmcu=atmega328p main.c -o build/main
	avr-size --format=avr --mcu=atmega328p build/main
	avr-objdump -Sz build/main > build/main.dump

burn: build
	avr-objcopy -O ihex -R .eeprom build/main build/main.hex
	avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:build/main.hex

clean:
	rm -rf build/

build_dir:
	mkdir -p build
