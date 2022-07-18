# Makefile for notes

# specify a location for Pd if desired
PDDIR = ../pure-data

lib.name = notesLib

cflags = -Iinclude 

lib.setup.sources = src/notesLib.c # blank Pd object that loads the library

class.sources = src/notes.c src/mainscore.c src/line2score.c

common.sources = src/notes_lib.c

datafiles = help/notes-help.pd help/hpp-format-o.pd README.md

# build a multi-object library
make-lib-executable=yes

PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
