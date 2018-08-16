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
	title = "noteheads "
}

inst_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 g2-0 
		\once \override NoteHead.style = #'harmonic g2-1  |
% ________________________________________bar 2 :
\xNote g2-2 
		\once \override NoteHead.style = #'triangle g2-3  |
% ________________________________________bar 3 :
\once \override NoteHead.style = #'fa g2-4 
		\once \override NoteHead.style = #'mensural g2-5  |
% ________________________________________bar 4 :
\once \override NoteHead.style = #'xcircle g2-6 
		\once \override NoteHead.style = #'diamond g2-7  |
% ________________________________________bar 5 :
\once \override NoteHead.style = #'slash g2-8 
		\parenthesize g2-9  |
% ________________________________________bar 6 :
g4-0 
	\once \override NoteHead.style = #'harmonic g4-1 
		\xNote g4-2 
			\once \override NoteHead.style = #'triangle g4-3  |
% ________________________________________bar 7 :
\once \override NoteHead.style = #'fa g4-4 
	\once \override NoteHead.style = #'mensural g4-5 
		\once \override NoteHead.style = #'xcircle g4-6 
			\once \override NoteHead.style = #'diamond g4-7  |
% ________________________________________bar 8 :
\once \override NoteHead.style = #'slash g4-8 
	\parenthesize g4-9 
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
