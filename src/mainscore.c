// code for the "mainscore" pd class. 
// Encodes information created in Pd into a Lilypond score (lilypond.org)
// developed by Jaime Oliver La Rosa (la.rosa@nyu.edu)
// @ the NYU Waverly Labs in the Music Department - FAS. (nyu-waverlylabs.org)
// with contributions by Fede Camara Halac (fch226@nyu.edu)
// Released under the GNU General Public License. 

#include "notes_lib.h" 

////	____________________________________________________ MAIN STRUCT
typedef struct mainscore 														{
  t_object x_ob;
  t_outlet *x_outlet0, *x_outlet1, *x_outlet2;
  t_canvas *x_canvas;
  FILE *fp1;
  
  int part_n[MXV][2], i_part_n[MXV][2];
  char parts[MXV][2][130], i_parts[MXV][2][130];
  char title[64][130], sub_title[64][130], author[64][130], osname[130], lily_dir[MAXPDSTRING], barfile[MAXPDSTRING], inst[150];
 
  const char *dummysym; // const to remove warning
  int ii, debug, auth_n, titl_n, sub_title_n;
  int inst_n, papersize, paperorientation, part_i, i_part_i, voice, total_voices;
  int open;
} 
t_mainscore;
////	____________________________________________________ INPUT
void mainscore_part(t_mainscore *x, t_symbol *s, int argcount, t_atom *argvec) {
	int a;
	a = argcount;
	a = 0;
	x->dummysym = s->s_name;
	
	if (argvec[a].a_type 	== A_FLOAT 	&& 
		argvec[a+1].a_type 	== A_FLOAT 	&& 
		argvec[a+2].a_type 	== A_SYMBOL && 
		argvec[a+3].a_type 	== A_SYMBOL		) {
			x->i_part_n[x->i_part_i][0]	=	argvec[a].a_w.w_float;		/// part number
			x->i_part_n[x->i_part_i][1]	=	argvec[a+1].a_w.w_float;	/// voice number
			strcpy(x->i_parts[x->i_part_i][0], argvec[a+2].a_w.w_symbol->s_name);/// inst name
			strcpy(x->i_parts[x->i_part_i][1], argvec[a+3].a_w.w_symbol->s_name);/// path
		//	post("mainscore:path:: %i\t%i\t%i\t%s\t%s", x->i_part_i, x->i_part_n[x->i_part_i][0], x->i_part_n[x->i_part_i][1], x->i_parts[x->i_part_i][0], x->i_parts[x->i_part_i][1]);
			x->i_part_i++;
	}
	else {
		post("MAINSCORE:::::::::::: wrong input format, please format to: part no., voice no., inst name, file path.");
	}
}
////	____________________________________________________ WRITE
void mainscore_write(t_mainscore *x, t_symbol *s)								{
//	post("WRITE METHOD");
	int i, min, j, k, m, d, done[x->i_part_i];
	char a;
	char buf[MAXPDSTRING], partpath[MAXPDSTRING], scorename[MAXPDSTRING], linename[MAXPDSTRING];
	FILE *fp1, *fp2;
//// _______________________________________________ REORDER INPUT
	post("mainscore: Sorting Input ...");
	k=d=0;
	while(d < x->i_part_i){
		min = 1000000;
		for (i=0; i<x->i_part_i; i++){
			if(x->i_part_n[i][0] <= min){
				m = 0;
				for (j=0; j<d; j++){
					if (i == done[j]) m = 1;
				}
				if (m == 0) {
					min = x->i_part_n[i][0];
					k = i;
				}
			}
		}
		x->part_n[d][0]	=		x->i_part_n[k][0];	/// part number
		x->part_n[d][1]	=		x->i_part_n[k][1];	/// voice number
		strcpy(x->parts[d][0], 	x->i_parts[k][0]);	/// inst name
		strcpy(x->parts[d][1], 	x->i_parts[k][1]);	/// path
		done[d]			= 		k;
	//	post("%d\t%d\t%d\t%s\t%s\t", d, x->part_n[d][0], x->part_n[d][1], x->parts[d][0], x->parts[d][1]);
		d++;
	}
//	post("Copying");
	x->part_i = x->i_part_i;
	for (i=0; i<x->i_part_i; i++){
		x->i_part_n[i][0]	=	x->part_n[i][0];	/// part number
		x->i_part_n[i][1]	=	x->part_n[i][1];	/// voice number
		strcpy(x->i_parts[i][0], x->parts[i][0]);	/// inst name
		strcpy(x->i_parts[i][1], x->parts[i][1]);	/// path
	}
//	post("sorting voices");
	for (i=0; i<x->i_part_i; i++){
		if(x->i_part_n[i][0] == x->i_part_n[i+1][0]) {
			if(x->i_part_n[i][1] > x->i_part_n[i+1][1]) {
		//	post("yyyyyyyyyyyyyyyy");
				x->part_n[i][0]		=		x->i_part_n[i+1][0];	/// part number
				x->part_n[i][1]		=		x->i_part_n[i+1][1];	/// voice number
				strcpy(x->parts[i][0], 		x->i_parts[i+1][0]);	/// inst name
				strcpy(x->parts[i][1], 		x->i_parts[i+1][1]);	/// path
				x->part_n[i+1][0]	=		x->i_part_n[i][0];	/// part number
				x->part_n[i+1][1]	=		x->i_part_n[i][1];	/// voice number
				strcpy(x->parts[i+1][0], 	x->i_parts[i][0]);	/// inst name
				strcpy(x->parts[i+1][1], 	x->i_parts[i][1]);	/// path
				i++;
			}
			else {
				x->part_n[i][0]	=			x->i_part_n[i][0];	/// part number
				x->part_n[i][1]	=			x->i_part_n[i][1];	/// voice number
				strcpy(x->parts[i][0], 		x->i_parts[i][0]);	/// inst name
				strcpy(x->parts[i][1], 		x->i_parts[i][1]);	/// path
			}
		}
		else {
			x->part_n[i][0]	=			x->i_part_n[i][0];	/// part number
			x->part_n[i][1]	=			x->i_part_n[i][1];	/// voice number
			strcpy(x->parts[i][0], 		x->i_parts[i][0]);	/// inst name
			strcpy(x->parts[i][1], 		x->i_parts[i][1]);	/// path
		}
	}
	for (i=0; i<x->i_part_i; i++){	
	//	post("%d\t%d\t%d\t%s\t%s\t", i, x->part_n[i][0], x->part_n[i][1], x->parts[i][0], x->parts[i][1]);
	}
//// _______________________________________________ OPEN FILE		
	post("mainscore: ... Formatting Score... ");
	canvas_makefilename(x->x_canvas, s->s_name, buf, MAXPDSTRING); /// This is a Pd function to get the path relative to the canvas
	sys_bashfilename(buf, buf);
	strcpy( scorename, buf);
	strcat( scorename, ".ly");
	fp1 = fopen(scorename, "w");
	if(!fp1)						{
		pd_error(x,"%s: couldn't create", buf);
		return;
	}
//// _______________________________________________ WRITE SCORE	
	else 							{  
		post("mainscore: writing into %s", scorename);
		fprintf(fp1, "%% [notes] external for Pure Data\n%% version 0.2 August 2, 2022 \n%% by Jaime E. Oliver La Rosa\n%% la.rosa@nyu.edu\n%% @ the Waverly Labs in NYU MUSIC FAS\n%% With contributions from Fede Camara Halac\n%% Open this file with Lilypond\n%% more information is available at lilypond.org\n%% Released under the GNU General Public License.\n\n");
		//// _______________________________________ COPY PARTS TO MAIN SCORE
		for (i=0; i<x->part_i; i++) {	
			strcpy(partpath, x->parts[i][1]);
			post("mainscore: reading %s", partpath);
			fp2 = fopen(partpath, "r");
			a = fgetc(fp2);
			if (a != EOF) fputc(a,  fp1);
			while(a != EOF)	{
				a = fgetc(fp2);
				if (a != EOF) fputc(a,  fp1);
			}
			fprintf(fp1, "\n");
			fclose(fp2);
		}
		//// __________________________________________ SCORE EXPRESSION
		if (x->auth_n > 0 || x->titl_n > 0 || x->sub_title_n > 0) {
			fprintf(fp1, "\n\\header {");
			if (x->auth_n 		> 0) {
				fprintf(fp1, "\n\tcomposer = \"");
				for(i=0; i<x->auth_n; i++){
					fprintf(fp1, "%1.32s ", x->author[i]);
				}
				fprintf(fp1, "\"");
			}
			if (x->titl_n 		> 0) {
				fprintf(fp1, "\n\ttitle = \"");
				for(i=0; i<x->titl_n; i++){
					fprintf(fp1, "%1.32s ", x->title[i]);
				}
				fprintf(fp1, "\"");
			}
			if (x->sub_title_n 	> 0) {
				fprintf(fp1, "\n\tsubtitle = \"");
				for(i=0; i<x->sub_title_n; i++){
					fprintf(fp1, "%1.32s ", x->sub_title[i]);
				}
				fprintf(fp1, "\"");
			}
			fprintf(fp1, "\n}\n\n");
		} //	HEADER Title, subtitle, and Author	
		fprintf(fp1, "\n\\score {\n\t<<");
		for (i=0; i<x->part_i; i++) {
			strcpy(linename, x->parts[i][0]);
			strcat(linename, "_part");
			fprintf(fp1, "\n\t\\new Staff \\with { instrumentName = \"%s\" } ", x->parts[i][0]);
			fprintf(fp1, "{\n\t\t<<\n\t\t\\new Voice {");
			if (x->part_n[i][0] == x->part_n[i+1][0]) {
				if 		(x->part_n[i][1] <= 1) {
					fprintf(fp1, "\n\t\t\t\\voiceOne");
					fprintf(fp1, "\n\t\t\t\\%s\n\t\t}", linename);
				}
				while (x->part_n[i][0] == x->part_n[i+1][0]) {
					i++;
					strcpy(linename, x->parts[i][0]);
					strcat(linename, "_part");
					fprintf(fp1, "\n\t\t\\new Voice {");
				 	fprintf(fp1, "\n\t\t\t\\voiceTwo");
				 	fprintf(fp1, "\n\t\t\t\\%s\n\t\t}", linename);
				}
				fprintf(fp1, "\n\t\t>>\n\t}");
			}
			else {
				fprintf(fp1, "\n\t\t\t\\%s\n\t\t}\n\t\t>>\n\t}", linename);
			}
		}
		fprintf(fp1, "\n\t>>\n\t\\layout {");	
		fprintf(fp1, "\n\t\t\\mergeDifferentlyHeadedOn");
		fprintf(fp1, "\n\t\t\\mergeDifferentlyDottedOn");
		fprintf(fp1, "\n\t\t\\set Staff.pedalSustainStyle = #'mixed");
		fprintf(fp1, "\n\t\t#(set-default-paper-size \"a%i", x->papersize);
		if(x->paperorientation==1) fprintf(fp1, "landscape\")");
		else fprintf(fp1, "\")");
		fprintf(fp1, "\n\t}\n\t\\midi { }\n}");	
		fprintf(fp1, "\n\n\\version \"2.18.2\"\n%% mainscore Pd External version 0.2 \n");
		fclose(fp1);
		post("mainscore: .ly score finished");
    // compile and open
//	if(compile_and_open(buf,scorename,x->debug,x->FOLLOW,x->render,x->open, x->lily_dir)){ //according to notes
	if(compile_and_open(buf, scorename, x->debug, 0, 1, x->open, x->lily_dir)){
    //if(compile_and_open(buf, scorename, x->debug, 0, 1, x->open,LYBINDIR)){
      pd_error(x, "mainscore: error compiling score");
    }
    }  // if a file is correctly provided.
	//*/
}
////	____________________________________________________ CLEAR
void mainscore_clear(t_mainscore *x)											{	
	x->part_i = x->i_part_i = 0;
    x->auth_n = x->titl_n = x->sub_title_n = 0; 
	post("mainscore: Cleared");
}
////	____________________________________________________ OPENING SWITCH
void mainscore_open(t_mainscore *x, t_floatarg f) 							{
	int i;
	if (f == 0) {
		i = 0;
		post("mainscore: score opening off");
	}
	else {
		i = 1;
		post("mainscore: score opening on");
	}
	x->open = i;
}
////	____________________________________________________ DEBUG  
void mainscore_debug(t_mainscore *x, t_floatarg f) 								{	
	x->debug = (int) f;
	post("debugging level = %d", x->debug);
} 
////	____________________________________________________ TITLE
void mainscore_title(t_mainscore *x, t_symbol *s, int argc, t_atom *argv) 		{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->title[i], 1000);
	//	post(x->title[i]);
	}	
	x->titl_n = argc;
}
////	____________________________________________________ SUB_TITLE  
void mainscore_sub_title(t_mainscore *x, t_symbol *s, int argc, t_atom *argv) 	{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->sub_title[i], 1000);
	//	post(x->sub_title[i]);
	}	
	x->sub_title_n = argc;
}
////	____________________________________________________ AUTHOR
void mainscore_author(t_mainscore *x, t_symbol *s, int argc, t_atom *argv) 		{
	x->dummysym = s->s_name;
	int i;
	for(i=0;i<argc;i++){
		atom_string(argv+i, x->author[i], 1000);
	//	post(x->author[i]);
	}
	x->auth_n = argc;	
}
////	____________________________________________________ Lilypond Location
void mainscore_lily_dir(t_mainscore *x, t_symbol *s, int argc, t_atom *argv) 	{
	int i; i = argc;
	x->dummysym = s->s_name;
	atom_string(argv, x->lily_dir, 1000);
	post("mainscore: Lilypond directory set to: %s", x->lily_dir);
}
////	____________________________________________________ PAPER SIZE
void mainscore_paper(t_mainscore *x, t_floatarg f, t_floatarg g) 								{	
	x->papersize 		= (int) f;
	x->paperorientation = (int) g;
} 

t_class *mainscore_class;
void *mainscore_new(t_floatarg ff)												{
    t_mainscore *x = (t_mainscore *)pd_new(mainscore_class);
//	inlet_new(&x->x_ob, &x->x_ob.ob_pd, gensym("symbol"), gensym("readfile"));
  	x->x_outlet0 = outlet_new(&x->x_ob, &s_symbol);
//  x->x_outlet1 = outlet_new(&x->x_ob, &s_symbol);
  	x->x_canvas = canvas_getcurrent();
	strcpy(x->lily_dir, LYDIR); // see notes_lib.h
	// strcpy( x->lily_dir, "~/bin");
    strcpy (x->inst, "inst");
    x->debug 				= 0;
    x->auth_n = x->titl_n 	= 0; 
    x->papersize 			= 4;
	x->paperorientation 	= 0;
	x->part_i = x->part_i	= 0;
	x->total_voices			= (int) ff;
    x->open = 1;
    return (void *)x;
}
void mainscore_setup(void)														{
    mainscore_class = 	class_new(gensym("mainscore"), (t_newmethod)mainscore_new, 0, sizeof(t_mainscore), 0, A_DEFFLOAT, 0);

	class_addmethod(mainscore_class, (t_method)mainscore_part, 		gensym("part"), 	A_GIMME, 	0);
	class_addmethod(mainscore_class, (t_method)mainscore_write, 	gensym("write"), 	A_SYMBOL,	0);	
	class_addmethod(mainscore_class, (t_method)mainscore_title, 	gensym("title"), 	A_GIMME, 	0);
	class_addmethod(mainscore_class, (t_method)mainscore_sub_title, gensym("sub_title"),A_GIMME, 	0);
	class_addmethod(mainscore_class, (t_method)mainscore_author, 	gensym("author"), 	A_GIMME, 	0);
	class_addmethod(mainscore_class, (t_method)mainscore_lily_dir, 	gensym("lily_dir"), A_GIMME,	0);
	class_addmethod(mainscore_class, (t_method)mainscore_clear, 	gensym("clear"), 				0);
	class_addmethod(mainscore_class, (t_method)mainscore_debug, 	gensym("debug"), 	A_DEFFLOAT, 0);
	class_addmethod(mainscore_class, (t_method)mainscore_paper, 	gensym("paper"), 	A_DEFFLOAT, A_DEFFLOAT, 0);
    class_addmethod(mainscore_class, (t_method)mainscore_open, 	gensym("open"), 	A_DEFFLOAT, 0);
    class_sethelpsymbol(mainscore_class, gensym("notes"));
	//post("mainscore:\ttesting: 20220802-1");
}