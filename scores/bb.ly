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
bb_part = \relative c' 
{

\time 4/4

\clef tenor 
% ________________________________________bar 1 :
 ais4 
	a8  a8 
		a4 
			a16  ais8.~  |
% ________________________________________bar 2 :
ais16  gis8  b16~ 
	b8.  gis16 
		a16  b8  b16~ 
			b16  gis8.~  |
% ________________________________________bar 3 :
gis16  a8  a16~ 
	a16  gis16  gis16  ais16 
		b8  gis8~ 
			gis8  b16  ais16~  |
% ________________________________________bar 4 :
ais16  ais8.~ 
	ais16  gis16  a8 
		b16  a16  b8 
			b4  |
% ________________________________________bar 5 :
b16  b8.~ 
	b16  b8.~ 
		b16  ais16  gis16  ais16~ 
			ais8.  b16  |
% ________________________________________bar 6 :
gis8  b16  a16~ 
	a8.  a16 
		a8  a8~ 
			a8  gis8~  |
% ________________________________________bar 7 :
gis8  gis8 
	gis16 
}

\score {
	\new Staff \with { instrumentName = "bb" } {
		\new Voice {
			\bb_part
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
