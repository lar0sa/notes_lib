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
Ifour_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 d4 
	dis2 
			b4~  |
% ________________________________________bar 2 :
b4 
	c4 
		d4 
			c4~  |
% ________________________________________bar 3 :
c4 
	e4 
		c2  |
% ________________________________________bar 4 :
c4 
	cis4 
		dis8  b8~ 
			b4~  |
% ________________________________________bar 5 :
b8  d8 
	b4 
		dis2  |
% ________________________________________bar 6 :
dis8  c8~ 
	c8  e8 
		d4 
			b4  |
% ________________________________________bar 7 :
b8  dis8 
	d8  c8~ 
		c4~ 
			c8  d8~  |
% ________________________________________bar 8 :
d4. 
	d8~ 
		d4~ 
			d8  b8~  |
% ________________________________________bar 9 :
b4. 
	ais8 
		d8  ais8 
			d8  d8~  |
% ________________________________________bar 10 :
d4. 
	ais8~ 
		ais4~ 
			ais8  e'8~  |
% ________________________________________bar 11 :
e4. 
	b8~ 
		b4~ 
			b8  c8~  |
% ________________________________________bar 12 :
c8  d8~ 
	d4~ 
		d8  cis8 
			f4  |
% ________________________________________bar 13 :
d4 
	dis8  d8 
		ais4 
			f'4~  |
% ________________________________________bar 14 :
f4 
	c4 
		f2  |
% ________________________________________bar 15 :
d2 
		c2  |
% ________________________________________bar 16 :
f2 
		d4 
			cis4~  |
% ________________________________________bar 17 :
cis4 
	cis2 
			f4~  |
% ________________________________________bar 18 :
f4 
	d2 
			ais8  ais8~  |
% ________________________________________bar 19 :
ais4. 
	f'8~ 
		f4~ 
			f8  e8~  |
% ________________________________________bar 20 :
e8  d8~ 
	d8  f8~ 
		f8  b,8~ 
			b8  ais8~  |
% ________________________________________bar 21 :
ais8  f'8 
	b,2 
			d4  |
% ________________________________________bar 22 :
cis8  dis8~ 
	dis4~ 
		dis8  f8 
			e4  |
% ________________________________________bar 23 :
c2 
}

\score {
	\new Staff \with { instrumentName = "Ifour" } {
		\new Voice {
			\Ifour_part
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
