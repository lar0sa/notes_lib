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
	title = "grace notes "
	subtitle = "grace - slashed grace - acciacatura & appogiatura notes "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c1  \grace {gis'8-1-8 }   |
% ________________________________________bar 2 :
c,1  \slashedGrace {a'16-2-16 }   |
% ________________________________________bar 3 :
c,1  \acciaccatura {gis'32-3-32 }   |
% ________________________________________bar 4 :
c,1  \acciaccatura {gis'64-4-64 }   |
% ________________________________________bar 5 :
c,1  |
% ________________________________________bar 6 :
c1  \grace {gis'8-1-8 gis8-1-8 }   |
% ________________________________________bar 7 :
c,1  \slashedGrace {a'16-2-16 a16-2-16 }   |
% ________________________________________bar 8 :
c,1  \acciaccatura {gis'32-3-32 gis32-3-32 }   |
% ________________________________________bar 9 :
c,1  \acciaccatura {gis'64-4-64 gis64-4-64 }   |
% ________________________________________bar 10 :
c,1 
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
