inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c8  d8 
	c8  d8 
		f8  g8 
			e8  fis8  |
% ________________________________________bar 2 :
c8_\markup { \combine \arrow-head #Y #UP ##t \draw-line #'(0 . -2)}_\markup { \harp-pedal #"v-^|ov-^v" }  d8 
	c8  d8 
		f8  g8 
			e8  fis8  |
% ________________________________________bar 3 :
c8  d8 
	c8  d8 
		f8  g8 
			e8  fis8  |
% ________________________________________bar 4 :
c8_\markup { \combine \arrow-head #Y #UP ##t \draw-line #'(0 . -2)}_\markup { \harp-pedal #"v-^|o^-^v" }  d8 
	c8  d8 
		f8  g8 
			e8  fis8 
}
