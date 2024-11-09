#
# A Makefile that compiles all .c and .s files in "src" and "res" 
# subdirectories and places the output in a "obj" subdirectory
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ../../../
endif

LCC = $(GBDK_HOME)bin/lcc 
PNG2ASSET = $(GBDK_HOME)bin/png2asset 

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif

# From: https://stackoverflow.com/questions/3774568/makefile-issue-smart-way-to-scan-directory-tree-for-c-files
# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


# You can set the name of the .gb ROM file here
PROJECTNAME    = HowToSaveData

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
GENDIR      = gen
BINS	    = $(OBJDIR)/$(PROJECTNAME).gb

# How to recursively find all files that match a pattern
CSOURCES := $(call rwildcard,$(SRCDIR)/,*.c)   $(call rwildcard,$(GENDIR)/,*.c) 

LCCFLAGS += -Iinclude -Iheaders -Igen

all:	prepare png2asset $(BINS)

obj/saved-data.o: saved-data.c
	$(LCC) $(LCCFLAGS) -Wf-ba0 -c -o obj/saved-data.o saved-data.c

png2asset: 
	$(PNG2ASSET) $(RESDIR)/CoinSprite.png -c $(GENDIR)/CoinSprite.c -keep_palette_order -noflip -spr8x16 -sw 8 -sh 16 -px 4 -py 4
	$(PNG2ASSET) $(RESDIR)/PlayerSprite.png -c $(GENDIR)/PlayerSprite.c -keep_palette_order -noflip -spr8x16 -sw 16 -sh 16
	$(PNG2ASSET) $(RESDIR)/GBDKSaveExampleBackground.png -c $(GENDIR)/GBDKSaveExampleBackground.c -map -keep_palette_order -noflip
	$(PNG2ASSET) $(RESDIR)/Font.png -c $(GENDIR)/Font.c -map -keep_palette_order -noflip

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat


# Link the compiled object files into a .gb ROM file
$(BINS):	$(CSOURCES) obj/saved-data.o
	$(LCC) $(LCCFLAGS) -Wm-yt3 -Wm-yoA -Wm-ya1 -o $(BINS) $(CSOURCES) obj/saved-data.o

prepare:
	mkdir -p $(OBJDIR)
	mkdir -p $(GENDIR)

clean:
#	rm -f  *.gb *.ihx *.cdb *.adb *.noi *.map
	rm -f  $(OBJDIR)/*.*
	rm -f  $(GENDIR)/*.*

