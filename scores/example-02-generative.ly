% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.


\header {
	title = "a simple algorithmic melody "
}

inst_part = \relative c' 
{

\time 4/4

\tempo 4 = 36

\clef treble 
% ________________________________________bar 1 :
 c32[ f32 ais32 d,32~ d8~]
	d8[ g32 c32 e,16~]
		e8~[ e16. a32~]
			a4 |
% ________________________________________bar 2 :
cis,4~
	cis32[ fis32 b8.~]
		b16.[ dis,32~ dis8~]
			dis8[ gis8] |
% ________________________________________bar 3 :
c,4~
	c32[ f16.~ f8~]
		f16[ ais8 d,16~]
			d16[ g8.~] |
% ________________________________________bar 4 :
g16.[ c32~ c8~]
	c8[ e,8]
		a8[ cis,8~]
			cis8~[ cis32 fis32 b32 dis,32~] |
% ________________________________________bar 5 :
dis4
	gis8[ c,32 f16.~]
		f8.[ ais16~]
			ais16[ d,32 g32~ g16. c32] |
% ________________________________________bar 6 :
e,8[ a32 cis,16.~]
	cis8.[ fis16~]
		fis8~[ fis16. b32]
			dis,32[ gis16.~ gis32 c,16.~] |
% ________________________________________bar 7 :
c8.[ f16~]
	f16[ ais8 d,16~]
		d16[ g8 c16~]
			c16[ e,8.~] |
% ________________________________________bar 8 :
e16.[ a32~ a8~]
	a8[ cis,8~]
		cis8~[ cis32 fis16.~]
			fis32[ b16.~ b32 dis,16.~] |
% ________________________________________bar 9 :
dis32[ gis16.~ gis8~]
	gis16[ c,8 f16~]
		f8~[ f16. ais32~]
			ais16.[ d,32 g8~] |
% ________________________________________bar 10 :
g8~[ g32 c32 e,32 a32~]
	a16.[ cis,32 fis8]
		b8[ dis,32 gis32 c,16~]
			c8~[ c16.]
}

\score {
	\new Staff {
		\new Voice {
			\inst_part
		}
	}
	\layout {
		\mergeDifferentlyHeadedOn
		\mergeDifferentlyDottedOn
		\set Staff.pedalSustainStyle = #'mixed
		#(set-default-paper-size "a4")
	}
	\midi { }
}

\version "2.18.2"
% notes Pd External version testing 
