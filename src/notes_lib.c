// code for the "notes_lib" common file. 
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// updated by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License. 

#include "notes_lib.h"

////	____________________________________________________ FUNCTIONS
float reduce_meter(int a) 					{
	float b, c;
	
	if 		(a == 2) { a = 1; 	b = .16;	}
	else if (a == 6) { a = 3; 	b = .16;	}
	else if (a == 10){ a = 5; 	b = .16;	}
	else if (a == 14){ a = 7; 	b = .16;	} 
	else if (a == 18){ a = 9; 	b = .16;	} 
	else if (a == 22){ a = 11; 	b = .16;	}
	else if (a == 26){ a = 13; 	b = .16;	}
	else if (a == 30){ a = 15; 	b = .16;	}

	else if (a == 4) { a = 1; 	b = .08;	} 
	else if (a == 12){ a = 3; 	b = .08;	}
	else if (a == 20){ a = 5; 	b = .08;	}
	else if (a == 28){ a = 7; 	b = .08;	}

	else if (a == 8) { a = 1; 	b = .04;	} 
	else if (a == 16){ a = 2; 	b = .04;	} 
	else if (a == 24){ a = 3; 	b = .04;	}
	else if (a == 32){ a = 4; 	b = .04;	}
	
	else {a = 0; b = 0;}

	c = a + b;
	return (c);
}
int get_beatsize(int a, int b, int c) 		{
	// a = num, b = den, c = refdur
	int m, beatsize;
	
	if 		(b == 4) {
		beatsize = exp2f( (float) (log2f((float) c) - log2f((float) b)));
	}
	else if 		(b == 8 || b == 16 || b == 32) {
		m = b / 2;
		if 		(a == 4) {
			beatsize = exp2f( (float) (log2f((float) c) - log2f((float) m)));
			beatsize = beatsize / 2;
		}
		else if (a == 7 || a == 8 || a == 10 || a == 13) {
			beatsize = exp2f( (float) (log2f((float) c) - log2f((float) m)));
		}
		else if (a == 3 || a == 5 || a == 6 || a == 9 || a == 11 || a == 12) {
			beatsize = exp2f( (float) (log2f((float) c) - log2f((float) m)));
		//	beatsize = (beatsize / 2);
		}
		else {
			beatsize = exp2f( (float) (log2f((float) c) - log2f((float) m)));
			beatsize = (beatsize / 2);
		}
	}
	else beatsize = exp2f( (float) (log2f((float) c) - log2f((float) a)));
	
	if (beatsize < 2) beatsize = 2;
	
//	if (beatsize == 16) beatsize = 8;
	
	return (beatsize);
}
int pow2test(int a) 						{
	if ((a & (a - 1)) == 0) {return 1;}
	else 					{return 0;}
}
int pow2dottest(int a) 						{
	int b;
	b = (int) ((a / 3) * 2);
	if (((b/2)*3) != a)	{return 0;}
	else {
		if ((b & (b - 1)) == 0) {return 1;}
		else 					{return 0;}
	}
}
int pow2ordot(int a) 						{
	int t1, t2;
	if ((a & (a - 1)) == 0) {t1 = 1;}
	else 					{t1 = 0;}
	int b;
	b = (int) ((a / 3) * 2);
	if (((b/2)*3) != a)		{t2 = 0;}
	else {
		if ((b & (b - 1)) == 0) {t2 = 1;}
		else 					{t2 = 0;}
	}
	t1 = t1+t2;
	if (t1>0) 	{return 1;}
	else 		{return 0;}
}
void find_relative(int a, FILE *f) 			{
	int temp;
	temp = (int) a - 48;
//	fprintf(f, " ");
//	post("find_relative function, float = %d", temp);
	if		(temp >=  55 && temp <=  66)	{	fprintf(f, "\\relative c''''' \n\{\n\n");	} 
	else if	(temp >=  43 && temp <=  54)	{	fprintf(f, "\\relative c'''' \n\{\n\n");	} 
	else if	(temp >=  31 && temp <=  42)	{	fprintf(f, "\\relative c''' \n\{\n\n");		} 
	else if	(temp >=  19 && temp <=  30)	{	fprintf(f, "\\relative c'' \n\{\n\n");		}
	else if	(temp >=   7 && temp <=  18)	{	fprintf(f, "\\relative c' \n\{\n\n");		}
	else if	(temp >=  -6 && temp <=   6)	{	fprintf(f, "\\relative c \n\{\n\n");		}
	else if (temp >= -18 && temp <=  -7)	{	fprintf(f, "\\relative c, \n\{\n\n");		}
	else if (temp >= -30 && temp <= -18)	{	fprintf(f, "\\relative c,, \n\{\n\n");		}
	else if (temp >= -42 && temp <= -31)	{	fprintf(f, "\\relative c,,, \n\{\n\n");		}
	else if (temp >= -54 && temp <= -43)	{	fprintf(f, "\\relative c,,,, \n\{\n\n");	}
	else if (temp >= -66 && temp <= -55)	{	fprintf(f, "\\relative c,,,,, \n\{\n\n");	}
}
void find_pitch(float a, int b, char g[]) 	{
///////////////////////////// a = current note, b = accidentals 0 = is or  1= es 
///////////////////////////// g=note[] (char)
	int p;
	float f;
	f = (float) a;
	p = a;
//	post ("f1=%f", f);
//	post ("p =%d", p);
	f -= ((float) p);
//	post ("f2=%f", f);
	
	if (p < 0) {
		g[0] = 'r'; 
		g[1] = '\0';
	}
	else {
		p = p % 12; // see if it is a natural or altered note (# or b) // assign note name, c, d, etc.
		if		(p ==  0)	{	g[0] = 'c'; g[1] = '\0';	
				if	(b==0 && f==0.5) { g[0] = 'c'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'd'; g[1] = 'e'; g[2] = 's'; g[3] = 'e';	g[4] = 'h'; g[5] = '\0';}
		}
		else if (p ==  1)	{
			if (b == 0)			{ g[0] = 'c'; g[1] = 'i'; g[2] = 's'; g[3] = '\0';}
			if (b==1)			{ g[0] = 'd'; g[1] = 'e'; g[2] = 's'; g[3] = '\0';}
			if (b==0 && f==0.5) { g[0] = 'c'; g[1] = 'i'; g[2] = 's'; g[3] = 'i';	g[4] = 'h'; g[5] = '\0';} 
			if (b==1 && f==0.5) { g[0] = 'd'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';}
		}
		else if (p ==  2)	{	g[0] = 'd'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'd'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'e'; g[1] = 'e'; g[2] = 's'; g[3] = 'e';	g[4] = 'h'; g[5] = '\0';}
		}
		else if (p ==  3)	{
			if (b==0)			{ g[0] = 'd'; g[1] = 'i'; g[2] = 's'; g[3] = '\0';}
			if (b==1)			{ g[0] = 'e'; g[1] = 'e'; g[2] = 's'; g[3] = '\0';}
			if (b==0 && f==0.5) { g[0] = 'd'; g[1] = 'i'; g[2] = 's'; g[3] = 'i';	g[4] = 'h'; g[5] = '\0';} 
			if (b==1 && f==0.5) { g[0] = 'e'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';}
		}
		else if (p ==  4)	{	g[0] = 'e'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'e'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'f'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';} 
		}
		else if (p ==  5)	{	g[0] = 'f'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'f'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'g'; g[1] = 'e'; g[2] = 's'; g[3] = 'e';	g[4] = 'h'; g[5] = '\0';}
		}
		else if (p ==  6)	{
			if (b==0)			{ g[0] = 'f'; g[1] = 'i'; g[2] = 's'; g[3] = '\0';}
			if (b==1)			{ g[0] = 'g'; g[1] = 'e'; g[2] = 's'; g[3] = '\0';}
			if (b==0 && f==0.5) { g[0] = 'f'; g[1] = 'i'; g[2] = 's'; g[3] = 'i';	g[4] = 'h'; g[5] = '\0';} 
			if (b==1 && f==0.5) { g[0] = 'g'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';}
		}
		else if (p ==  7)	{	g[0] = 'g'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'g'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'a'; g[1] = 'e'; g[2] = 's'; g[3] = 'e';	g[4] = 'h'; g[5] = '\0';}
		}
		else if (p ==  8)	{
			if (b==0)			{ g[0] = 'g'; g[1] = 'i'; g[2] = 's'; g[3] = '\0';}
			if (b==1)			{ g[0] = 'a'; g[1] = 'e'; g[2] = 's'; g[3] = '\0';}
			if (b==0 && f==0.5) { g[0] = 'g'; g[1] = 'i'; g[2] = 's'; g[3] = 'i';	g[4] = 'h'; g[5] = '\0';} 
			if (b==1 && f==0.5) { g[0] = 'a'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';}
		}
		else if (p ==  9)	{	g[0] = 'a'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'a'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'b'; g[1] = 'e'; g[2] = 's'; g[3] = 'e';	g[4] = 'h'; g[5] = '\0';}
		}
		else if (p == 10)	{
			if (b==0)			{ g[0] = 'a'; g[1] = 'i'; g[2] = 's'; g[3] = '\0';}
			if (b==1)			{ g[0] = 'b'; g[1] = 'e'; g[2] = 's'; g[3] = '\0';}
			if (b==0 && f==0.5) { g[0] = 'a'; g[1] = 'i'; g[2] = 's'; g[3] = 'i';	g[4] = 'h'; g[5] = '\0';} 
			if (b==1 && f==0.5) { g[0] = 'b'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';}
		}
		else				{	g[0] = 'b'; g[1] = '\0';						
				if	(b==0 && f==0.5) { g[0] = 'b'; g[1] = 'i'; g[2] = 'h'; g[3] = '\0';} 
				if	(b==1 && f==0.5) { g[0] = 'c'; g[1] = 'e'; g[2] = 'h'; g[3] = '\0';} 
		}
	}
}
int  find_jump(int a, int b, int c, char g[]) 		{   
	int jmp, direction, i, accidental;
	accidental = c;
	int sharp_pitches[250] = { 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9,  9, 10, 11, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 20, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 34, 35, 36, 36, 37, 37, 38, 39, 39, 40, 40, 41, 41, 42, 43, 43, 44, 44, 45, 46, 46, 47, 47, 48, 48, 49, 50, 50, 51, 51, 52, 53, 53, 54, 54, 55, 55, 56, 57, 57, 58, 58, 59, 60, 60, 61, 61, 62, 62, 63, 64, 64, 65, 65, 66, 67, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75, 75, 76, 76, 77, 78, 78, 79, 79, 80, 81, 81, 82, 82, 83, 83, 84, 85, 85, 86, 86, 87, 88, 88, 89, 89, 90, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 98, 99, 99,  100, 100, 101, 102, 102, 103, 103, 104, 104, 105, 106, 106, 107, 107, 108, 109, 109, 110, 110, 111, 111, 112, 113, 113, 114, 114, 115, 116, 116, 117, 117, 118, 118, 119};
	int flat_pitches[250] =  { 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 9, 9, 10, 10, 11, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20, 21, 21, 22, 23, 23, 24, 24, 25, 26, 26, 27, 27, 28, 28, 29, 30, 30, 31, 31, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39, 40, 40, 41, 41, 42, 42, 43, 44, 44, 45, 45, 46, 47, 47, 48, 48, 49, 49, 50, 51, 51, 52, 52, 53, 54, 54, 55, 55, 56, 56, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 70, 71, 72, 72, 73, 73, 74, 75, 75, 76, 76, 77, 77, 78, 79, 79, 80, 80, 81, 82, 82, 83, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 90, 91, 91, 92, 93, 93, 94, 94, 95, 96, 96, 97, 97, 98, 98, 99, 100, 100, 101, 101, 102, 103, 103, 104, 104, 105, 105, 106, 107, 107, 108, 108, 109, 110, 110, 111, 111, 112, 112, 113, 114, 114, 115, 115, 116, 117, 117, 118, 118, 119, 119};
	int	pitch_current, pitch_previous, interval;
	i = 1;
	if (b < 0) b = abs(b);
	if(accidental == 0) {
		pitch_current 	= sharp_pitches[abs(a)];
		pitch_previous 	= sharp_pitches[abs(b)];
	}
	else {
		pitch_current 	= flat_pitches[abs(a)];
		pitch_previous 	= flat_pitches[abs(b)];
	}
	jmp = a - b;
	if (jmp >= 0) direction = 1;
	else direction = 0;
	if (a < 0) interval = 1;
	else {
		if (direction == 1) {
			interval = pitch_current - pitch_previous + 1;
			if (interval < 0) {
				interval = pitch_previous - pitch_current;
				interval = interval * -1 + 8;
			}
		}
		else {
			interval = pitch_previous - pitch_current + 1;
			if (interval < 0) {
				interval = pitch_current - pitch_previous;
				interval = interval * -1 + 8;
			}
			interval = interval * -1;
		}
	}
	if		(interval 					 < -67) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = ','; g[5] = ','; g[6] = ','; g[7] = ','; g[8] = ','; g[9] = '\0';}
	else if	(interval >= -60 && interval < -53) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = ','; g[5] = ','; g[6] = ','; g[7] = ','; g[8] = '\0';}
	else if	(interval >= -53 && interval < -46) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = ','; g[5] = ','; g[6] = ','; g[7] = '\0';}
	else if	(interval >= -46 && interval < -39) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = ','; g[5] = ','; g[6] = '\0';}
	else if	(interval >= -39 && interval < -32) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = ','; g[5] = '\0';}
	else if	(interval >= -32 && interval < -25) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = ','; g[4] = '\0';}
	else if	(interval >= -25 && interval < -18) 	{g[0] = ','; g[1] = ','; g[2] = ','; g[3] = '\0';}
	else if	(interval >= -18 && interval < -11) 	{g[0] = ','; g[1] = ','; g[2] = '\0';}
	else if	(interval >= -11 && interval <  -4) 	{g[0] = ','; g[1] = '\0';}
	else if (interval >=  -4 && interval <=  4) 	{i = 0; g[0] = '\0';}
	else if (interval >=   4 && interval <= 11) 	{g[0] = '\''; g[1] = '\0';}
	else if	(interval >   11 && interval <= 18) 	{g[0] = '\''; g[1] = '\''; g[2] = '\0';}	
	else if	(interval >   18 && interval <= 25) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\0';}
	else if	(interval >   25 && interval <= 32) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\0';}
	else if	(interval >   32 && interval <= 39) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\''; g[5] = '\0';}	
	else if	(interval >   39 && interval <= 46) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\''; g[5] = '\''; g[6] = '\0';}	
	else if	(interval >   46 && interval <= 53) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\''; g[5] = '\''; g[6] = '\''; g[7] = '\0';}
	else if	(interval >   53 && interval <= 60) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\''; g[5] = '\''; g[6] = '\''; g[7] = '\''; g[8] = '\0';}	
	else if	(interval >					    67) 	{g[0] = '\''; g[1] = '\''; g[2] = '\''; g[3] = '\''; g[4] = '\''; g[5] = '\''; g[6] = '\''; g[7] = '\''; g[8] = '\''; g[9] = '\0';}		
	return(i);
} 
void find_clef(int a, FILE *f) 				{
	if		(a==0)	fprintf(f, "\\clef treble "); // 
	else if	(a==1)	fprintf(f, "\\clef alto "); //  
	else if	(a==2)	fprintf(f, "\\clef tenor "); //, 
	else if	(a==3)	fprintf(f, "\\clef bass "); //, 
	else if	(a==4)	fprintf(f, "\\clef french "); //
	else if	(a==5)	fprintf(f, "\\clef soprano "); // , 
	else if	(a==6)	fprintf(f, "\\clef mezzosoprano "); // 
	else if	(a==7)	fprintf(f, "\\clef baritone "); // 
	else if	(a==8)	fprintf(f, "\\clef varbaritone "); // 
	else if	(a==9)	fprintf(f, "\\clef percussion "); //
}
void find_articulation(int a, FILE *f) 		{
	if		(a==0)	fprintf(f, "\\accent"); // 
	else if	(a==1)	fprintf(f, "\\espressivo"); //  
	else if	(a==2)	fprintf(f, "\\marcato"); //, 
	else if	(a==3)	fprintf(f, "\\portato"); //, 
	else if	(a==4)	fprintf(f, "\\staccatissimo"); //
	else if	(a==5)	fprintf(f, "\\staccato"); // 
	else if	(a==6)	fprintf(f, "\\tenuto"); //
	else if	(a==7)	fprintf(f, "\\shortfermata"); // 
	else if	(a==8)	fprintf(f, "\\fermata"); // 
	else if	(a==9)	fprintf(f, "\\longfermata"); //
	else if	(a==10)	fprintf(f, "\\verylongfermata"); //
	else if	(a==11)	fprintf(f, "\\upbow "); //
	else if	(a==12)	fprintf(f, "\\downbow "); //
	else if	(a==13)	fprintf(f, "\\flageolet"); //
	else if	(a==14)	fprintf(f, "\\thumb"); //
	else if	(a==15)	fprintf(f, "\\snappizzicato"); //
	else if	(a==16)	fprintf(f, "\\open"); //
	else if	(a==17)	fprintf(f, "\\halfopen"); //
	else if	(a==18)	fprintf(f, "\\stopped"); //
	else if	(a==19)	fprintf(f, "\\lheel"); //
	else if	(a==20)	fprintf(f, "\\rheel"); //
	else if	(a==21)	fprintf(f, "\\ltoe"); //
	else if	(a==22)	fprintf(f, "\\rtoe"); //
	else if	(a==23)	fprintf(f, "\\laissezVibrer "); //,
	else if	(a==24)	fprintf(f, "^\\markup { \\sharp }"); //, \markup { \sharp } " \\xNote ");
	else if	(a==25)	fprintf(f, "^\\markup { \\flat }"); //,	"\\harmonic"); //,	
	else if	(a==26)	fprintf(f, "^\\markup { \\natural }"); //	
	else if	(a==27)	fprintf(f, "\\trill"); //
	else if	(a==28)	fprintf(f, "\\prall"); //
	else if	(a==29)	fprintf(f, "\\mordent"); //
	else if	(a==30)	fprintf(f, "\\prallmordent"); //
	else if	(a==31)	fprintf(f, "\\upprall"); //, 
	else if	(a==32)	fprintf(f, "\\downprall"); //, 
	else if	(a==33)	fprintf(f, "\\upmordent"); //, 
	else if	(a==34)	fprintf(f, "\\downmordent"); //, 
	else if	(a==35)	fprintf(f, "\\lineprall"); //, 
	else if	(a==36)	fprintf(f, "\\prallprall"); //, 
	else if	(a==37)	fprintf(f, "\\pralldown"); //, 
	else if	(a==38)	fprintf(f, "\\prallup"); //, 
	else if	(a==39)	fprintf(f, "\\turn"); //,
	else if	(a==40)	fprintf(f, "\\reverseturn"); //,  
	else if	(a==41)	fprintf(f, "\\segno"); //		
	else if	(a==42)	fprintf(f, "\\coda"); //		
	else if	(a==43)	fprintf(f, "\\varcoda"); //
	else if	(a==44)	fprintf(f, "\\breathe"); //
	else if	(a==45)	fprintf(f, "\\bendAfter #+4 "); //
	else if	(a==46)	fprintf(f, "\\bendAfter #-4 "); //
	else if	(a==47)	fprintf(f, "-\\markup{pizz.}"); //
	else if	(a==48)	fprintf(f, "-\\markup{arco}"); //
	else if	(a==49)	fprintf(f, "-\\markup{vib.}"); //
	else if	(a==50)	fprintf(f, "-\\markup{senza vib.}"); //			
}
void find_dynamics(int a, FILE *f) 			{
	if		(a==0)	fprintf(f, "\\<"); // 
	else if	(a==1)	fprintf(f, "\\>"); // 
	else if	(a==2)	fprintf(f, "\\!"); // 
	else if	(a==3)	fprintf(f, "\\ppppp"); // 
	else if	(a==4)	fprintf(f, "\\pppp"); // 
	else if	(a==5)	fprintf(f, "\\ppp"); // 
	else if	(a==6)	fprintf(f, "\\pp"); // 
	else if	(a==7)	fprintf(f, "\\p"); // 
	else if	(a==8)	fprintf(f, "\\mp"); // 
	else if	(a==9)	fprintf(f, "\\mf"); // 
	else if	(a==10)	fprintf(f, "\\f"); // 
	else if	(a==11)	fprintf(f, "\\ff"); // 
	else if	(a==12)	fprintf(f, "\\fff"); // 
	else if	(a==13)	fprintf(f, "\\ffff"); // 
	else if	(a==14)	fprintf(f, "\\fffff"); //
	else if	(a==15)	fprintf(f, "\\fp");
	else if	(a==16)	fprintf(f, "\\sf");
	else if	(a==17)	fprintf(f, "\\sff");
	else if	(a==18)	fprintf(f, "\\sp");
	else if	(a==19)	fprintf(f, "\\spp");
	else if	(a==20)	fprintf(f, "\\sfz");
	else if	(a==21)	fprintf(f, "\\rfz");
	else if (a>=22) post("notes: Warning: Only dynamics 0 through 21 are predefined");
}
void find_small_numbers(int a, FILE *f) 	{
	fprintf(f, "-%i", a);
}
void find_span(int a, FILE *f) 				{
	if		(a==0)	fprintf(f, "\\glissando"); // GLISSANDO
	else if	(a==1)	fprintf(f, "\\sustainOn"); //  SUSTAIN
	else if	(a==2)	fprintf(f, "\\sustainOff"); //  STOP SUSTAIN
	else if	(a==3)	fprintf(f, "("); //, SLUR 
	else if	(a==4)	fprintf(f, ")"); //, STOP SLUR
	else if	(a==5)	fprintf(f, "\\startTrillSpan"); // TRILL SPAN
	else if	(a==6)	fprintf(f, "\\stopTrillSpan"); //STOP TRILL SPAN
	else if	(a==7)	fprintf(f, "\\glissando");// \\glissandoSkipOn"); // 
	else if	(a==8)	fprintf(f, "\\glissandoSkipOff"); // 	
}
void find_stafftext(int a, char g[]) 		{
	int n, total;
	char fst[6];
	total = a;
	if (total < 10) {
		n = total;
		if		(n==0) strcpy( fst, "zero");	
		else if	(n==1) strcpy( fst, "one");
		else if (n==2) strcpy( fst, "two");
		else if (n==3) strcpy( fst, "three");
		else if (n==4) strcpy( fst, "four");
		else if (n==5) strcpy( fst, "five");
		else if (n==6) strcpy( fst, "six");
		else if (n==7) strcpy( fst, "seven");
		else if (n==8) strcpy( fst, "eight");
		else if (n==9) strcpy( fst, "nine");
	}
	else {
		n = (int) ((float) total / 10.);
		if		(n==0) strcpy( fst, "zero");	
		else if	(n==1) strcpy( fst, "one");
		else if (n==2) strcpy( fst, "two");
		else if (n==3) strcpy( fst, "three");
		else if (n==4) strcpy( fst, "four");
		else if (n==5) strcpy( fst, "five");
		else if (n==6) strcpy( fst, "six");
		else if (n==7) strcpy( fst, "seven");
		else if (n==8) strcpy( fst, "eight");
		else if (n==9) strcpy( fst, "nine");
		n = total - (n*10);
		if		(n==0) strcat( fst, "zero");	
		else if	(n==1) strcat( fst, "one");
		else if (n==2) strcat( fst, "two");
		else if (n==3) strcat( fst, "three");
		else if (n==4) strcat( fst, "four");
		else if (n==5) strcat( fst, "five");
		else if (n==6) strcat( fst, "six");
		else if (n==7) strcat( fst, "seven");
		else if (n==8) strcat( fst, "eight");
		else if (n==9) strcat( fst, "nine");
	}	/*	if		(n==0) { g[0]='z';g[1]='e';g[2]='r';g[3]='o';g[4]='\0';} 	
	else if	(n==1) { g[0]='o';g[1]='n';g[2]='e';g[3]='\0';} 
	else if (n==2) { g[0]='t';g[1]='w';g[2]='o';g[3]='\0';} 
	else if (n==3) { g[0]='t';g[1]='h';g[2]='r';g[3]='e';g[4]='e';g[5]='\0';}
	else if (n==4) { g[0]='f';g[1]='o';g[2]='u';g[3]='r';g[4]='\0';}
	else if (n==5) { g[0]='f';g[1]='i';g[2]='v';g[3]='e';g[4]='\0';}
	else if (n==6) { g[0]='s';g[1]='i';g[2]='x';g[3]='\0';} 
	else if (n==7) { g[0]='s';g[1]='e';g[2]='v';g[3]='e';g[4]='n';g[5]='\0';}
	else if (n==8) { g[0]='e';g[1]='i';g[2]='g';g[3]='h';g[4]='t';g[5]='\0';}
	else if (n==9) { g[0]='n';g[1]='i';g[2]='n';g[3]='e';g[4]='\0';}*/
	strcpy (g, fst);
}
void find_grace(int a, FILE *f) 			{
	if		(a==1)	fprintf(f, " \\grace {"); // 
	else if	(a==2)	fprintf(f, " \\slashedGrace {"); // 
	else if	(a==3)	fprintf(f, " \\acciaccatura {"); // 
	else if	(a==4)	fprintf(f, " \\appoggiatura {"); // 
}
void find_arpeggio(int a, FILE *f) 			{
	if		(a==1)	fprintf(f, " \\arpeggioArrowUp "); // 
	else if	(a==2)	fprintf(f, " \\arpeggioArrowDown "); // 
	else if	(a==3)	fprintf(f, " \\arpeggioNormal "); // 
}
void find_notehead(int a, FILE *f) 			{
	if		(a==1)	fprintf(f, "\\once \\override NoteHead.style = #'harmonic "); // 
	else if	(a==2)	fprintf(f, "\\xNote "); // 
	else if	(a==3)	fprintf(f, "\\once \\override NoteHead.style = #'triangle "); // 
	else if	(a==4)	fprintf(f, "\\once \\override NoteHead.style = #'fa "); // 
	else if	(a==5)	fprintf(f, "\\once \\override NoteHead.style = #'mensural "); // 
	else if	(a==6)	fprintf(f, "\\once \\override NoteHead.style = #'xcircle "); // 
	else if	(a==7)	fprintf(f, "\\once \\override NoteHead.style = #'diamond "); //
	else if	(a==8)	fprintf(f, "\\once \\override NoteHead.style = #'slash "); //
	else if	(a==9)	fprintf(f, "\\parenthesize "); // 
}
int readbarfile(int a[][8], FILE *f) {
    int row = 0;
    char * line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {
        // We expect 4 integer items. Actually, we can directly read into the output array
        // because the data type (int) matches the %d specifier.
        if (sscanf(line, "%d%d%d%d%d", &a[row][0], &a[row][1], &a[row][2], &a[row][3], &a[row][4]) != 5) {
            // handle error
        }
        row++;
    }
    free(line);
    return row;   
}
/*
int readbarfile(int a[][8], FILE *f)		{
	int i, ii, j, jj, strsize, temp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	char ss[10];
    temp=j=0;

	ii=0;
	while ((read = getline(&line, &len, f)) != -1) {
		jj 		= 4;
		strsize = (int) read;
		for (i=strsize-1; i>=0; i--){
			if 		( line[i] == (int) 32 || line[i] == (int) 10) { //space or newline
				if(i != (strsize-1)) {	
					a[ii][jj] = temp;
					jj--;
				}
				j=0;
				temp=0;
			}
			else	 {
				ss[0] = line[i];
				temp += atoi(ss)*( (int) pow((double)10, (double)j) );
				j++;
			}	
		}
		ii++;
	}
	return (ii);	
}*/
void copyfiles(FILE *f, FILE *g)			{
	char a;
	post("copyfiles");
	a = fgetc(g);
	if (a != EOF) fputc(a,  f);
	while(a != EOF)	{
		post("copyfiles");
		a = fgetc(g);
		if (a != EOF) fputc(a,  f);
	}
} // f1 into f2 

int compile(char *buf, char *name, int debug, char *lily_dir) {
    char cmdbuf[MAXPDSTRING];
    if (debug >= 1) post("notes: compiling score");

    snprintf(cmdbuf, MAXPDSTRING, "%s%slilypond -o %s %s", lily_dir, LYBINDIR, buf, name);

    cmdbuf[MAXPDSTRING-1] = 0;
    if (debug >= 1) post("notes: cmdbuf = %s", cmdbuf);
    // RENDER THE SCORE TO PDF
    if (!system(cmdbuf)) {    
      if (debug >= 1) post("notes: score compiled");
      return 0;
    } else {
      post("notes: score did not compile");
      post("... you might want to run the following command manually:\n");
      post("%s\n", cmdbuf);
      return 1;
    }
	// free(cmdbuf);
}

void open_pdf(char *buf) {
    char cmdbuf[MAXPDSTRING];
    post("notes: Opening PDF score");
    // OPEN THE .PDF SCORE (adapted from pdcontrol's browse method)
    snprintf(cmdbuf, MAXPDSTRING, "::pd_menucommands::menu_openfile {%s.pdf}\n", buf);
    cmdbuf[MAXPDSTRING-1] = 0;
    sys_gui(cmdbuf);
	// free(cmdbuf);
}

int compile_and_open(char *buf, char *name, int debug, int FOLLOW, int render, int OPEN, char *lily_dir) {
    if (!render) {
      if (debug >= 1) post("notes: skipping score rendering");
    } else if (FOLLOW == 1) {
      if (debug >= 1) post("notes: render disabled in FOLLOW mode");
    } else { // FOLLOW == 0 && render == 1
      if (!system(NULL)) {
        if (debug >= 1) post("notes: system() not found");
        return 1;
      } else {
        if(!compile(buf, name, debug, lily_dir))  {
            if (OPEN) open_pdf(buf);
         } else {
            if (debug >= 1) post("notes: score did not compile");
            return 1;
         }
      }
    }
    return 0;
}