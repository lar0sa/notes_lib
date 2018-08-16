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
	title = "ANEXO 3 "
	subtitle = "flute, part I"
}

inst_part = \relative c' 
{

\time 4/4

\clef treble 
% ________________________________________bar 1 :
 <beh' e>1\pp^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  }  \breathe
% ________________________________________bar 2 :
 <beh e>1(\pp\<^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  } 
 % ________________________________________bar 3 :
 <e cih'>1)\mp^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  }  \breathe
 % ________________________________________bar 4 :
 <beh e>1(\glissando\pp\<^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  } 
 % ________________________________________bar 5 :
 <b f'>1\glissando\>^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four1hT ))
            (lh . (b))
            (rh . ()))
    }
  } 
  % ________________________________________bar 6 :
 <beh e>1)\pp^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  } \breathe
  % ________________________________________bar 7 :
  <ees c'>1)\mf(^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two three four five1hT six))
            (lh . (b))
            (rh . (c cis)))
    }
  }
  % ________________________________________bar 8 :
  <e cis'>1)^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two three four1hT five six))
            (lh . (b))
            (rh . (cis )))
    }
  } \breathe 
  % ________________________________________bar 9 :
 <e cih'>1\mf\>^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  }  
% ________________________________________bar 10 :
 <beh e>1\pp^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (two three four five))
            (lh . (b))
            (rh . ()))
    }
  }  \breathe
  
% ________________________________________bar 11 :
 <aeh' e'>1(\mp\>^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two three1hT four five six))
            (lh . (b))
            (rh . (c cis)))
    }
  } 
  % ________________________________________bar 12 :
 <a f'>1^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))	(lh . (b))  (rh . (cis)))
    }
  } 
  % ________________________________________bar 13 :
 <cih, aeh'>1^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three  four five six))  (lh . (b))   (rh . (c cis)))
    }
  } 
  % ________________________________________bar 14 :
 <g cih aeh'>1^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))
            (lh . (b))
            (rh . (c cis)))
    }
  } 
  % ________________________________________bar 15 :
 <g cih>1^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))
            (lh . (b))
            (rh . (c cis)))
    }
  } 
  % ________________________________________bar 16 :
  <fis b>1\pp)^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))
            (lh . (b))
            (rh . (c cis b)))
    }
  } \breathe
   % ________________________________________bar 17 :
  <fis b>1(\pp)^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))
            (lh . (b))
            (rh . (c cis b)))
    }
  }
   % ________________________________________bar 18 :
  <fis gih'>1))^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two three1hT four five six))
            (lh . (b))
            (rh . (c cis b)))
    }
  } \breathe
     % ________________________________________bar 19 :
  <fis b>1\pp^
  \markup 
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two1hT three four five six))
            (lh . (b))
            (rh . (c cis b)))
    }
  } \breathe
     % ________________________________________bar 20 :
  <c' d'>1\ff^
  \markup
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two ))    (lh . (b))   (rh . (ees)))
    }
  } \breathe
   % ________________________________________bar 21 :
  <c des>1\pp^
  \markup
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (three four five six ))    (lh . (b))   (rh . (c cis)))
    }
  } \breathe
     % ________________________________________bar 22 :
  <cis e>1\f^
  \markup
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (two three four five ))    (lh . (b))   (rh . (d)))
    }
  } \breathe
       % ________________________________________bar 23 :
  <beh cis>1\pp^
  \markup
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . (one two three four five six ))    (lh . (b))   (rh . (cis)))
    }
  } \breathe
         % ________________________________________bar 23 :
  <beh ees>2^
  \markup
  \override #'(size . 0.6) {
    \center-column {
       \woodwind-diagram #'flute-b-extension #'
           ((cc . ( two three four five six1hT ))    (lh . (b))   (rh . (cis)))
    }
  } \breathe
}

\score {
	\new Staff {
		\new Voice {
			\inst_part
		}
	}
	\layout {
	  #(print-keys-verbose 'flute-b-extension (current-error-port))
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
