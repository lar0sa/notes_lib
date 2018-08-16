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
instr_three_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 d16  gis'8.~ 
	gis8  b,8~ 
		b8  c8~ 
			c16.  c,32~  c8~  |
% ________________________________________bar 2 :
c8~  c32  d16.~ 
	d2~ 
			d16  b''8.~  |
% ________________________________________bar 3 :
b2 
		b16  g,8.~ 
			g4~  |
% ________________________________________bar 4 :
g8.  gis'16~ 
	gis16  a,8.~ 
		a8.  ais16~ 
			ais8.  d,16~  |
% ________________________________________bar 5 :
d2~ 
		d8~  d32  gis16.~ 
			gis4~  |
% ________________________________________bar 6 :
gis8~  gis16.  c32~ 
	c4~ 
		c8.  cis16~ 
			cis16.  cis32  ais'8~  |
% ________________________________________bar 7 :
ais4~ 
	ais16.  g32~  g8~ 
		g16  b,8.~ 
			b4~  |
% ________________________________________bar 8 :
b8.  g'16~ 
	g4~ 
		g8~  g32  e16.~ 
			e8  cis,8  |
% ________________________________________bar 9 :
cis'4 
	f,2~ 
			f8  b8~  |
% ________________________________________bar 10 :
b4~ 
	b16.  c32~  c8~ 
		c4~ 
			c8~  c32  f,16.~  |
% ________________________________________bar 11 :
f4 
	ais4 
		g'2~  |
% ________________________________________bar 12 :
g32  e,16.~  e8~ 
	e4~ 
		e16.  ais'32~  ais8~ 
			ais4~  |
% ________________________________________bar 13 :
ais4 
	dis,8~  dis32  f,16.~ 
		f2~  |
% ________________________________________bar 14 :
f16.  a32~  a8~ 
	a2~ 
			a16.  a32~  a8~  |
% ________________________________________bar 15 :
a2~ 
		a32  b16.~  b8~ 
			b8~  b16.  dis,32~  |
% ________________________________________bar 16 :
dis32  ais'16.~  ais8~ 
	ais4~ 
		ais8~  ais32  b'16.~ 
			b4~  |
% ________________________________________bar 17 :
b4~ 
	b32  dis,16.~  dis8~ 
		dis4 
			fis4~  |
% ________________________________________bar 18 :
fis32  dis16.  c8~ 
	c4~ 
		c8~  c32  cis16.~ 
			cis4~  |
% ________________________________________bar 19 :
cis4~ 
	cis32  a16.~  a8 
		f'2~  |
% ________________________________________bar 20 :
f32  g,16.~  g8~ 
	g4~ 
		g32 
}

\score {
	\new Staff \with { instrumentName = "instr_three" } {
		\new Voice {
			\instr_three_part
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
