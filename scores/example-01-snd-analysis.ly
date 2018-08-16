% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.


\header {
	title = "a chord showing the partials of a sound sample "
}

inst_part = \relative c, 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 <gisih aisih' b' dih fih b fis' cis' >1[]
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
