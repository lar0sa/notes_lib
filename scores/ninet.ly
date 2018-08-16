% [notes] external for Pure Data
% development-version July 14, 2014 
% by Jaime E. Oliver La Rosa
% la.rosa@nyu.edu
% @ the Waverly Labs in NYU MUSIC FAS
% Open this file with Lilypond
% more information is available at lilypond.org
% Released under the GNU General Public License.

ii_part = \relative c''' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 dis8  cis8~ 
	cis8  d16  dis16~ 
		dis8.  dis16~ 
			dis16  d16  d8~  |
% ________________________________________bar 2 :
d8  cis16  dis16~ 
	dis8.  c16 
		cis8  d8~ 
			d8  cis8  |
% ________________________________________bar 3 :
cis8  d8~ 
	d8  c16  c16 
		dis4 
			c4  |
% ________________________________________bar 4 :
cis8  d8 
	d4 
		d4 
			dis4  |
% ________________________________________bar 5 :
dis16  cis16  dis8 
	cis4 
		cis4 
			d8  dis8  |
% ________________________________________bar 6 :
d8  cis8 
	cis4 
		d8  cis8 
}

hh_part = \relative c''' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 ais8  a8~ 
	a8  a8 
		gis4 
			b8  ais8  |
% ________________________________________bar 2 :
ais16  b8.~ 
	b16  a8.~ 
		a16  b8  ais16~ 
			ais16  b8  b16  |
% ________________________________________bar 3 :
ais8  b8 
	ais4 
		ais4 
			b8  b8  |
% ________________________________________bar 4 :
ais16  b8.~ 
	b16  gis8  b16~ 
		b16  ais8  a16~ 
			a16  a8.~  |
% ________________________________________bar 5 :
a16  ais8  a16~ 
	a8.  a16~ 
		a16  gis16  ais8 
			gis4  |
% ________________________________________bar 6 :
gis8  b8 
	gis8  a8~ 
		a8 
}

gg_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 e16  g8  e16~ 
	e16  f8.~ 
		f16  e8  g16~ 
			g16  g8.~  |
% ________________________________________bar 2 :
g16  fis8.~ 
	fis16  f8.~ 
		f16  fis8.~ 
			fis16  fis8.~  |
% ________________________________________bar 3 :
fis16  g8  g16~ 
	g16  fis16  e16  fis16~ 
		fis16  g16  f16  g16~ 
			g8.  e16  |
% ________________________________________bar 4 :
f8  e8~ 
	e8  g8 
		g8  e16  g16 
			e16  g8.~  |
% ________________________________________bar 5 :
g16  fis8  fis16~ 
	fis16  e8.~ 
		e16  g8.~ 
			g16  fis16  e16  g16~  |
% ________________________________________bar 6 :
g16  f8 
}

ff_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 cis16  cis8.~ 
	cis16  dis8.~ 
		dis16  dis16  d8~ 
			d8  dis16  cis16  |
% ________________________________________bar 2 :
dis4 
	cis4 
		d8  dis8 
			cis16  c8  c16~  |
% ________________________________________bar 3 :
c8.  dis16 
	cis4 
		d4 
			dis8  d8  |
% ________________________________________bar 4 :
d8  cis8 
	d8  d16  d16 
		d4 
			dis4  |
% ________________________________________bar 5 :
c4 
	d4 
		d16  dis16  cis8 
			dis4  |
% ________________________________________bar 6 :
d4 
	cis8  c16  c16 
}

ee_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 ais8  b8 
	b16  gis8.~ 
		gis16  b8.~ 
			b16  gis8  a16~  |
% ________________________________________bar 2 :
a16  a8.~ 
	a16  gis8  b16~ 
		b8.  b16 
			ais8  gis8  |
% ________________________________________bar 3 :
gis16  gis16  ais8 
	ais4 
		a4 
			a16  ais16  a8  |
% ________________________________________bar 4 :
b16  b8  a16 
	ais4 
		gis4 
			a4  |
% ________________________________________bar 5 :
b4 
	ais4 
		a4 
			ais4  |
% ________________________________________bar 6 :
a4 
	ais16  a8.~ 
		a16  gis16  ais16 
}

dd_part = \relative c'' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 g8  g16  fis16 
	fis16  f8  e16 
		g16  g8  f16~ 
			f8.  f16~  |
% ________________________________________bar 2 :
f8.  f16~ 
	f16  f8  f16~ 
		f8.  fis16 
			fis8  f8~  |
% ________________________________________bar 3 :
f8  f16  f16 
	fis16  e8.~ 
		e16  g8.~ 
			g16  e16  fis8~  |
% ________________________________________bar 4 :
fis8  e8~ 
	e8  fis16  f16 
		fis8  g8 
			fis4  |
% ________________________________________bar 5 :
fis4 
	f8  fis8~ 
		fis8  g8~ 
			g8  f8  |
% ________________________________________bar 6 :
f8  fis8 
	e4 
		fis4 
			e4  |
% ________________________________________bar 7 :
e4 
	f4 
		g4 
			g8  e8~  |
% ________________________________________bar 8 :
e8  f8~ 
	f8 
}

cc_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 c16  c8  d16~ 
	d16  c8.~ 
		c16  d16  cis8~ 
			cis8  dis16  dis16  |
% ________________________________________bar 2 :
c16  cis8.~ 
	cis16  cis8.~ 
		cis16  dis8  cis16~ 
			cis8.  cis16~  |
% ________________________________________bar 3 :
cis8.  dis16~ 
	dis8.  d16 
		c16  dis16  dis8 
			d16  cis8  d16  |
% ________________________________________bar 4 :
cis4 
	cis16  dis8.~ 
		dis16  d8  cis16 
			c8  c16  cis16~  |
% ________________________________________bar 5 :
cis8.  c16~ 
	c16  d8  dis16~ 
		dis16  c8  cis16 
			cis4  |
% ________________________________________bar 6 :
dis8  c16  c16~ 
	c16  d8.~ 
		d16  cis8.~ 
			cis16  cis8.~  |
% ________________________________________bar 7 :
cis16  dis8.~ 
	dis16  dis8.~ 
		dis16  dis8.~ 
			dis16 
}

bb_part = \relative c' 
{

\time 4/4

\clef tenor 
% ________________________________________bar 1 :
 ais4 
	a8  a8 
		a4 
			a16  ais8.~  |
% ________________________________________bar 2 :
ais16  gis8  b16~ 
	b8.  gis16 
		a16  b8  b16~ 
			b16  gis8.~  |
% ________________________________________bar 3 :
gis16  a8  a16~ 
	a16  gis16  gis16  ais16 
		b8  gis8~ 
			gis8  b16  ais16~  |
% ________________________________________bar 4 :
ais16  ais8.~ 
	ais16  gis16  a8 
		b16  a16  b8 
			b4  |
% ________________________________________bar 5 :
b16  b8.~ 
	b16  b8.~ 
		b16  ais16  gis16  ais16~ 
			ais8.  b16  |
% ________________________________________bar 6 :
gis8  b16  a16~ 
	a8.  a16 
		a8  a8~ 
			a8  gis8~  |
% ________________________________________bar 7 :
gis8  gis8 
	gis16 
}

aa_part = \relative c 
{

\time 4/4

\clef bass 
% ________________________________________bar 1 :
 f16  e16  fis16  e16~ 
	e8.  fis16~ 
		fis8.  fis16~ 
			fis8.  fis16  |
% ________________________________________bar 2 :
e16  fis16  e8~ 
	e8  e16  f16 
		e8  e16  f16~ 
			f16  f16  e8~  |
% ________________________________________bar 3 :
e8  f16  f16~ 
	f8.  g16 
		f4 
			e8  g8  |
% ________________________________________bar 4 :
fis8  fis8 
	f8  e8 
		g4 
			f16  f8.~  |
% ________________________________________bar 5 :
f16  e8.~ 
	e16  fis16  f16  g16~ 
		g16  f16  g8~ 
			g8  g8  |
% ________________________________________bar 6 :
e16  e8  g16~ 
	g16  e16  fis8~ 
		fis8  e8~ 
			e8  g16  g16~  |
% ________________________________________bar 7 :
g8. 
}


\header {
	composer = "with [notes] and [mainscore] objects "
	title = "A nine voice "
	subtitle = "example "
}


\score {
	<<
	\new Staff \with { instrumentName = "ii" } {
		<<
		\new Voice {
			\ii_part
		}
		>>
	}
	\new Staff \with { instrumentName = "hh" } {
		<<
		\new Voice {
			\hh_part
		}
		>>
	}
	\new Staff \with { instrumentName = "gg" } {
		<<
		\new Voice {
			\gg_part
		}
		>>
	}
	\new Staff \with { instrumentName = "ff" } {
		<<
		\new Voice {
			\ff_part
		}
		>>
	}
	\new Staff \with { instrumentName = "ee" } {
		<<
		\new Voice {
			\ee_part
		}
		>>
	}
	\new Staff \with { instrumentName = "dd" } {
		<<
		\new Voice {
			\dd_part
		}
		>>
	}
	\new Staff \with { instrumentName = "cc" } {
		<<
		\new Voice {
			\cc_part
		}
		>>
	}
	\new Staff \with { instrumentName = "bb" } {
		<<
		\new Voice {
			\bb_part
		}
		>>
	}
	\new Staff \with { instrumentName = "aa" } {
		<<
		\new Voice {
			\aa_part
		}
		>>
	}
	>>
	\layout {
		\mergeDifferentlyHeadedOn
		\mergeDifferentlyDottedOn
		\set Staff.pedalSustainStyle = #'mixed
		#(set-default-paper-size "a3landscape")
	}
	\midi { }
}

\version "2.18.2"
% mainscore Pd External version testing 
