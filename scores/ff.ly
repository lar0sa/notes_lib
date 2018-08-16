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
ff_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 cis16  cis8.~ 
	cis16  dis8.~ 
		dis16  dis16  d8~ 
			d8  dis16  cis16  |
% ________________________________________bar 2 :
dis4 
	cis4 
		d8  dis8 
			cis16  c8  c16~  |
% ________________________________________bar 3 :
c8.  dis16 
	cis4 
		d4 
			dis8  d8  |
% ________________________________________bar 4 :
d8  cis8 
	d8  d16  d16 
		d4 
			dis4  |
% ________________________________________bar 5 :
c4 
	d4 
		d16  dis16  cis8 
			dis4  |
% ________________________________________bar 6 :
d4 
	cis8  c16  c16 
}

\score {
	\new Staff \with { instrumentName = "ff" } {
		\new Voice {
			\ff_part
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
