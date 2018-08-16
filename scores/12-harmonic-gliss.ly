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
	\override NoteHead.no-ledgers = ##t
}

glissandoSkipOff = {
	\revert NoteColumn.glissando-skip
	\undo \hide NoteHead
	\undo \hide Accidental
	\revert NoteHead.no-ledgers
}

\header {
	title = "harmonic gliss "
}

inst_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 <g c\harmonic  >4\glissando\slashedGrace {<g' c\harmonic >16} 
	<g, c\harmonic  >4\glissando \glissandoSkipOn
		<d' g\harmonic  >4\glissandoSkipOff\slashedGrace {<g c\harmonic >16} 
			<g, c\harmonic  >4\glissando \glissandoSkipOn
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
		\set Staff.pedalSustainStyle = #'mixed
		\set baseMoment = #(ly:make-moment 1/8)
		\set beatStructure = #'(2 2 2 2)
		#(set-default-paper-size "a4")
	}
	\midi { }
}

\version "2.18.2"
% notes Pd External version testing 
