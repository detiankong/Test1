#
# File: CanTestForBd1.mk
#
#--------------------------------------------------------------
#   Embedded Coder for Microchip dsPIC30/dsPIC33/PIC24 family. |
#   Generate .c and .h files from your Matlab/simulink model   |
#   and compile the diagram to .hex and .cof file that can be  |
#   downloaded directly into the microcontroller               |
#                                                              |
#      The Microchip name PIC, dsPIC, and MPLAB are            |
#      registered trademarks of Microchip Technology Inc.      |
#      MATLAB, Simulink, and Real-Time Workshop are            |
#      registered trademarks of The MathWorks, Inc.            |
#                                                              |
# Licence Accorded to Yi Sun                                   |
#                                                              |
#   Written by Lubin KERHUEL -  http://www.kerhuel.eu          |
#  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
#   Version 3.7c                             15-Nov-2011       |
#--------------------------------------------------------------

MAKE 			 = "D:\PROGRA~1\MATLAB\R2010b\bin\win32\gmake"
HOST             = PC
BUILD            = yes
BUILD_SUCCESS    = *** Created
SYS_TARGET_FILE  = dspic.tlc

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the 
# Real-Time Workshop build procedure.
#   
MODEL               = CanTestForBd1
MODULES             = CanTestForBd1_main.c ecan.c 
MAKEFILE            = CanTestForBd1.mk
MATLAB_ROOT         = D:\Program Files\MATLAB\R2010b
ALT_MATLAB_ROOT     = D:\PROGRA~1\MATLAB\R2010b
S_FUNCTIONS         = 
S_FUNCTIONS_LIB     = 
NUMST               = 2
NCSTATES            = 0
COMPUTER            = PCWIN
BUILDARGS           =  GENERATE_REPORT=0 MULTI_INSTANCE_CODE=0 PORTABLE_WORDSIZES=0 GENERATE_ASAP2=0 TMW_EXTMODE_TESTING=0
MULTITASKING        = 0
MODELREFS           = 
SHARED_SRC          = 
SHARED_SRC_DIR      = 
SHARED_BIN_DIR      = 
SHARED_LIB          = 
GEN_SAMPLE_MAIN     = 0
TARGET_LANG_EXT     = c
EXT_MODE            = 0
EXTMODE_TRANSPORT   = 0
EXTMODE_STATIC      = 0
EXTMODE_STATIC_SIZE = 1000000
NUMST               = 2


#--------------------------- Model and reference models -----------------------
MODELLIB                  = CanTestForBd1lib.lib
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ..\..
# NONE: standalone, SIM: modelref sim, RTW: modelref rtw
MODELREF_TARGET_TYPE       = NONE

# New : to support Continuous States ? find in "Upgrading from V3.2.1 or V3.2"
CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DNUMST=$(NUMST) -DNCSTATES=$(NCSTATES) \
-DMAT_FILE=$(MAT_FILE)
-DINTEGER_CODE=$(INTEGER_CODE) \
-DONESTEPFCN=$(ONESTEPFCN) -DTERMFCN=$(TERMFCN) \
-DHAVESTDIO
-DMULTI_INSTANCE_CODE=$(MULTI_INSTANCE_CODE) \
-DADD_MDL_NAME_TO_GLOBALS=$(ADD_MDL_NAME_TO_GLOBALS)

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif

# RTW option makevariables that are not expanded in the template makefile are
# automatically passed into make. To avoid this, create NOOP replacements.
# For this custom target, these ERT makevariables are not used.
#
NOOP = 0
NOOP = 0
NOOP = 0
NOOP = 0
NOOP = 0

#------------------------------ Tool Locations ---------------------------------
#

GCCPATH	= ''

CC   = $(GCCPATH)pic30-gcc 
CPP  = $(GCCPATH)pic30-gcc
#LD   = $(GCCPATH)pic30-ld  
LD   = $(GCCPATH)pic30-gcc  
AR   = $(GCCPATH)pic30-ar -r

# parameter controlled from simulink

#-O3 -fschedule-insns -fschedule-insns2
OPTIM_GCC = -mcpu=33fj128MC804 -O3 -fschedule-insns -fschedule-insns2 	

#-t --report-mem -Map ../untitled.map --heap 0  -cref
LDFLAGS =  -Xlinker -t -Xlinker --report-mem -Xlinker -Map=../untitled.map -Xlinker --heap=0 -Xlinker -cref

#-T C:\PROGRA~1\MICROC~1\MPLABC~1\support\gld\p30f2012.gld
LDPICTYPE =  -Xlinker --script=C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\support\dsPIC33F\gld\p33fj128MC804.gld

#-LC:\PROGRA~1\MICROC~1\MPLABC~1\lib\ -lp30F2012 -lm -lc -lpic30
LDLIBPIC =  C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\lib\libpic30-coff.a C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\lib\dsPIC33F\libp33fj128MC804-coff.a C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\lib\libc-coff.a C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\lib\libm-coff.a

PIC_INCLUDES =  -I C:\PROGRA~1\MICROC~1\mplabc30\v3.30c\include

PIC_REF = 33fj128MC804

CC_OPTS = $(OPTIM_GCC) -O 

#------------------------------ Include Path -----------------------------------
#
MATLAB_INCLUDES = \
	-I$(MATLAB_ROOT)/simulink/include \
  -I$(MATLAB_ROOT)/extern/include \
	-I$(MATLAB_ROOT)/rtw/c/src \
	-I$(MATLAB_ROOT)/rtw/c/ert \
	-I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common

# Additional includes 
#
ADD_INCLUDES = \
	-IE:\Program\Mplab\ForTestS\Test_Canbus\CanTestForBd1\CanTestForBd1_dspic\sources \
	-IE:\Program\Mplab\ForTestS\Test_Canbus\CanTestForBd1 \



USER_INCLUDES = 

SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I$(SHARED_SRC_DIR) 
endif

INCLUDES = -I. -I$(RELATIVE_PATH_TO_ANCHOR) $(MATLAB_INCLUDES) $(ADD_INCLUDES) \
           $(USER_INCLUDES) $(PIC_INCLUDES) $(MODELREF_INC_PATH) \
           $(SHARED_INCLUDES)

#-------------------------------- C Flags --------------------------------------
# General User Options 

CFLAGS    =$(CC_OPTS)  $(INCLUDES) 
CPPFLAGS = $(CC_OPTS)  $(INCLUDES)

LIBS =
 
LIBS += $(S_FUNCTIONS_LIB)

#----------------------------- Source Files ------------------------------------
SHARED_OUTPUT_OPTS = -o $@
SRCS = $(MODULES) $(S_FUNCTIONS)
ifeq ($(MODELREF_TARGET_TYPE), NONE)
  # Top-level model for RTW
  PRODUCT            = $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).hex
  BUILD_PRODUCT_TYPE = "executable"
  SRCS               += $(MODEL).$(TARGET_LANG_EXT)  $(EXT_SRC)

#ifeq ($(GEN_SAMPLE_MAIN),0)
#    SRCS += main.c
#  else
#    SRCS += ert_main.c
#  endif

else
  # sub-model for RTW
  PRODUCT            = $(MODELLIB)
  BUILD_PRODUCT_TYPE = "library"
endif

#ifeq ($(ExtMode),1)
  # external mode sources
#  EXT_SRC  = ext_svr.c
#  EXT_SRC += updown.c
#  EXT_SRC += ext_work.c
#  EXT_SRC += ext_svr_serial_transport.c
#  EXT_SRC += ext_serial_pkt.c
#  EXT_SRC += ext_serial_c167_port.c
#  
  # static memory management (optional)
#  ifeq ($(ExtModeStatMemAlloc),1) 
    # memory manager
#	EXT_SRC += mem_mgr.c
#  endif
#  SRCS += EXT_SRC
#endif


USER_SRCS =
USER_OBJS = $(addsuffix .o, $(basename $(USER_SRCS)))
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

OBJS      = $(addsuffix .o, $(basename $(SRCS))) $(USER_OBJS)
LINK_OBJS = $(addsuffix .o, $(basename $(SRCS))) $(LOCAL_USER_OBJS)

SHARED_SRC := $(wildcard $(SHARED_SRC))
SHARED_OBJS = $(addsuffix .o, $(basename $(SHARED_SRC)))

#--------------------------------- Rules ---------------------------------------
ifeq ($(MODELREF_TARGET_TYPE),NONE)
# Top-level model for RTW
$(PRODUCT) : $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).cof 
	$(GCCPATH)pic30-bin2hex $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).cof 
		@echo "*** Converted $(MODEL).cof to $(MODEL).hex"	
		@echo .
		@echo "***  MPLAB: file -> import, choose $(MODEL).hex. Configure -> Configuration Bits : Verify !"
		@echo "       Download into the chip and run."		
#		@echo "***  Alternatively, open project created and compile it (again):"
# Message suite within m script, can't work with both windows 7 and previous windows!		
#ifeq ($(COMPUTER),PCWIN)  # does not work on win x64!
#		@echo "   	  ==> <a href="matlab: !start $(MODEL).mcp">MPLAB 8</a>: Within Matlab, right-click $(MODEL).mcp -> open outside Matlab."	
#		@echo "   	  ==> <a href="matlab: !C:\Program Files\Microchip\MPLABX\mplab_ide\bin\MPLAB_IDE.exe ^&">MPLAB X</a>: Start MPLAB X, open the project folder /$(MODEL)_dspic"	
#else
#		@echo "   	  ==> MPLAB 8: Within Matlab, right-click $(MODEL).mcp -> open outside Matlab."	
#		@echo "   	  ==> MPLAB X: Start MPLAB X, open the project folder /$(MODEL)_dspic"			
#endif
#		@echo " " 

else
# sub-model for RTW
$(PRODUCT) : $(OBJS) $(SHARED_OBJS)
	@rm -f $(MODELLIB)
	$(AR) ruv $(MODELLIB) $(LINK_OBJS)
	@echo "### $(MODELLIB) Created"
	@echo "$(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@"	
endif


$(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).cof : $(OBJS) $(SHARED_LIB) $(MODELREF_LINK_LIBS) $(LIBS)
		@echo " ================================================================"
	    @echo "*** Embedded Target for dsPIC by Lubin KERHUEL - http://www.kerhuel.eu"
	    @echo " | Licence Accorded to Yi Sun                                   |"
		@echo " |                     yisun.hust@gmail.com                     |"	    
	    @echo " |          Companie : Ritsumeikan University                   |" 
		@echo " |                     Kyoto                                    |"
		@echo " |                     Japan                                    |" 		
		@echo " |                                                              |"
		@echo " |                                                              |"		 		
		@echo " | Financial Service : Yi Sun                                   |"
		@echo " | Contact             yisun.hust@gmail.com                     |"
		@echo " |                     Kyoto                                    |"
		@echo " |                     Japan                                    |"
		@echo " |                                                              |"
		@echo " |                                                              |"
	    @echo " | Version 3.7c                              15-Nov-2011        |"
		@echo " | For Matlab 7.11            R2010b                            |"
		@echo " ================================================================"	
	$(LD) -mcpu=$(PIC_REF) $(MODELREF_LINK_LIBS) $(LINK_OBJS) $(SYSLIBS) $(SHARED_LIB) $(LIBS) $(LDLIBPIC) -o $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).cof $(LDPICTYPE) $(LDFLAGS)	 
		@echo "    ---$(PIC_REF)---"
		@echo "$(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@"	

	
%.o : %.c
	$(CC) -c $(CFLAGS) $<

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $<

%.o : %.s
	$(CC) -c $< -Wa,-p=$(PIC_REF),-g
	
%.o : ../%.c
	$(CC) -c $(CFLAGS) $<

%.o : ../%.cpp
	$(CC) -c $(CPPFLAGS) $<
	
%.o : ../%.s
	$(CC) -c $< -Wa,-p=$(PIC_REF),-g

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) -c $(CFLAGS) $<

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CC) -c $(CPPFLAGS) $<
	
%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(CC) -c $< -Wa,-p=$(PIC_REF),-g
	

%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c $(CFLAGS) $<

%.o : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c
	$(CC) -c $(CFLAGS) $<

%.o : $(MATLAB_ROOT)/rtw/c/src/ext_mode/custom/%.c
	$(CC) -c $(CFLAGS) $<

%.o : $(MATLAB_ROOT)\rtw\c\src/%.c
	$(CC) -c $(CFLAGS) $<


%.o : $(MATLAB_ROOT)\rtw\c\src/%.cpp
	$(CC) -c $(CPPFLAGS) $<


%.o : $(MATLAB_ROOT)\rtw\c\src/%.s
	$(CC) -c $< -Wa,-p=$(PIC_REF),-g


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) -c $(CFLAGS) $<

%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CC) -c $(CPPFLAGS) $<

	
	
#------------------------------- Libraries -------------------------------------





#----------------------------- Dependencies ------------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw

$(SHARED_OBJS) : $(SHARED_BIN_DIR)/%.o : $(SHARED_SRC_DIR)/%.c  
	$(CC) -c $(CFLAGS) $(SHARED_OUTPUT_OPTS) $<

$(SHARED_OBJS) : $(SHARED_BIN_DIR)/%.o : $(SHARED_SRC_DIR)/%.s  
	$(CC) -c $< -Wa,-p=$(PIC_REF),-g
	
$(SHARED_LIB) : $(SHARED_OBJS)
	@echo "### Creating $@ "
	$(AR) $@ $(SHARED_OBJS)
	@echo "### $@ Created "

