PLATFORM := AVR

# MCU
MCU := ATMEGA128
#MCU = ATMEGA16
#MCU = ATMEGA32
#MCU = ATMEGA256

PROJECT_NAME :=heater_pid_system
#PROJECT_NAME = PRO2
#PROJECT_NAME = PRO2

#CRYSTAL_FRQ =4000000UL
CRYSTAL_FRQ :=8000000UL
#CRYSTAL_FRQ =16000000UL
#CRYSTAL_FRQ =32000000UL

CC :=avr-gcc

BUILD_TYPE = debug
#BUILD_TYPE = release

ifeq ($(MCU),ATMEGA128)
MMCU=atmega128
endif

ifeq ($(BUILD_TYPE), debug)
DEBUG :=DEBUGGING_ENABLE
else
DEBUG :=DEBUGGING_DISABLE
endif


CFLAG = -funsigned-char -funsigned-bitfields
#************************** SOURCE PATH AND OUTPUT PATH****************

OUTPUT_PATH = output
PROJECT_PATH = ./


#************************* BUILDING FLAGS****************************
CFLAG +=-D$(MCU)
CFLAG +=-D$(PROJECT_NAME)
CFLAG +=-DF_CPU=$(CRYSTAL_FRQ)
CFLAG +=-D$(DEBUG)

#************************* H Header FILES ***************************
HEADER += -I$(PROJECT_PATH)common
HEADER += -I$(PROJECT_PATH)hal/include
HEADER += -I$(PROJECT_PATH)hal/include/boards
HEADER += -I$(PROJECT_PATH)utils/debug
HEADER += -I$(PROJECT_PATH)utils/lcd_mngr
HEADER += -I$(PROJECT_PATH)utils/timer_mngr

#***************************** C FILE SOURCE ******************
C_SOURCE_PATHS  += $(PROJECT_PATH)common
C_SOURCE_PATHS  += $(PROJECT_PATH)utils/debug
C_SOURCE_PATHS  += $(PROJECT_PATH)utils/lcd_mngr
C_SOURCE_PATHS  += $(PROJECT_PATH)utils/timer_mngr
C_SOURCE_PATHS  += $(PROJECT_PATH)hal/source

ifeq ($(PROJECT_NAME), heater_pid_system)
HEADER += -I$(PROJECT_PATH)app\projects\heater_pid_controller
C_SOURCE_PATHS  += app/projects/heater_pid_controller
endif

CFILES += $(foreach var,$(C_SOURCE_PATHS), $(wildcard $(var)/*.c)) 

OBJECTS := $(addprefix $(OUTPUT_PATH)/,$(notdir $(CFILES:%.c=%.o)))

#$(info $(CFILES))


all: $(OUTPUT_PATH) $(PROJECT_NAME) 


$(PROJECT_NAME): $(OBJECTS) 
	@echo "Generating... $(PROJECT_NAME).map, $(PROJECT_NAME).elf and $(PROJECT_NAME).hex files"
	@$(CC) -Wl,-Map,$(OUTPUT_PATH)/$(PROJECT_NAME).map -mmcu=$(MMCU) -o $(OUTPUT_PATH)/$(PROJECT_NAME).elf $(OBJECTS) $(HEADER)
	@avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature  $(OUTPUT_PATH)/$(PROJECT_NAME).elf $(OUTPUT_PATH)/$(PROJECT_NAME).hex

$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)common/%.c 
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU) $< -o $@
	
$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)utils/debug/%.c
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU) $< -o $@

$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)utils/lcd_mngr/%.c
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU) $< -o $@

$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)utils/timer_mngr/%.c
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU)  $< -o $@

$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)hal/source/%.c
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU) $< -o $@

ifeq ($(PROJECT_NAME), heater_pid_system)
$(OUTPUT_PATH)/%.o: $(PROJECT_PATH)app/projects/heater_pid_controller/%.c
	@echo "Compiling... $<"
	@$(CC) -c $(CFLAG) $(HEADER) -O1 -fpack-struct -fshort-enums -g2 -Wall -std=gnu99 -MD -MP -MF $(@:%.o=%.d) -MT$(@:%.o=%.d) -MT$(@:%.o=%.o) -mmcu=$(MMCU) $< -o $@
endif


$(OUTPUT_PATH):
	mkdir $@

flash:
	@echo "Not added now"

clean:
	@echo "Clean....."
	@rm -rf $(OBJECTS) $(OUTPUT_PATH)/$(PROJECT_NAME).hex $(OUTPUT_PATH)/$(PROJECT_NAME).map