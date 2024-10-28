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

###########################
# compiler and linker flags
export CFLAGS = -mmcu=$(MCU) -Wall -I. -DF_CPU=16000000 -Os
export LDFLAGS = -g $(TARGET_ARCH) -lm -Wl,--gc-sections

#################
# AVRDUDE options
PGMER = -c arduino -b 57600 -P $(TERM)
PGMERISP = -c arduino -b 115200 -P $(TERM)
ARVDUDECONF= -C $(AVRDUDECONF_LOC)/avrdude.conf
export DUDE = $(AVRDUDE_PATH)/avrdude -F -v -p $(MCU) $(AVRDUDECONF)


### OBJS
SRC := src
OBJ := obj
_dummy := $(shell mkdir -p $(OBJ))
C_SRCS := $(wildcard $(SRC)/*.c)
C_OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(C_SRCS))
TARGET := $(OBJ)/$(TARGET)


all: $(TARGET).hex

$(OBJ)/%.o:$(SRC)/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TARGET).elf: $(C_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(C_OBJS)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	stty $(STTY_OPT) $(TERM) hupcl # reset
	$(DUDE) $(PGMERISP) -U flash:w:$(TARGET).hex

size: $(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf

clean:
	rm -f **/*.o *~ **/*.hex **/*.elf