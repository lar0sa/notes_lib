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
	title = "twnty random durations "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c2.~-0-28 
			c8  c8~-1-40  |
% ________________________________________bar 2 :
c1~  |
% ________________________________________bar 3 :
c8  c8~-2-10 
	c8.  c16~-3-42 
		c2~  |
% ________________________________________bar 4 :
c2. 
			c16.-4-3  c32~-5-14  c8~  |
% ________________________________________bar 5 :
c4~ 
	c32  c16.~-6-27  c8~ 
		c2~  |
% ________________________________________bar 6 :
c8  c8~-7-20 
	c2~ 
			c4~-8-39  |
% ________________________________________bar 7 :
c2.~ 
			c8~  c16.  c32~-9-13  |
% ________________________________________bar 8 :
c4. 
	c8~-10-12 
		c4 
			c4~-11-31  |
% ________________________________________bar 9 :
c2~ 
		c8~  c16.  c32~-12-22 
			c4~  |
% ________________________________________bar 10 :
c4.~ 
	c32  c16.~-13-27 
		c2~  |
% ________________________________________bar 11 :
c4 
	c2.~-14-31  |
% ________________________________________bar 12 :
c8~  c16.  c32~-15-29 
	c2.~  |
% ________________________________________bar 13 :
c8  c8~-16-16 
	c4~ 
		c8  c8~-17-35 
			c4~  |
% ________________________________________bar 14 :
c2~ 
		c8~  c16.  c32~-18-24 
			c4~  |
% ________________________________________bar 15 :
c4.~ 
	c16.  c32~-19-40 
		c2~  |
% ________________________________________bar 16 :
c2~ 
		c8~  c16. 
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
