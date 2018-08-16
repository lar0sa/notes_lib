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
dd_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 g8  g16  fis16 
	fis16  f8  e16 
		g16  g8  f16~ 
			f8.  f16~  |
% ________________________________________bar 2 :
f8.  f16~ 
	f16  f8  f16~ 
		f8.  fis16 
			fis8  f8~  |
% ________________________________________bar 3 :
f8  f16  f16 
	fis16  e8.~ 
		e16  g8.~ 
			g16  e16  fis8~  |
% ________________________________________bar 4 :
fis8  e8~ 
	e8  fis16  f16 
		fis8  g8 
			fis4  |
% ________________________________________bar 5 :
fis4 
	f8  fis8~ 
		fis8  g8~ 
			g8  f8  |
% ________________________________________bar 6 :
f8  fis8 
	e4 
		fis4 
			e4  |
% ________________________________________bar 7 :
e4 
	f4 
		g4 
			g8  e8~  |
% ________________________________________bar 8 :
e8  f8~ 
	f8 
}

\score {
	\new Staff \with { instrumentName = "dd" } {
		\new Voice {
			\dd_part
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
