##################
# general options
export CC = avr-gcc
export MCU = atmega328p
export TARGET_ARCH = -mmcu=$(MCU)

TARGET = SCAM

#######################
# Setting up tool paths
TERM = /dev/ttyUSB0
STTY_OPT = -F
AVRDUDE_PATH = /usr/bin/
AVRDUDECONF_PATH = /usr/share/arduino/hardware/tools/

###########################
# compiler and linker flags
export LDFLAGS = -g $(TARGET_ARCH) -nostdlib


#################
# AVRDUDE options
PGMER = -c arduino -b 57600 -P $(TERM)
PGMERISP = -c arduino -b 115200 -P $(TERM)
ARVDUDECONF= -C $(AVRDUDECONF_LOC)/avrdude.conf
export DUDE = $(AVRDUDE_PATH)/avrdude -F -v -p $(MCU) $(AVRDUDECONF)


### OBJS
SRC_CODES := blink_sleep.S


### RULES
all: $(TARGET).hex

$(TARGET).hex: $(SRC_CODES)
	$(CC) $(LDFLAGS) -o $(TARGET).elf $(SRC_CODES)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	stty $(STTY_OPT) $(TERM) hupcl # reset
	$(DUDE) $(PGMERISP) -U flash:w:$(TARGET).hex

size: $(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf

peek: $(TARGET).elf
	avr-objdump -D -s $(TARGET).elf -j .text

clean:
	rm -f *.hex *.elf