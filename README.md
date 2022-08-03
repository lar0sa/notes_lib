# notes_lib
notes Pd external object library for encoding music notation in lilypond syntax.

It is sometimes the case that one needs to generate scores with traditional musical notation from with a Pure Data patch. 

The "notes" external object [1] for Pure Data [2] fits information generated on a patch into traditional music notation, and encodes it in lilypond syntax. See notes-help.pd to see what syntax must be used inside Pd to input information into notes.

notes will generate .ly scores and you will need Lilypond to compile these scores and output sheet music in .pdf format. If Lilypond is installed, the object will compile the score directly and produce a .pdf document from within Pd. 

LilyPond is an open source music engraving program. Go to [3] to learn more about lilypond and how to install it. The INSTALL.txt file contained with this distribution gives OS-specific guidelines on installing Lilypond to work with notes_lib as well as instructions to compile the code.

notes is programmed by Jaime Oliver La Rosa [4] [la.rosa@nyu.edu] with contributions by Fede Cámara Halac [5] at the NYU Waverly Labs [6] and is released under the GPL License [7]. It is currently in beta-ish stage.


[1] https://github.com/lar0sa/notes_lib
[2] http://msp.ucsd.edu/software.html
[3] http://www.lilypond.org/
[4] http://www.jaimeoliver.pe
[5] https://github.com/fdch
[6] https://as.nyu.edu/departments/music.html
[7] http://www.gnu.org/copyleft/gpl.html
