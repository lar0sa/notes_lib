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
instr_one_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 f8  b,8~ 
	b2~ 
			b32  e,16.~  e8~  |
% ________________________________________bar 2 :
e4 
	gis'8.  a,16~ 
		a8.  e'16~ 
			e16  gis,8.~  |
% ________________________________________bar 3 :
gis16  gis'8.~ 
	gis2~ 
			gis32  e16.~  e8~  |
% ________________________________________bar 4 :
e4~ 
	e32  gis,16.~  gis8 
		f'8  c32  fis,16.~ 
			fis4~  |
% ________________________________________bar 5 :
fis4 
	cis4.~ 
		cis16  a''16~ 
			a16  fis8.~  |
% ________________________________________bar 6 :
fis4.~ 
	fis16.  a,32~ 
		a4~ 
			a8.  fis16~  |
% ________________________________________bar 7 :
fis2 
		f2~  |
% ________________________________________bar 8 :
f4 
	b'16.  g32~  g8~ 
		g4~ 
			g32  e,16.~  e8~  |
% ________________________________________bar 9 :
e4 
	gis16.  g'32~  g8~ 
		g16.  b,32~  b16  cis,16~ 
			cis4~  |
% ________________________________________bar 10 :
cis4.~ 
	cis16  b''16~ 
		b2~  |
% ________________________________________bar 11 :
b8  a8~ 
	a16.  c,,32~  c16  fis'16~ 
		fis2~  |
% ________________________________________bar 12 :
fis8.  ais,16~ 
	ais4 
		g2~  |
% ________________________________________bar 13 :
g16.  ais'32~  ais8~ 
	ais8.  cis,16~ 
		cis32  d16.~  d8~ 
			d16  ais'16~  ais32  e16.~  |
% ________________________________________bar 14 :
e4 
	gis,8.  e16~ 
		e4~ 
			e16.  gis32~  gis8~  |
% ________________________________________bar 15 :
gis2~ 
		gis32  e16.~  e8~ 
			e8~  e32  f16.~  |
% ________________________________________bar 16 :
f2~ 
		f8  cis'8~ 
			cis4~  |
% ________________________________________bar 17 :
cis8~  cis16.  dis32~ 
	dis8~  dis16.  d,32~ 
		d2~  |
% ________________________________________bar 18 :
d16  g32  fis'32~  fis8~ 
	fis16  e,8.~ 
		e4 
			fis'4~  |
% ________________________________________bar 19 :
fis16  cis,8.~ 
	cis2~ 
			cis32  gis''16.~  gis8~  |
% ________________________________________bar 20 :
gis4.~ 
	gis16. 
}

\score {
	\new Staff \with { instrumentName = "instr_one" } {
		\new Voice {
			\instr_one_part
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
