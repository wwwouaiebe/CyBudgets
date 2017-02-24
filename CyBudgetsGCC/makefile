# -Werror
#
# -Wall:
# -Waddress -Warray-bounds -Wc++11-compat -Wchar-subscripts -Wcomment -Wformat -Wmaybe-uninitialized -Wmissing-braces -Wnonnull -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var 
# option supprimée: -Wc++11-compat
# -Wextra:
# -Wclobbered -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter
# option supprimée: -Wignored-qualifiers
#
DEBUG := no
TESTING := no

ifeq ($(DEBUG),yes)
	ifeq ($(TESTING),yes)
		RESULT := CyBudgetsLinuxDebugUnitTestingx64
		CPPFLAGS := -std=c++03 -I ../Code/ -I ../../sqlite-3.17.00.00/code/ -I /usr/include/wx-3.1/ -funsigned-char -Werror -Wclobbered -Wempty-body -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wformat -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var -D CY_UNIT_TESTS -D CY_COMPILER_GCC -D CY_64_BITS -D _DEBUG -g `wx-config --cxxflags`
	else
		RESULT := CyBudgetsLinuxDebugx64
		CPPFLAGS := -std=c++03 -I ../Code/ -I ../../sqlite-3.17.00.00/code/ -I /usr/include/wx-3.1/ -funsigned-char -Werror -Wclobbered -Wempty-body -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter -Waddress -Warray-bounds -Wchar-subscripts -Wcomment -Wformat -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var -D CY_COMPILER_GCC -D CY_64_BITS -D _DEBUG -g `wx-config --cxxflags` 
	endif
    LDFLAGS := `wx-config --unicode --debug --libs` ../../sqlite-3.17.00.00/code/sqlite3.o
else
	ifeq ($(TESTING),yes)
		RESULT := CyBudgetsLinuxReleaseUnitTestingx64
		CPPFLAGS := -std=c++03 -I ../Code/ -I ../../sqlite-3.17.00.00/code/ -I /usr/include/wx-3.1/ -funsigned-char -D CY_UNIT_TESTS -D CY_COMPILER_GCC -D CY_64_BITS `wx-config --cxxflags`
	else
		RESULT := CyBudgetsLinuxReleasex64
		CPPFLAGS := -std=c++03 -I ../Code/ -I ../../sqlite-3.17.00.00/code/ -I /usr/include/wx-3.1/ -funsigned-char -D CY_COMPILER_GCC -D CY_64_BITS `wx-config --cxxflags` 
	endif
    LDFLAGS := `wx-config --unicode --libs` ../../sqlite-3.17.00.00/code/sqlite3.o
endif

CC := c++

UTILITIESSRC := $(wildcard ../Code/UtilitiesLayer/*.cpp)
UTILITIESOBJ := $(UTILITIESSRC:.cpp=.o)

DATASRC := $(wildcard ../Code/DataLayer/*.cpp)
DATAOBJ := $(DATASRC:.cpp=.o)

CORESRC := $(wildcard ../Code/CoreLayer/*.cpp)
COREOBJ := $(CORESRC:.cpp=.o)

UISRC := $(wildcard ../Code/UserInterfaceLayer/*.cpp)
UIOBJ := $(UISRC:.cpp=.o)

OBJECTS = $(UTILITIESOBJ)
OBJECTS += $(DATAOBJ)
OBJECTS += $(COREOBJ)
OBJECTS += $(UIOBJ)

clean : exec
	@echo ""
	@echo "Cleaning temporary files"
	@rm $(OBJECTS)
	@echo ""
	@echo ""
	@echo "End of execution"
	@echo ""
	@echo ""
	
exec : copy
	@echo ""
	@echo "Running CyBudgets"
	@../Bin/$(RESULT)
	@echo ""

copy : CyBudgets
	@echo ""
	@echo "Copying executable "
	@cp -f $< ../Bin/$(RESULT)

CyBudgets : $(OBJECTS)
	@echo "Now linking " $@
	@echo ""
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo ""
	@echo "End linking "

%.o : %.cpp
	@echo "Now compiling " $<
	@echo ""
	@$(CC) -o $@ -c $< $(CPPFLAGS)
	@echo ""
	@echo "End compiling " $<
	@echo ""