inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c8-1\sustainOn  d8 
	e8  fis8 
		gis8  ais8 
			c8  d8-2\sustainOff  |
% ________________________________________bar 2 :
c,8-3(  d8 
	e8  fis8 
		gis8  ais8 
			c8  d8-4)  |
% ________________________________________bar 3 :
d1-5\startTrillSpan  |
% ________________________________________bar 4 :
c2.-6-0^\markup {glissando }\stopTrillSpan\glissando 
			c,4-0\glissando  |
% ________________________________________bar 5 :
g'2-0\glissando 
		d2  |
% ________________________________________bar 6 :
r8  ais''8-7^\markup {glissando }\glissando\glissandoSkipOn  
	gis4 
		dis4 
			ais4-8\glissandoSkipOff  |
% ________________________________________bar 7 :
fis16  f'8.~ 
	f2.~ 
}
