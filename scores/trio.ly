% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.

instr_one_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 a1~
 a4 \breathe a2.~^"rec1"
 a4 \breathe r2.^"deja el guiro"^"posición ord."
 r4 b2.~^"rec2"
  b4 \breathe cis2.~^"rec3"
  cis4 \breathe dis2.~
  dis4 \breathe f2.(
  d1)
}

instr_two_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 a1~ 
 a8 \breathe gis2..~^"rec1"
gis1~
 gis8 \breathe ais2..~^"rec2"
 ais8 \breathe c2..~^"rec3"
 c8 \breathe d2..~^"rec4"
 d8 \breathe e2..~
 e2 b2~\<
 b1~
 b\>
 r1\!
}

instr_three_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
a1_"todos tempos largos, multiples repeticiones, pedales al inicio y fin de cada rec"  \breathe
g1~^"rec1" \breathe
g1
fis1^"rec2" \breathe
f!1^"rec3" \breathe
e1^"rec4" \breathe
dis1^"ped, empieza el descenso"
r1\fermata
c~\<
c\>
r1\!

}


\header {
	composer = " "
	title = "clusters "
	subtitle = "  "
}


\score {
	<<
	\new Staff \with { instrumentName = "vln" } {
		<<
		\new Voice {
			\instr_one_part
		}
		>>
	}
	\new Staff \with { instrumentName = "fl" } {
		<<
		\new Voice {
			\instr_two_part
		}
		>>
	}
	\new Staff \with { instrumentName = "sax" } {
		<<
		\new Voice {
			\instr_three_part
		}
		>>
	}
	>>
	\layout {
		\mergeDifferentlyHeadedOn
		\mergeDifferentlyDottedOn
		\set Staff.pedalSustainStyle = #'mixed
		#(set-default-paper-size "a4landscape")
	}
	\midi { }
}

\version "2.18.2"
% mainscore Pd External version testing 
