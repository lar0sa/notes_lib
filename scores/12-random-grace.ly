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
	title = "random grace notes "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c8[ fis8] \slashedGrace {c'32} 
	c8[ dis,8~]
		dis8[ a'8~]
			a8[ c,8] \slashedGrace {dis'32}  |
% ________________________________________bar 2 :
fis,8[ c'8~]
	c8[ dis,8~]
		dis8[ a'8~]
			a8[ \slashedGrace {fis'32~}  c,8~] |
% ________________________________________bar 3 :
c8[ fis8] \slashedGrace {d'32f32} 
	c8[ dis,8~]
		dis8[ a'8~]
			a8[ c,8] \slashedGrace {cis'32e32}  |
% ________________________________________bar 4 :
fis,8[ c'8~]
	c8[ dis,8]
		a'4 \slashedGrace {c32dis32} 
			c,4 |
% ________________________________________bar 5 :
fis8[ \slashedGrace {fis'32~d32~}  c8~]
	c8[ dis,8~]
		dis8[ a'8~]
			a8[ c,8] \slashedGrace {f'32}  |
% ________________________________________bar 6 :
fis,4
	c'8[ \slashedGrace {cis32}  dis,8]
		a'4 \slashedGrace {e'32} 
			c,8[ \slashedGrace {c'32dis32}  fis,8] |
% ________________________________________bar 7 :
c'4 \slashedGrace {fis32} 
	dis,4 \slashedGrace {d'32f32} 
		a,8[ c,8~]
			c8[ fis8] \slashedGrace {cis'32e32}  |
% ________________________________________bar 8 :
c8[ \slashedGrace {c32dis32}  dis,8] \slashedGrace {fis'32} 
	a,4
		c,8[ \slashedGrace {d'32~}  fis,8~]
			fis8[ \slashedGrace {f'32}  c8] \slashedGrace {cis32e32}  |
% ________________________________________bar 9 :
dis,4
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
