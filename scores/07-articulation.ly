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
	title = "articulation "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c2-0\accent 
		c2-1\espressivo  |
% ________________________________________bar 2 :
c2-2\marcato 
		c2-3\portato  |
% ________________________________________bar 3 :
c2-4\staccatissimo 
		c2-5\staccato  |
% ________________________________________bar 4 :
c2-6\tenuto 
		c2-7\shortfermata  |
% ________________________________________bar 5 :
c2-8\fermata 
		c2-9\longfermata  |
% ________________________________________bar 6 :
c2-10\verylongfermata 
		c2-11\upbow   |
% ________________________________________bar 7 :
c2-12\downbow  
		c2-13\flageolet  |
% ________________________________________bar 8 :
c2-14\thumb 
		c2-15\snappizzicato  |
% ________________________________________bar 9 :
c2-16\open 
		c2-17\halfopen  |
% ________________________________________bar 10 :
c2-18\stopped 
		c2-19\lheel  |
% ________________________________________bar 11 :
c2-20\rheel 
		c2-21\ltoe  |
% ________________________________________bar 12 :
c2-22\rtoe 
		c2-23\laissezVibrer   |
% ________________________________________bar 13 :
c2-24^\markup { \sharp } 
		c2-25^\markup { \flat }  |
% ________________________________________bar 14 :
c2-26^\markup { \natural } 
		c2-27\trill  |
% ________________________________________bar 15 :
c2-28\prall 
		c2-29\mordent  |
% ________________________________________bar 16 :
c2-30\prallmordent 
		c2-31\upprall  |
% ________________________________________bar 17 :
c2-32\downprall 
		c2-33\upmordent  |
% ________________________________________bar 18 :
c2-34\downmordent 
		c2-35\lineprall  |
% ________________________________________bar 19 :
c2-36\prallprall 
		c2-37\pralldown  |
% ________________________________________bar 20 :
c2-38\prallup 
		c2-39\turn  |
% ________________________________________bar 21 :
c2-40\reverseturn 
		c2-41\segno  |
% ________________________________________bar 22 :
c2-42\coda 
		c2-43\varcoda  |
% ________________________________________bar 23 :
c2-44\breathe 
		c2-45\bendAfter #+4   |
% ________________________________________bar 24 :
c2-46\bendAfter #-4  
		c2-47-\markup{pizz.}  |
% ________________________________________bar 25 :
c2-48-\markup{arco} 
		c2-49-\markup{vib.}  |
% ________________________________________bar 26 :
c2-50-\markup{senza vib.} 
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
