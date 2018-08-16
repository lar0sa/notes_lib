inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 r4 
	\pitchedTrill e2\startTrillSpan gis 
			e4\stopTrillSpan\glissando  |
% ________________________________________bar 2 :
\pitchedTrill c'2.\glissando\startTrillSpan d 
			g4\stopTrillSpan\glissando  |
% ________________________________________bar 3 :
e4 
	\pitchedTrill f'2.\glissando\startTrillSpan g\glissandoSkipOn   |
% ________________________________________bar 4 :
f4\glissandoSkipOff 
	ais,4\stopTrillSpan 
		ais4. 
			\pitchedTrill f'8\glissando\startTrillSpan g\glissandoSkipOn   |
% ________________________________________bar 5 :
f4\glissandoSkipOff 
	d4\stopTrillSpan\glissando 
		ais2~  |
% ________________________________________bar 6 :
ais4 
}
