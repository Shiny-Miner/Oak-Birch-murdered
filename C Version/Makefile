#
# int_demo.mak
#
# makefile for a simple interrupt demo


# --- Project details ---
PROJ    := int_demo
EXT     := gba
#UDIR    := ../toncllib

SFILES  := 
CPFILES  := main.cpp

SOBJS   := $(SFILES:.s=.o)
COBJS   := $(CFILES:.c=.o)
OBJS    := $(SOBJS) $(COBJS)

#--- Tool settings ---
CROSS   := /opt/devkitpro/devkitARM/bin/arm-none-eabi-                    # use arm-agb-elf- for DKA
AS      := $(CROSS)as
CC      := $(CROSS)gcc
LD      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy


MODEL   := -mthumb-interwork -mthumb
SPECS   := -specs=gba.specs

ASFLAGS := -mthumb-interwork
CFLAGS  := -I./ -I$(UDIR) $(MODEL) -O2 -Wall
LDFLAGS := $(SPECS) $(MODEL)

#--- Build steps ---
build : $(PROJ).$(EXT)

$(PROJ).$(EXT) : $(PROJ).elf
	@$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@

$(PROJ).elf : $(OBJS)
	@$(LD) $^ $(LDFLAGS) -o $@

#COBJS compiled automatically via implicit rules
#$(COBJS) : %.o : %.c
#	$(CC) -c $< $(CFLAGS) -o $@

$(SOBJS) : %.o : %.s
	$(AS) $(ASFLAGS) $< -o $@


# --- Clean ---
.PHONY : clean
clean : 
	@rm -fv $(COBJS) $(SOBJS)
	@rm -fv $(PROJ).$(EXT) 
	@rm -fv $(PROJ).elf	

