#---------------------------------------------------------------------------------
# MiroTayWorkshopRPG Makefile
# Requires: devkitPPC, libogc, GRRLIB, wiiuse
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

LD          :=  $(CC)

#---------------------------------------------------------------------------------
TARGET      :=  MiroTayWorkshopRPG
BUILD       :=  build
SOURCES     :=  source
DATA        :=  data
INCLUDES    :=  source

CFLAGS      =   -g -O2 -Wall $(MACHDEP) $(INCLUDE) -I$(LIBOGC_INC)
CXXFLAGS    =   $(CFLAGS)
LDFLAGS     =   -g $(MACHDEP) -L$(LIBOGC_LIB) -Wl,-Map,$(notdir $@).map

LIBS        :=  -lgrrlib -lfreetype -ljpeg -lpngu -lpng -lz -lfat -lwiiuse -lbte -logc -lm

LIBDIRS     :=  $(PORTLIBS)

#---------------------------------------------------------------------------------
include $(DEVKITPPC)/base_rules

ifneq ($(BUILD),$(notdir $(CURDIR)))
export OUTPUT   :=  $(CURDIR)/$(TARGET)
export VPATH    :=  $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                     $(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR  :=  $(CURDIR)/$(BUILD)

CFILES      :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES    :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES      :=  $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES    :=  $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

export OFILES_BIN   :=  $(addsuffix .o,$(BINFILES))
export OFILES_SRC   :=  $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(sFILES:.s=.o)
export OFILES        :=  $(OFILES_BIN) $(OFILES_SRC)
export HFILES_BIN   :=  $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE  :=  $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                     $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                     -I$(CURDIR)/$(BUILD)

export LIBPATHS :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

else

DEPENDS :=  $(OFILES:.o=.d)

$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

$(OFILES_SRC): $(HFILES_BIN)

endif
