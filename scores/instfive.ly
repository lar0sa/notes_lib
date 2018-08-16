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
Ifive_part = \relative c''' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 gis8  g8 
	g4 
		dis8  g8~ 
			g8  e8~  |
% ________________________________________bar 2 :
e4. 
	gis8 
		f2  |
% ________________________________________bar 3 :
dis2 
		e2  |
% ________________________________________bar 4 :
a2 
		f4 
			ais4~  |
% ________________________________________bar 5 :
ais4 
	g8  ais8~ 
		ais8  ais8 
			ais4  |
% ________________________________________bar 6 :
fis2 
		ais2  |
% ________________________________________bar 7 :
fis2 
		ais4 
			dis,4~  |
% ________________________________________bar 8 :
dis4 
	a'8  a8~ 
		a4~ 
			a8  a8~  |
% ________________________________________bar 9 :
a8  e8~ 
	e8  e8~ 
		e8  dis8 
			fis8  gis8~  |
% ________________________________________bar 10 :
gis4. 
	g8~ 
		g8  fis8~ 
			fis8  a8~  |
% ________________________________________bar 11 :
a8  f8~ 
	f8  g8~ 
		g8  gis8~ 
			gis4~  |
% ________________________________________bar 12 :
gis8  fis8 
	gis8  f8~ 
		f8  ais8~ 
			ais8  fis8  |
% ________________________________________bar 13 :
a2 
		ais4 
			g4  |
% ________________________________________bar 14 :
ais8  f8~ 
	f4~ 
		f8  f8 
			gis4  |
% ________________________________________bar 15 :
a8  gis8~ 
	gis8  g8~ 
		g4~ 
			g8  a8  |
% ________________________________________bar 16 :
a4 
	dis,4 
		f2  |
% ________________________________________bar 17 :
e4 
	fis2 
			g8  ais8~  |
% ________________________________________bar 18 :
ais8  f8~ 
	f8  f8~ 
		f4~ 
			f8  fis8~  |
% ________________________________________bar 19 :
fis4. 
	g8 
		gis4 
			f4~  |
% ________________________________________bar 20 :
f4 
	f2 
			fis4  |
% ________________________________________bar 21 :
e8  e8 
	gis2 
}

\score {
	\new Staff \with { instrumentName = "Ifive" } {
		\new Voice {
			\Ifive_part
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
