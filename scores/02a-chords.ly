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
	title = "generative chords "
}

inst_part = \relative c 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 <c cis a' fis' >1~  |
% ________________________________________bar 2 :
<c cis a' fis' >4 
	<d ais' b g' >2.~  |
% ________________________________________bar 3 :
<d ais' b g' >2 
		<dis c' gis' a >2~  |
% ________________________________________bar 4 :
<dis c' gis' a >2. 
			<e f cis' ais' >4~  |
% ________________________________________bar 5 :
<e f cis' ais' >1  |
% ________________________________________bar 6 :
<fis d' dis b' >1~  |
% ________________________________________bar 7 :
<fis d' dis b' >4 
	<g e' c' cis >2.~  |
% ________________________________________bar 8 :
<g e' c' cis >2 
		<c, gis' a f' >2~  |
% ________________________________________bar 9 :
<c gis' a f' >2. 
			<cis ais' fis' g >4~  |
% ________________________________________bar 10 :
<cis ais' fis' g >1  |
% ________________________________________bar 11 :
<d dis b' gis' >1~  |
% ________________________________________bar 12 :
<d dis b' gis' >4 
	<e c' cis a' >2.~  |
% ________________________________________bar 13 :
<e c' cis a' >2 
		<f d' ais' b >2~  |
% ________________________________________bar 14 :
<f d' ais' b >2. 
			<fis g dis' c' >4~  |
% ________________________________________bar 15 :
<fis g dis' c' >1  |
% ________________________________________bar 16 :
<gis e' f cis' >1~  |
% ________________________________________bar 17 :
<gis e' f cis' >4 
	<c, cis a' fis' >2.~  |
% ________________________________________bar 18 :
<c cis a' fis' >2 
		<d ais' b g' >2~  |
% ________________________________________bar 19 :
<d ais' b g' >2. 
			<dis c' gis' a >4~  |
% ________________________________________bar 20 :
<dis c' gis' a >1  |
% ________________________________________bar 21 :
<e f cis' ais' >1~  |
% ________________________________________bar 22 :
<e f cis' ais' >4 
	<fis d' dis b' >2.~  |
% ________________________________________bar 23 :
<fis d' dis b' >2 
		<g e' c' cis >2~  |
% ________________________________________bar 24 :
<g e' c' cis >2. 
			<c, gis' a f' >4~  |
% ________________________________________bar 25 :
<c gis' a f' >1  |
% ________________________________________bar 26 :
<cis ais' fis' g >1~  |
% ________________________________________bar 27 :
<cis ais' fis' g >4 
	<d dis b' gis' >2.~  |
% ________________________________________bar 28 :
<d dis b' gis' >2 
		<e c' cis a' >2~  |
% ________________________________________bar 29 :
<e c' cis a' >2. 
			<f d' ais' b >4~  |
% ________________________________________bar 30 :
<f d' ais' b >1 
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
