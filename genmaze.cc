/*

   Maze Generator   Copyright (x) 1995 DJ Delorie

   Permission granted to use this source for any purpose, provided
   this copyright notice remains present and intact.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/resource.h>

int print_mime = 1;
int solve = 0;
int html = 0;

#define GIF_GREY 0xcc

void
print_form()
{
  char *accept = getenv("HTTP_ACCEPT");
  printf("Content-type: text/html\n\n");
  system("header Maze Generator");
  printf("<form method=\"POST\" action=\"genmaze.cgi\">\n");
  printf("Number of cells across (1..N):\n");
  printf("<input type=text width=10 name=cols value=10><br>\n");

  printf("Number of cells up/down (1..N):\n");
  printf("<input type=text width=10 name=rows value=10><br>\n");

  printf("Type of maze: <select name=type>\n");
  printf("<option value=gif> GIF (cell size in pixels)\n");
  printf("<option value=text> Text (cell size in characters)\n");
  printf("</select><br>\n");

  printf("Width of each cell (2..N):\n");
  printf("<input type=text width=10 name=width><br>\n");
  printf("Height of each cell (2..N):\n");
  printf("<input type=text width=10 name=height><br>\n");
  
  printf("Random Number Seed (optional):\n");
  printf("<input type=text width=10 name=seed><br>\n");

  printf("<input type=submit value=Generate><img src=\"/icons/is-cgi.gif\" alt=\"[X]\"><p>\n");
  printf("</form>\n");

  system("trailer");
}

#define GO_LEFT		1
#define GO_RIGHT	2
#define GO_UP		4
#define GO_DOWN		8
#define USED		16
#define SOLUTION	32

#define M(x,y) maze_data[(x)+1+((y)+1)*(c+2)]

#define dprintf if(0)printf

void
generate_maze(int gif, int c, int r, int w, int h, int s)
{
  char *maze_data;
  int x, y;
  int *xt, *yt;

  if (c < 1 || r < 1 || w < 1 || h < 1)
    return;

  maze_data = (char *)calloc(r+2, c+2);
  xt = (int *)malloc(c*r*sizeof(int));
  yt = (int *)malloc(c*r*sizeof(int));

  for (x=0; x<c; x++)
    for (y=0; y<r; y++)
    {
      xt[x+y*c] = x;
      yt[x+y*c] = y;
    }

  for (x=-1; x<=c; x++)
  {
    M(x, -1) = USED;
    M(x, r) = USED;
  }
  for (y=0; y<=r; y++)
  {
    M(-1, y) = USED;
    M(c, y) = USED;
  }

  if (s == 0)
    s = time(0);
  srandom(s);

  for (x=r*c-1; x>0; x--)
  {
    y = random() % (x+1);
    if (y!=x)
    {
      int t = xt[x];
      xt[x] = xt[y];
      xt[y] = t;
      t = yt[x];
      yt[x] = yt[y];
      yt[y] = t;
    }
  }

  M(-1,0) |= USED | GO_RIGHT;
  M(0,0) |= USED | GO_LEFT;

  int num_left = r*c-1;
  while (num_left)
    for (x=0; x<c; x++)
      for (y=0; y<r; y++)
      {
	dprintf("%d, %d\n", x, y);
	while (1)
	{
	  int px = xt[x+y*c];
	  int py = yt[x+y*c];
	  int ways[8], wp;
	  if (!(M(px, py) & USED))
	    break;
	  dprintf("\tstarting\n");

	  while (1)
	  {
	    wp = 0;

	    if (!(M(px,py-1) & USED))
	      ways[wp++] = GO_UP;
	    if (!(M(px,py-1) & USED))
	      ways[wp++] = GO_UP;
	    if (!(M(px,py+1) & USED))
	      ways[wp++] = GO_DOWN;
	    if (!(M(px-1,py) & USED))
	      ways[wp++] = GO_LEFT;
	    if (!(M(px-1,py) & USED))
	      ways[wp++] = GO_LEFT;
	    if (!(M(px+1,py) & USED))
	      ways[wp++] = GO_RIGHT;
	    if (wp == 0)
	    {
	      dprintf("\t\tblocked at %d,%d\n", px, py);
	      break;		// blocked at this point
	    }
	    dprintf("\t\t%d ways found from %d,%d\n", wp, px, py);
	    
	    wp = random() % wp;
	    
	    switch (ways[wp])
	    {
	    case GO_LEFT:
	      dprintf("\t\tleft\n");
	      M(px,py) |= GO_LEFT;
	      px--;
	      M(px,py) |= GO_RIGHT | USED;
	      break;
	    case GO_RIGHT:
	      dprintf("\t\tright\n");
	      M(px,py) |= GO_RIGHT;
	      px++;
	      M(px,py) |= GO_LEFT | USED;
	      break;
	    case GO_UP:
	      dprintf("\t\tup\n");
	      M(px,py) |= GO_UP;
	      py--;
	      M(px,py) |= GO_DOWN | USED;
	      break;
	    case GO_DOWN:
	      dprintf("\t\tdown\n");
	      M(px,py) |= GO_DOWN;
	      py++;
	      M(px,py) |= GO_UP | USED;
	      break;
	    }
	    num_left--;
	  }
	  dprintf("\tending at %d,%d\n", px, py);
	  if (px == xt[x+y*c] && py == yt[x+y*c])
	    break;
	}
      }
  
  M(c,r-1) |= USED | GO_LEFT;
  M(c-1,r-1) |= USED | GO_RIGHT;
  
  if (solve)
  {
    for (x=0; x<c; x++)
      for (y=0; y<r; y++)
	M(x,y) |= SOLUTION;
    M(-1,0) |= SOLUTION;
    M(0,0) |= SOLUTION;
    M(c,r-1) |= SOLUTION;
    M(c-1,r-1) |= SOLUTION;
    
    for (x=0; x<c; x++)
      for (y=0; y<r; y++)
      {
	int px = x;
	int py = y;
	int ways[4], wp;
	
	while (1)
	{
	  wp = 0;
	  
	  if (M(px,py) & GO_UP && M(px,py-1) & SOLUTION)
	    ways[wp++] = GO_UP;
	  if (M(px,py) & GO_DOWN && M(px,py+1) & SOLUTION)
	    ways[wp++] = GO_DOWN;
	  if (M(px,py) & GO_LEFT && M(px-1,py) & SOLUTION)
	    ways[wp++] = GO_LEFT;
	  if (M(px,py) & GO_RIGHT && M(px+1,py) & SOLUTION)
	    ways[wp++] = GO_RIGHT;
	  if (wp != 1)
	    break;		// not a dead end
	  
	  switch (ways[0])
	  {
	  case GO_LEFT:
	    M(px,py) &= ~SOLUTION;
	    px--;
	    break;
	  case GO_RIGHT:
	    M(px,py) &= ~SOLUTION;
	    px++;
	    break;
	  case GO_UP:
	    M(px,py) &= ~SOLUTION;
	    py--;
	    break;
	  case GO_DOWN:
	    M(px,py) &= ~SOLUTION;
	    py++;
	    break;
	  }
	}
      }
  }
  
  if (!gif)
  {
    int i;
    printf("<pre>\n");
    for (y=0; y<=r; y++)
    {
      putchar('+');
      for (x=0; x<c; x++)
      {
	if (M(x,y) & GO_UP || x==-1)
	  for (i=1; i<w; i++)
	    putchar((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? '#' : ' ');
	else
	  for (i=1; i<w; i++)
	    putchar('-');
	printf("+");
      }
      printf("\n");
      if (y<r)
	for (int dy=1; dy<h; dy++)
	{
	  if (M(0,y) & GO_LEFT)
	    putchar((M(0,y)&SOLUTION && M(-1,y)&SOLUTION) ? '#' : ' ');
	  else
	    putchar('|');
	  for (x=0; x<c; x++)
	  {
	    for (i=1; i<w; i++)
	      putchar(M(x,y)&SOLUTION?'#':' ');
	    if (M(x,y) & GO_RIGHT)
	      putchar((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? '#' : ' ');
	    else
	      printf("|");
	  }
	  printf("\n");
	}
    }
    printf("</pre>\n");
  }
  else
  {
    // 0 = lines  GIF_GREY = blank  255 = solution
    int i;
    FILE *trans = popen("/usr/bin/ppmtogif 2>/dev/null", "w");
    fprintf(trans, "P5\n%d %d %d\n", (c+2)*w+1, (r+2)*h+1, 255);
    for (i=0; i<((c+2)*w+1) * h; i++)
      fputc(GIF_GREY, trans);
    for (y=0; y<=r; y++)
    {
      for (i=0; i<w; i++)
	fputc(GIF_GREY, trans);
      fputc(0, trans);
      for (x=0; x<c; x++)
      {
	if (M(x,y) & GO_UP || x==-1)
	  for (i=1; i<w; i++)
	    fputc((M(x,y)&SOLUTION && M(x,y-1)&SOLUTION) ? 255 : GIF_GREY, trans);
	else
	  for (i=1; i<w; i++)
	    fputc(0, trans);
	fputc(0, trans);
      }
      for (i=0; i<w; i++)
	fputc(GIF_GREY, trans);
      if (y<r)
	for (int dy=1; dy<h; dy++)
	{
	  for (i=0; i<w; i++)
	    fputc(M(-1,y)&SOLUTION ? 255 : GIF_GREY, trans);
	  if (M(0,y) & GO_LEFT)
	    fputc((M(-1,y)&SOLUTION) ? 255 : GIF_GREY, trans);
	  else
	    fputc(0, trans);
	  for (x=0; x<c; x++)
	  {
	    for (i=1; i<w; i++)
	      fputc((M(x,y)&SOLUTION) ? 255 : GIF_GREY, trans);
	    if (M(x,y) & GO_RIGHT)
	      fputc((M(x,y)&SOLUTION && M(x+1,y)&SOLUTION) ? 255 : GIF_GREY, trans);
	    else
	      fputc(0, trans);
	  }
	  for (i=0; i<w; i++)
	    fputc(M(c,y)&SOLUTION ? 255 : GIF_GREY, trans);
	}
    }
    for (i=0; i<((c+2)*w+1) * h; i++)
      fputc(GIF_GREY, trans);
    pclose(trans);
  }
}


void
generate_maze(int argc, char **argv)
{
  char *maze_data;
  int c=10, r=10, w=3, h=2, s=0, gif=0, x, y;
  
  if (strcmp(argv[1], "gif") == 0)
  {
    gif = 1;
    w = h = 10;
  }
  
  if (argc > 2) c = atoi(argv[2]);
  if (argc > 3) r = atoi(argv[3]);
  if (argc > 4) w = atoi(argv[4]);
  if (argc > 5) h = atoi(argv[5]);
  if (argc > 6) s = atoi(argv[6]);

  if (s == 0)
    s = (int)time(0);
  
  if (html)
  {
    printf("Content-type: text/html\n\n");
    if (solve)
      system("header Maze Solution");
    else
      system("header Generated Maze");
    
    if (strcmp(argv[1], "text") == 0)
    {
      print_mime = 0;
      printf("<center>");
      generate_maze(0, c, r, w, h, s);
      printf("</center>");
    }
    else
      printf("<center><img src=\"genmaze.cgi?%sgif+%d+%d+%d+%d+%d\"></center><p>\n",
	     solve?"solve+":"",
	     c, r, w, h, s);

    if (!solve)
      printf("<center><a href=\"genmaze.cgi?html+solve+%s+%d+%d+%d+%d+%d\">Solution</a><img src=\"/icons/is-cgi.gif\" alt=\"[X]\"></center><br>\n",
	     gif?"gif":"text", c, r, w, h, s);
    system("trailer -p genmaze.cgi");
  }
  else
  {
    if (gif)
      printf("Content-type: image/gif\n\n");
    else
      printf("Content-type: text/html\n\n");
    
    generate_maze(gif, c, r, w, h, s);
  }
}

int
main(int argc, char **argv)
{
  setbuf(stdout, 0);
  if (setpriority(PRIO_PROCESS, 0, 20))
    exit(1);
  if (strcasecmp(getenv("REQUEST_METHOD")?:"", "post"))
  {
    if (argc == 1)
    {
      print_form();
      return 0;
    }
    else
    {
      while (1)
      {
	if (strcmp(argv[1], "solve") == 0)
	  solve = 1;
	else if (strcmp(argv[1], "html") == 0)
	  html = 1;
	else
	  break;
	argc--;
	argv++;
      }
      generate_maze(argc, argv);
      return 0;
    }
  }
  
  printf("Content-type: text/html\n\n");
  
  int cols=10, rows=10, cwidth=0, cheight=0, seed=(int)time(0);
  char *type = "text";
  
  char name[100], val[100], *cp=name, *end=name+sizeof(name)-1;
  int cl = atoi(getenv("CONTENT_LENGTH")?:"0"), i, ch;
  for (i=0; ; i++)
  {
    if (i < cl)
      ch = getc(stdin);
    else
      ch = 0;
    if (ch == '=')
    {
      *cp = 0;
      cp = val;
      end = val+sizeof(val)-1;
    }
    else if (ch == '&' || ch == 0)
    {
      *cp = 0;
      cp = name;
      end = name+sizeof(name)-1;
      
      if (strcmp(name, "cols") == 0)
	cols = atoi(val);
      else if (strcmp(name, "rows") == 0 && val[0])
	rows = atoi(val);
      else if (strcmp(name, "type") == 0 && val[0])
	type = strdup(val);
      else if (strcmp(name, "width") == 0 && val[0])
	cwidth = atoi(val);
      else if (strcmp(name, "height") == 0 && val[0])
	cheight = atoi(val);
      else if (strcmp(name, "seed") == 0 && val[0])
	seed = atoi(val);
      
      if (ch == 0)
	break;
    }
    else
      {
        *cp++ = ch;
	if (cp >= end)
	  cp--;
      }
  }
  if (cwidth == 0)
    if (strcmp(type, "text") == 0)
      cwidth = 3;
    else
      cwidth = 10;
  if (cheight == 0)
    if (strcmp(type, "text") == 0)
      cheight = 2;
    else
      cheight = 10;
  
  if (cols < 1 || cols > 100
      || rows < 1 || rows > 100
      || cwidth < 2 || cwidth > 30
      || cheight < 2 || cheight > 30)
  {
    printf("Invalid parameters.  cells 1..100, cell size 2..30\n");
    return 0;
  }
  if (cols*cwidth > 600 || rows * cheight > 600)
  {
    printf("Invalid parameters.  Image cannot exceed 600x600\n");
    return 0;
  }
  if (seed == 0)
    seed = (int)time(0);
  
  system("header Generated Maze");
  
  if (strcmp(type, "text") == 0)
  {
    print_mime = 0;
    printf("<center>");
    generate_maze(0, cols, rows, cwidth, cheight, seed);
    printf("</center>");
  }
  else
    printf("<center><img src=\"genmaze.cgi?gif+%d+%d+%d+%d+%d\"></center><p>\n",
	   cols, rows, cwidth, cheight, seed);
  printf("<center><a href=\"genmaze.cgi?html+solve+%s+%d+%d+%d+%d+%d\">Solution</a><img src=\"/icons/is-cgi.gif\" alt=\"[X]\"></center><br>\n",
	 type, cols, rows, cwidth, cheight, seed);
  
  system("trailer -p genmaze.cgi");
  
  return 0;
}
