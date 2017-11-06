# ST Visual Debugger Generated MAKE File, based on dmx.stp

ifeq ($(CFG), )
CFG=Debug
$(warning ***No configuration specified. Defaulting to $(CFG)***)
endif

ToolsetRoot=C:\PROGRA~2\COSMIC\FSE_CO~1\CXSTM8
ToolsetBin=C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8
ToolsetInc=C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8\Hstm8
ToolsetLib=C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8\Lib
ToolsetIncOpts=-i"C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8\Hstm8" 
ToolsetLibOpts=-l"C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8\Lib" 
ObjectExt=o
OutputExt=elf
InputName=$(basename $(notdir $<))


# 
# Debug
# 
ifeq "$(CFG)" "Debug"


OutputPath=Debug
ProjectSFile=dmx
TargetSName=dmx
TargetFName=dmx.elf
IntermPath=$(dir $@)
CFLAGS_PRJ=$(ToolsetBin)\cxstm8  +modsl0 +debug -pxp -pp -l -dSTM8S005 -i..\biquad -i..\..\fwlib\inc $(ToolsetIncOpts) -cl$(IntermPath:%\=%) -co$(IntermPath:%\=%) $<
ASMFLAGS_PRJ=$(ToolsetBin)\castm8  -xx -l $(ToolsetIncOpts) -o$(IntermPath)$(InputName).$(ObjectExt) $<

all : $(OutputPath) dmx.elf

$(OutputPath) : 
	if not exist $(OutputPath)/ mkdir $(OutputPath)

Debug\stm8s_tim1.$(ObjectExt) : ..\..\fwlib\src\stm8s_tim1.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\fwlib\inc\stm8s_tim1.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_clk.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_gpio.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_uart2.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_gpio.$(ObjectExt) : ..\..\fwlib\src\stm8s_gpio.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\fwlib\inc\stm8s_gpio.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_clk.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim1.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_uart2.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_clk.$(ObjectExt) : ..\..\fwlib\src\stm8s_clk.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\fwlib\inc\stm8s_clk.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_gpio.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim1.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_uart2.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_uart2.$(ObjectExt) : ..\..\fwlib\src\stm8s_uart2.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\fwlib\inc\stm8s_uart2.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_clk.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_gpio.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim1.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\main.$(ObjectExt) : main.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_clk.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_gpio.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim1.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_uart2.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8_interrupt_vector.$(ObjectExt) : stm8_interrupt_vector.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h ..\..\fwlib\inc\stm8s_adc1.h ..\..\fwlib\inc\stm8s_awu.h ..\..\fwlib\inc\stm8s_beep.h ..\..\fwlib\inc\stm8s_clk.h ..\..\fwlib\inc\stm8s_exti.h ..\..\fwlib\inc\stm8s_flash.h ..\..\fwlib\inc\stm8s_gpio.h ..\..\fwlib\inc\stm8s_i2c.h ..\..\fwlib\inc\stm8s_itc.h ..\..\fwlib\inc\stm8s_iwdg.h ..\..\fwlib\inc\stm8s_rst.h ..\..\fwlib\inc\stm8s_spi.h ..\..\fwlib\inc\stm8s_tim1.h ..\..\fwlib\inc\stm8s_tim2.h ..\..\fwlib\inc\stm8s_tim3.h ..\..\fwlib\inc\stm8s_tim4.h ..\..\fwlib\inc\stm8s_uart2.h ..\..\fwlib\inc\stm8s_wwdg.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

dmx.elf :  $(OutputPath)\stm8s_tim1.o $(OutputPath)\stm8s_gpio.o $(OutputPath)\stm8s_clk.o $(OutputPath)\stm8s_uart2.o $(OutputPath)\main.o $(OutputPath)\stm8_interrupt_vector.o $(OutputPath)\dmx.lkf
	$(ToolsetBin)\clnk  -m $(OutputPath)\$(TargetSName).map $(ToolsetLibOpts) -o $(OutputPath)\$(TargetSName).sm8 $(OutputPath)\$(TargetSName).lkf 
	$(ToolsetBin)\cvdwarf  $(OutputPath)\$(TargetSName).sm8 

	$(ToolsetBin)\chex  -o $(OutputPath)\$(TargetSName).s19 $(OutputPath)\$(TargetSName).sm8
clean : 
	-@erase $(OutputPath)\stm8s_tim1.o
	-@erase $(OutputPath)\stm8s_gpio.o
	-@erase $(OutputPath)\stm8s_clk.o
	-@erase $(OutputPath)\stm8s_uart2.o
	-@erase $(OutputPath)\main.o
	-@erase $(OutputPath)\stm8_interrupt_vector.o
	-@erase $(OutputPath)\dmx.elf
	-@erase $(OutputPath)\stm8s_tim1.ls
	-@erase $(OutputPath)\stm8s_gpio.ls
	-@erase $(OutputPath)\stm8s_clk.ls
	-@erase $(OutputPath)\stm8s_uart2.ls
	-@erase $(OutputPath)\main.ls
	-@erase $(OutputPath)\stm8_interrupt_vector.ls
endif

# 
# Release
# 
ifeq "$(CFG)" "Release"


OutputPath=Release
ProjectSFile=dmx
TargetSName=dmx
TargetFName=dmx.elf
IntermPath=$(dir $@)
CFLAGS_PRJ=$(ToolsetBin)\cxstm8  -i..\biquad +mods0 -pp $(ToolsetIncOpts) -cl$(IntermPath:%\=%) -co$(IntermPath:%\=%) $< 
ASMFLAGS_PRJ=$(ToolsetBin)\castm8  $(ToolsetIncOpts) -o$(IntermPath)$(InputName).$(ObjectExt) $<

all : $(OutputPath) dmx.elf

$(OutputPath) : 
	if not exist $(OutputPath)/ mkdir $(OutputPath)

Release\stm8s_tim1.$(ObjectExt) : ..\..\fwlib\src\stm8s_tim1.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_gpio.$(ObjectExt) : ..\..\fwlib\src\stm8s_gpio.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_clk.$(ObjectExt) : ..\..\fwlib\src\stm8s_clk.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_uart2.$(ObjectExt) : ..\..\fwlib\src\stm8s_uart2.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST86F2~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\main.$(ObjectExt) : main.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8_interrupt_vector.$(ObjectExt) : stm8_interrupt_vector.c c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods0.h stm8s_conf.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stm8s.h c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~3.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STM8S_~4.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F2E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST7CB3~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST2F09~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4044~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE645~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST070E~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST3D3F~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST0B76~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STC41B~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST4AA7~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\ST1FE4~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STE34D~1.H c:\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\fwlib\STF2EC~1.H 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

dmx.elf :  $(OutputPath)\stm8s_tim1.o $(OutputPath)\stm8s_gpio.o $(OutputPath)\stm8s_clk.o $(OutputPath)\stm8s_uart2.o $(OutputPath)\main.o $(OutputPath)\stm8_interrupt_vector.o $(OutputPath)\dmx.lkf
	$(ToolsetBin)\clnk  $(ToolsetLibOpts) -o $(OutputPath)\$(TargetSName).sm8 $(OutputPath)\$(TargetSName).lkf 
	$(ToolsetBin)\cvdwarf  $(OutputPath)\$(TargetSName).sm8 

	$(ToolsetBin)\chex  -o $(OutputPath)\$(TargetSName).s19 $(OutputPath)\$(TargetSName).sm8
clean : 
	-@erase $(OutputPath)\stm8s_tim1.o
	-@erase $(OutputPath)\stm8s_gpio.o
	-@erase $(OutputPath)\stm8s_clk.o
	-@erase $(OutputPath)\stm8s_uart2.o
	-@erase $(OutputPath)\main.o
	-@erase $(OutputPath)\stm8_interrupt_vector.o
	-@erase $(OutputPath)\dmx.elf
	-@erase $(OutputPath)\dmx.map
	-@erase $(OutputPath)\dmx.st7
	-@erase $(OutputPath)\dmx.s19
	-@erase $(OutputPath)\stm8s_tim1.ls
	-@erase $(OutputPath)\stm8s_gpio.ls
	-@erase $(OutputPath)\stm8s_clk.ls
	-@erase $(OutputPath)\stm8s_uart2.ls
	-@erase $(OutputPath)\main.ls
	-@erase $(OutputPath)\stm8_interrupt_vector.ls
endif
