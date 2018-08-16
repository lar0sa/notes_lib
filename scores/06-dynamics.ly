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

\header {
	title = "writing dynamics "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c1-0\<  |
% ________________________________________bar 2 :
c1-1\>  |
% ________________________________________bar 3 :
c1-2\!  |
% ________________________________________bar 4 :
c1-3\ppppp  |
% ________________________________________bar 5 :
c1-4\pppp  |
% ________________________________________bar 6 :
c1-5\ppp  |
% ________________________________________bar 7 :
c1-6\pp  |
% ________________________________________bar 8 :
c1-7\p  |
% ________________________________________bar 9 :
c1-8\mp  |
% ________________________________________bar 10 :
c1-9\mf  |
% ________________________________________bar 11 :
c1-10\f  |
% ________________________________________bar 12 :
c1-11\ff  |
% ________________________________________bar 13 :
c1-12\fff  |
% ________________________________________bar 14 :
c1-13\ffff  |
% ________________________________________bar 15 :
c1-14\fffff  |
% ________________________________________bar 16 :
c1-15\fp  |
% ________________________________________bar 17 :
c1-16\sf  |
% ________________________________________bar 18 :
c1-17\sff  |
% ________________________________________bar 19 :
c1-18\sp  |
% ________________________________________bar 20 :
c1-19\spp  |
% ________________________________________bar 21 :
c1-20\sfz  |
% ________________________________________bar 22 :
c1-21\rfz  |
% ________________________________________bar 23 :
c1-22 
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
