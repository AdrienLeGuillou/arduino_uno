default: build

build: build_dir
	# preprocess only
	avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -E main.S -o build/main.s
	# compile no link
	avr-gcc -mmcu=atmega328p -nostdlib -c build/main.s -o build/main.o
	# link
	avr-ld -o build/main.elf build/main.o
	# size breakdown of the object
	avr-size --format=avr --mcu=atmega328p build/main.elf
	avr-objdump -Sz build/main.elf > build/main.dump

burn: build
	# convert to ihex
	avr-objcopy build/main.elf -R .eeprom build/main.hex -O ihex
	# flash to arduino
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/main.hex

clean:
	rm -rf build/

build_dir:
	mkdir -p build
