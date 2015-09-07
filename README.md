# notes_lib
notes Pd external object library for encoding music notation in lilypond syntax

It is sometimes the case that one needs to generate scores with traditional musical notation from with a Pure Data patch.

The "notes" external object [1] for Pure Data [2] fits information generated on a patch into traditional music notation, 
and encodes it in lilypond syntax. See notes-help.pd to see what syntax must be used inside Pd to input information into notes.

notes will generate .ly scores and you will need Lilypond to compile it and output sheet music in .pdf format. 
LilyPond is an open source music engraving program. 

To compile the externals just cd into this directory and run "make". If you have any trouble, 
try "make clean" and then "make" again.

If Lilypond is installed, the object will also compile the score directly and produce a .pdf document from within Pd. 
Go to [3] to learn more about lilypond and how to install it. In OS X, you must follow additional steps that will allow 
you to run it from the command line which is a prerequisite for the external to compile the score automatically from 
within Pd [4].

notes is programmed by Jaime Oliver La Rosa [5] [la.rosa@nyu.edu] at the NYU Waverly Labs [6] and is released under 
the GPL License [7]. It is currently in alpha stage.


[1] http://nyu-waverlylabs.org/notes/
[2] http://msp.ucsd.edu/software.html
[3] http://www.lilypond.org/
[4] http://www.lilypond.org/macos-x.html
[5] http://www.jaimeoliver.pe
[6] http://www.nyu-waverlylabs.org/
[7] http://www.gnu.org/copyleft/gpl.html
