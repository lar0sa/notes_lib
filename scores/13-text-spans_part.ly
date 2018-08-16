inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.style = #'dashed-line 
c4-1\startTextSpan
	g'4
		f4
			d4 |
% ________________________________________bar 2 :
d'4
	ais4
		cis4
			c4\stopTextSpan |
% ________________________________________bar 3 :
d,4
	b'4
		
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.bound-details.right.arrow = ##t 
	\once \override TextSpanner.style = #'dashed-line 
c,4-3\startTextSpan
			e4 |
% ________________________________________bar 4 :
ais4
	f'4
		fis,4
			ais4 |
% ________________________________________bar 5 :
g4
	c4\stopTextSpan
		gis4
			g4 |
% ________________________________________bar 6 :

	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.style = #'line 
c,4-4\startTextSpan
	e'4
		cis,4
			d4 |
% ________________________________________bar 7 :
c'4
	b4
		gis4
			c4\stopTextSpan |
% ________________________________________bar 8 :
dis,4
	c4
		
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.bound-details.right.arrow = ##t 
	\once \override TextSpanner.style = #'line 
c4-6\startTextSpan
			cis'4 |
% ________________________________________bar 9 :
gis4
	cis4
		b4
			dis4 |
% ________________________________________bar 10 :
c,4
	c'4\stopTextSpan
		cis,4
			cis'4
}
