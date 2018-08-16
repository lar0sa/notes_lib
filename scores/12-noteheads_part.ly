inst_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 g2-0 
		\once \override NoteHead.style = #'harmonic g2-1  |
% ________________________________________bar 2 :
\xNote g2-2 
		\once \override NoteHead.style = #'triangle g2-3  |
% ________________________________________bar 3 :
\once \override NoteHead.style = #'fa g2-4 
		\once \override NoteHead.style = #'mensural g2-5  |
% ________________________________________bar 4 :
\once \override NoteHead.style = #'xcircle g2-6 
		\once \override NoteHead.style = #'diamond g2-7  |
% ________________________________________bar 5 :
\once \override NoteHead.style = #'slash g2-8 
		\parenthesize g2-9  |
% ________________________________________bar 6 :
g4-0 
	\once \override NoteHead.style = #'harmonic g4-1 
		\xNote g4-2 
			\once \override NoteHead.style = #'triangle g4-3  |
% ________________________________________bar 7 :
\once \override NoteHead.style = #'fa g4-4 
	\once \override NoteHead.style = #'mensural g4-5 
		\once \override NoteHead.style = #'xcircle g4-6 
			\once \override NoteHead.style = #'diamond g4-7  |
% ________________________________________bar 8 :
\once \override NoteHead.style = #'slash g4-8 
	\parenthesize g4-9 
}
