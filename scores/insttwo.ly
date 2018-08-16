% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.

% HEADERS

glissandoSkipOn = {
	\override NoteColumn.glissando-skip = ##t
	\hide NoteHead
	\hide Accidental
	\hide Tie
	\override NoteHead.no-ledgers = ##t
}

glissandoSkipOff = {
	\revert NoteColumn.glissando-skip
	\undo \hide NoteHead
	\undo \hide Tie
	\undo \hide Accidental
	\revert NoteHead.no-ledgers
}
instr_two_part = \relative c''' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 gis4. 
	cis,8~ 
		cis4~ 
			cis16.  gis32~  gis8~  |
% ________________________________________bar 2 :
gis16  c,16~  c32  gis'16.~ 
	gis4~ 
		gis8~  gis32  e16.~ 
			e4~  |
% ________________________________________bar 3 :
e4. 
	c8~ 
		c16.  f'32~  f8~ 
			f8  f8~  |
% ________________________________________bar 4 :
f16.  c32~  c8~ 
	c2~ 
			d4  |
% ________________________________________bar 5 :
cis,2~ 
		cis8~  cis16.  b'32~ 
			b4~  |
% ________________________________________bar 6 :
b4.~ 
	b32  b16.~ 
		b4~ 
			b8.  a'32  b,32~  |
% ________________________________________bar 7 :
b2~ 
		b8.  gis'16~ 
			gis4~  |
% ________________________________________bar 8 :
gis8  gis8~ 
	gis8~  gis32  ais,16.~ 
		ais32  c16.~  c8~ 
			c4~  |
% ________________________________________bar 9 :
c8~  c32  a16.~ 
	a4~ 
		a16.  g'32~  g8~ 
			g4~  |
% ________________________________________bar 10 :
g8~  g16.  dis32~ 
	dis2~ 
			dis16.  a32~  a8~  |
% ________________________________________bar 11 :
a2~ 
		a16.  fis'32~  fis8~ 
			fis32  f16.~  f8~  |
% ________________________________________bar 12 :
f8~  f16.  b,32~ 
	b32  d,16.~  d8~ 
		d4~ 
			d8.  b''16~  |
% ________________________________________bar 13 :
b32  dis,,16.~  dis8 
	d4~ 
		d16.  g'32~  g8~ 
			g4~  |
% ________________________________________bar 14 :
g8.  gis16~ 
	gis2~ 
			gis8~  gis32  a16.~  |
% ________________________________________bar 15 :
a2 
		ais,2~  |
% ________________________________________bar 16 :
ais8~  ais16.  g32~ 
	g2~ 
			g8  dis'8~  |
% ________________________________________bar 17 :
dis8.  fis,16~ 
	fis4 
		fis32  e16.~  e8~ 
			e4~  |
% ________________________________________bar 18 :
e4 
	b'2~ 
			b8~  b16.  b'32~  |
% ________________________________________bar 19 :
b2~ 
		b8~  b32  g16.~ 
			g8.  ais16~  |
% ________________________________________bar 20 :
ais8~  ais32  g,16.~ 
	g8.  fis'32  cis32~ 
		cis8~  cis32  f,16.~ 
			f4~  |
% ________________________________________bar 21 :
f16.  gis32~  gis8~ 
	gis2~ 
			gis16.  g'32~  g8~  |
% ________________________________________bar 22 :
g4~ 
	g16  g,8. 
}

\score {
	\new Staff \with { instrumentName = "instr_two" } {
		\new Voice {
			\instr_two_part
		}
	}
	\layout {
		\mergeDifferentlyHeadedOn
		\mergeDifferentlyDottedOn
		\set harmonicDots = ##t
		\override Glissando.thickness = #4
		\set Staff.pedalSustainStyle = #'mixed
		\override TextSpanner.bound-padding = #1.0
		\override TextSpanner.bound-details.right.padding = #1.3
		\override TextSpanner.bound-details.right.stencil-align-dir-y = #CENTER
		\override TextSpanner.bound-details.left.stencil-align-dir-y = #CENTER
		\override TextSpanner.bound-details.right-broken.text = ##f
		\override TextSpanner.bound-details.left-broken.text = ##f
		\override Glissando.minimum-length = #4
		\override Glissando.springs-and-rods = #ly:spanner::set-spacing-rods
		\override Glissando.breakable = ##t
		\override Glissando.after-line-breaking = ##t
		\set baseMoment = #(ly:make-moment 1/8)
		\set beatStructure = #'(2 2 2 2)
		#(set-default-paper-size "a4")
	}
	\midi { }
}

\version "2.18.2"
% notes Pd External version testing 
