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
cc_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c16  c8  d16~ 
	d16  c8.~ 
		c16  d16  cis8~ 
			cis8  dis16  dis16  |
% ________________________________________bar 2 :
c16  cis8.~ 
	cis16  cis8.~ 
		cis16  dis8  cis16~ 
			cis8.  cis16~  |
% ________________________________________bar 3 :
cis8.  dis16~ 
	dis8.  d16 
		c16  dis16  dis8 
			d16  cis8  d16  |
% ________________________________________bar 4 :
cis4 
	cis16  dis8.~ 
		dis16  d8  cis16 
			c8  c16  cis16~  |
% ________________________________________bar 5 :
cis8.  c16~ 
	c16  d8  dis16~ 
		dis16  c8  cis16 
			cis4  |
% ________________________________________bar 6 :
dis8  c16  c16~ 
	c16  d8.~ 
		d16  cis8.~ 
			cis16  cis8.~  |
% ________________________________________bar 7 :
cis16  dis8.~ 
	dis16  dis8.~ 
		dis16  dis8.~ 
			dis16 
}

\score {
	\new Staff \with { instrumentName = "cc" } {
		\new Voice {
			\cc_part
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
