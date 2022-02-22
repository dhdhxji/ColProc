#!/bin/bash

FONTS=$@
SIZE=7
FONTS_FILE=fonts.h

echo "" > $FONTS_FILE
printf "#ifndef FONTS_H\n" >> $FONTS_FILE
printf "#define FONTS_H\n\n" >> $FONTS_FILE

for font_ttf in $FONTS; do
    font_name="${font_ttf%.*}"
    font_dat=$font_name$SIZE.dat
    font_c=$font_name$SIZE.c
    
    ./mcufont import_ttf $font_ttf $SIZE
    ./mcufont rlefont_optimize $font_dat
    ./mcufont rlefont_export $font_dat

    printf "\n#include \"$font_c\"\n" >> $FONTS_FILE
done

printf "#endif // FONTS_H" >> $FONTS_FILE


#%.c: %.dat
#	./mcufont rlefont_export $< $@

#fonts.h: 
#	echo "" > $@
#	echo -n "#ifndef FONTS_H" >> $@
#	echo -n "#define FONTS_H" >> $@
#	for file in $(ls | grep \*.c); do\
#		echo "#include \"$(file)\"" >> $@\
#	done
#	echo -n "#endif // FONTS_H" >> $@
