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
	title = "writing text spans "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.style = #'dashed-line 
c4-1\startTextSpan
	g'4
		f4
			d4 |
% ________________________________________bar 2 :
d'4
	ais4
		cis4
			c4\stopTextSpan |
% ________________________________________bar 3 :
d,4
	b'4
		
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.bound-details.right.arrow = ##t 
	\once \override TextSpanner.style = #'dashed-line 
c,4-3\startTextSpan
			e4 |
% ________________________________________bar 4 :
ais4
	f'4
		fis,4
			ais4 |
% ________________________________________bar 5 :
g4
	c4\stopTextSpan
		gis4
			g4 |
% ________________________________________bar 6 :

	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.style = #'line 
c,4-4\startTextSpan
	e'4
		cis,4
			d4 |
% ________________________________________bar 7 :
c'4
	b4
		gis4
			c4\stopTextSpan |
% ________________________________________bar 8 :
dis,4
	c4
		
	\once \override TextSpanner.bound-details.left.text = #"text1 " 
	\once \override TextSpanner.bound-details.right.text = #" text2 " 
	\once \override TextSpanner.bound-details.right.arrow = ##t 
	\once \override TextSpanner.style = #'line 
c4-6\startTextSpan
			cis'4 |
% ________________________________________bar 9 :
gis4
	cis4
		b4
			dis4 |
% ________________________________________bar 10 :
c,4
	c'4\stopTextSpan
		cis,4
			cis'4
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
