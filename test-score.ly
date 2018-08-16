% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.


\header {
	composer = "www.nyu-waverlylabs.org "
	title = "notes: a music notation external for Pd "
	subtitle = "encodes your pd generated information into lilyond readable syntax "
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c4
	c4
		c4
			c4 |
% ________________________________________bar 2 :
c4
	c4
		c4
			c4
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
		#(set-default-paper-size "a4")
	}
	\midi { }
}

\version "2.18.2"
% notes Pd External version testing 
