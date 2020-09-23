#***************************************************************************
# Makefile                                                                 *
#***************************************************************************
# Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
# Departamento de Engenharia Electrotécnica e de Computadores              *
# Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
#***************************************************************************
# Author: Pedro Gonçalves                                                  *
#***************************************************************************

AVRDUDE_PROGRAMMER := avrispmkII
AVRDUDE_PORT := usb

COLOR=$(shell echo "\033[0;33m")
WHITE=$(shell echo "\033[0m")

SILENT ?= @
CROSS ?= avr-

MCU ?= atxmega32a4u
F_CPU ?= 32000000L

TARGET = button

OBJDIR = obj

PAKDIR = $(TARGET)_$(MCU)

#SRCS = $(wildcard *.c)
#SRCS = Src/core/SM_cleaning.c \
#	Src/core/SM_sampling.c \
#	Src/core/SM_stepper.c \
#	Src/core/SM_main.c \
#	Src/core/inputs.c \
#	Src/driver/io.c \
#	Src/driver/usart.c \
# TC_driver/TC_driver.c \
#	Src/core/main.c

SRCS = $(wildcard *.c) $(wildcard Src/*.c) $(wildcard Src/core/*.c) $(wildcard Src/driver/*.c) $(wildcard TC_driver/*.c)


# These will automatically be checked if they are set to YES
SPECIAL_DEFS +=

OBJS = $(SRCS:%.c=%.o)

ifneq ($(CROSS), )
  CC = $(CROSS)gcc
  CXX = $(CROSS)g++
  OBJCOPY = $(CROSS)objcopy
  OBJDUMP = $(CROSS)objdump
  SIZE = $(CROSS)size
endif

ifneq ($(F_CPU),)
  CFLAGS += -DF_CPU=$(F_CPU)
endif

## Special defines

define CHECK_ANSWER
  ifeq ($$($(1)), YES)
    CFLAGS += -D$(1)
  endif
endef

$(foreach i,$(SPECIAL_DEFS),$(eval $(call CHECK_ANSWER,$(i))))

##

OPT=s

CFLAGS += -g -O$(OPT) \
-ffreestanding -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes \
-Wl,-u,vfprintf -lprintf_flt -lm \
-Wl,-u,vfscanf -lscanf_flt -lm \
-Wa,-adhlns=$(OBJDIR)/$(<:.c=.lst) -std=gnu99 -mmcu=$(MCU)

LDFLAGS = -Wl,-Map=$(OBJDIR)/$(TARGET).map,--cref

release: $(OBJDIR) all

$(OBJDIR):
	$(SILENT) mkdir -p $(OBJDIR)
	$(SILENT) mkdir -p $(OBJDIR)/Src
	$(SILENT) mkdir -p $(OBJDIR)/Src/core
	$(SILENT) mkdir -p $(OBJDIR)/Src/driver
	$(SILENT) mkdir -p $(OBJDIR)/TC_driver

all: $(TARGET).hex #$(OBJDIR)/$(TARGET).elf

size: $(TARGET).elf
	@echo "$(COLOR)[$(TARGET)] >> Size:$(WHITE)"
	$(SILENT) $(SIZE) -C --mcu=$(MCU) $(TARGET).elf

clean:
	$(SILENT) -rm -rf $(wildcard $(OBJDIR)/$(OBJS) $(OBJDIR)/$(TARGET).elf $(OBJDIR)/$(TARGET).hex $(OBJDIR)/$(TARGET).eep $(OBJDIR)/$(TARGET).map $(OBJDIR)/$(OBJS:%.o=%.d) $(OBJDIR)/$(OBJS:%.o=%.lst) $(OBJDIR))
	$(SILENT) -rm -rf *.elf
	$(SILENT) -rm -rf *.hex
	$(SILENT) -rm -rf *.d
	clear
	@echo "$(COLOR)[$(TARGET)] >> Done.$(WHITE)"

ifneq ($(wildcard $(OBJS) $(TARGET).elf $(TARGET).hex), )
package:
	@echo "$(COLOR)[$(TARGET)] >> Creating Package:$(WHITE)"
	$(SILENT) mkdir $(PAKDIR)
	$(SILENT) cp *.elf $(PAKDIR)
	$(SILENT) cp *.hex $(PAKDIR)
	$(SILENT) cp -r Src $(PAKDIR)
	$(SILENT) cp *.h $(PAKDIR)
	$(SILENT) cp -r TC_driver $(PAKDIR)
	$(SILENT) cp -r Inc $(PAKDIR)
	$(SILENT) cp Makefile $(PAKDIR)
	$(SILENT) tar -zcf $(TARGET).tar.gz $(PAKDIR)
	$(SILENT) -rm -rf $(PAKDIR)
	@echo "$(COLOR)[$(TARGET)] >> Done.$(WHITE)"

else
package:
	@echo "$(COLOR)[$(TARGET)] >> need to do first >> make$(WHITE)"
endif

.SECONDARY:

%.elf: $(OBJS)
	@echo "$(COLOR)[$(TARGET)] >> Linking:" $@$(WHITE)
	$(SILENT) mv Src/core/*.o $(OBJDIR)/
	$(SILENT) mv Src/driver/*.o $(OBJDIR)/
	$(SILENT) mv TC_driver/*.o $(OBJDIR)/
	$(SILENT) $(CC) $(CFLAGS) $(OBJDIR)/*.o --output $@ $(LDFLAGS)

%.o : %.c
	@echo "$(COLOR)[$(TARGET)] >> Compiling:" $@$(WHITE)
	$(SILENT) $(CC) $(CFLAGS) -MMD -MF $(OBJDIR)/$(@:%.o=%.d) -c $< -o $@
#	$(SILENT) mv *.o $(OBJDIR)/

%.d : %.c
	@echo "$(COLOR)[$(TARGET)] >> Generating dependency:" $@$(WHITE)
	$(SILENT) $(CC) $(CFLAGS) -MM -MT $(OBJDIR)/$(addsuffix .o, $(basename $@)) -MF $@ $<


###############

## Programming

AVRDUDE := sudo avrdude

AVRDUDE_FLAGS += -p $(MCU)
ifneq ($(AVRDUDE_PORT), )
  AVRDUDE_FLAGS += -P $(AVRDUDE_PORT)
endif
ifneq ($(AVRDUDE_PROGRAMMER), )
  AVRDUDE_FLAGS += -c $(AVRDUDE_PROGRAMMER)
endif
ifneq ($(AVRDUDE_SPEED), )
  AVRDUDE_FLAGS += -b $(AVRDUDE_SPEED)
endif

#Add more verbose output if we dont have SILENT set
ifeq ($(SILENT), )
  AVRDUDE_FLAGS += -v -v
endif

# Fuses for internal 8MHz oscillator
ifeq ($(MCU), atmega328p)
  AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m
endif
ifeq ($(MCU), atmega88)
  AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m
endif
ifeq ($(MCU), atmega8)
  AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m
endif
ifeq ($(MCU), $(filter $(MCU), attiny2313 attiny4313))
  AVRDUDE_WRITE_FUSE ?= -U lfuse:w:0xE4:m
  #AVRDUDE_WRITE_FLASH := -U lfuse:w:0x64:m #run with 1 Mhz clock #default clock mode
endif

ifneq ($(AVRDUDE_PROGRAMMER), )
flash: $(OBJDIR) $(TARGET).hex #$(TARGET).eep
	@echo "$(COLOR)[$(TARGET)] >> Flashing $(MCU):"$(WHITE)
	$(SILENT) $(AVRDUDE) -e $(AVRDUDE_FLAGS) -U flash:w:$(TARGET).hex

fuse:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FUSE)

%.hex: %.elf
	@echo "Creating flash file:" $@...
	$(SILENT) $(SIZE) -C --mcu=$(MCU) $(TARGET).elf
	$(SILENT) $(OBJCOPY) -O ihex -R .eeprom $< $@

%.eep: %.elf
	@echo "Creating eeprom file:" $@...
	$(SILENT) $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O ihex $< $@
else
FLASH_MSG="You need to set AVRDUDE_PROGRAMMER/AVRDUDE_PORT/AVRDUDE_SPEED in ~/user.mk"
flash:
	@echo $(FLASH_MSG)

fuse:
	@echo $(FLASH_MSG)

clean_chip:
	@echo $(FLASH_MSG)
	$(AVRDUDE) -e $(AVRDUDE_FLAGS)
endif

###############

# Check which .o files we already have and include their dependency files.
# $(AVRDUDE) $(AVRDUDE_FLAGS) -U eeprom:w:$(TARGET).eep
PRIOR_OBJS := $(wildcard $(OBJS)) $(wildcard $(OBJS)/Src) $(wildcard $(OBJS)/Src/core) $(wildcard $(OBJS)/Src/driver) $(wildcard $(OBJS)/TC_driver)
include $(PRIOR_OBJS:%.o=%.d)