#include "graph.h"
#include "param.h"
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
static int MAXPATH = 5;
#define _CRT_SECURE_NO_WARNINGS

void init_graph(graph_t *g) {
  for (int i = 0; i < MAXNODE; i++) {
    g->v[i].head.next = NULL;
    g->v[i].src = i;
  }
}

bool rm_head(ghead_t *h) {
  if (h->head.next) {
    return false;
  }
  gnode_t *tmp;
  tmp = h->head.next;
  h->head.next = tmp->next;
  free(tmp);
  return true;
}

void clear_graph(graph_t *g) {
  for (int i = 0; i < MAXNODE; i++) {
    while (rm_head(&g->v[i]))
      ;
    g->v[i].head.next = NULL;
  }
}

void ghinsert(ghead_t *h, int dst, double w) {
  gnode_t *tmp = h->head.next;
  gnode_t *cur = (gnode_t *)malloc(sizeof(gnode_t));
  h->head.next = cur;
  cur->next = tmp;
  cur->dst = dst;
  cur->w = w;
}

void ginsert(graph_t *g, int src, int dst, double w) {
  ghinsert(&g->v[src], dst, w);
}

// without new line character
void ghprint_with_weight(ghead_t *h) {
  gnode_t *cur;
  int i = 0;
  for (cur = h->head.next; cur; cur = cur->next) {
    printf("-->%c(%g)", cur->dst + 'a', cur->w);
    i++;
  }
  printf(",%d", i);
}

void ghprint(FILE *f, ghead_t *h) {
  if (!f)
    return;
  gnode_t *cur;
  int i = 0;
  for (cur = h->head.next; cur; cur = cur->next) {
    fprintf(f, " %c", cur->dst + 'a');
    i++;
  }
  // fprintf(f, " : %d edge(s)", i);
}

void ghprint_networkx(FILE *fnx, ghead_t *h, city_t src) {
  assert(fnx != NULL);
  gnode_t *cur;
  for (cur = h->head.next; cur; cur = cur->next) {
    fprintf(fnx, "G.add_edge(\"%c\", \"%c\")\n", src + 'a', cur->dst + 'a');
  }
  // fprintf(f, " : %d edge(s)", i);
}

#define _CRT_SECURE_NO_WARNINGS

void gprint(graph_t *g) {
  FILE *f, *fnx;
  f = fopen("./pathinfo/graph_structure.txt", "w");
  fnx = fopen("./pathinfo/graph_structure_networkx.py", "w");
  assert(f != NULL && fnx != NULL);
  fprintf(fnx, "import matplotlib.pyplot as plt\nimport networkx as "
               "nx\nG=nx.DiGraph()\n");
  for (int i = 0; i < MAXNODE; i++)
    fprintf(fnx, "G.add_node(\"%c\")\n", i + 'a');
  for (int i = 0; i < MAXNODE; i++) {
    fprintf(f, "[%c]: (x:%g,y:%g)\t", i + 'a', g->v[i].p.x, g->v[i].p.y);
    ghprint(f, &g->v[i]);
    fprintf(f, "\n");
    ghprint_networkx(fnx, &g->v[i], i);
    // fprintf(fnx, "\n");
  }
  fprintf(fnx, "layout = nx.circular_layout(G)\n");
  fprintf(fnx, "nx.draw_networkx(G, pos=layout, with_labels=True)\n");
  fprintf(fnx, "plt.show()\n");
  fclose(f);
  fclose(fnx);
}

double get_dist(graph_t *g, int src, int dst) {
  double ret, x0, x1, y0, y1, dx, dy;

  x0 = g->v[src].p.x;
  y0 = g->v[src].p.y;

  x1 = g->v[dst].p.x;
  y1 = g->v[dst].p.y;

  dx = fabs(x0 - x1);
  dy = fabs(y0 - y1);
  ret = sqrt(dx * dx + dy * dy);

  return ret;
}

void print_point(point_t p) { printf("x: %g, y: %g", p.x, p.y); }

point_t get_rand_point(unsigned seed) {
  srand((unsigned)time(NULL) + seed);
  point_t ret;
  ret.x = (rand() / (double)RAND_MAX) * MAX_X;
  ret.y = (rand() / (double)RAND_MAX) * MAX_Y;
  return ret;
}
int get_num_of_edges(bool mark[][MAXNODE], city_t src) {
  int ret;
  ret = 0;
  for (int i = 0; i < MAXNODE; i++)
    if (mark[src][i])
      ret++;
  return ret;
}
void get_rand_graph(graph_t *g, bool mark[][MAXNODE]) {
  FILE *file_point_dat = fopen("./pathinfo/node_locations.dat", "wb");
  FILE *file_graph_mark = fopen("./pathinfo/node_adj.dat", "wb");
  assert(file_point_dat != NULL);
  assert(file_graph_mark != NULL);
  point_t p;
  point_t p_save[MAXNODE];
  int dst;
  init_graph(g);
  for (int i = 0; i < MAXNODE; i++) {
    p = get_rand_point(i);
    g->v[i].p = p;
    p_save[i] = p;
  }
  fwrite(p_save, sizeof(point_t), MAXNODE, file_point_dat);
LOOP:
  srand((unsigned)time(NULL));
  for (int src = 0; src < MAXNODE; src++)
    memset(mark[src], false, sizeof(mark[src]));
  for (int src = 0; src < MAXNODE; src++) {
    for (int cnt = get_num_of_edges(mark, src); cnt < 10;) {
      int start_time = time(NULL);
      while (true) {
        if (start_time != time(NULL)) // no hope
          goto LOOP;
        dst = rand() % MAXNODE;
        if (src == dst)
          continue;
        if (!mark[src][dst] && (get_num_of_edges(mark, dst) < 10))
          break;
      }
      mark[src][dst] = true;
      mark[dst][src] = true;
      cnt++;
    }
  }
  fwrite(mark, sizeof(bool) * MAXNODE * MAXNODE, 1, file_graph_mark);
  for (int src = 0; src < MAXNODE; src++)
    for (int dst = 0; dst < MAXNODE; dst++)
      if (mark[src][dst] && src != dst)
        ginsert(g, src, dst, get_dist(g, src, dst));

  gprint(g);
  fclose(file_point_dat);
  fclose(file_graph_mark);
}

void print_mark(bool mark[][MAXNODE]) {
  for (int i = 0; i < MAXNODE; i++) {
    for (int j = 0; j < MAXNODE; j++)
      printf("%d ", mark[i][j] ? 1 : 0);
    printf("\n");
  }
}

int do_dfs(graph_t *g, city_t intermediate, city_t intermediate_src,
           path_t *path) {
  if (path->pidx >= MAXPATH) {
    return UNFOUND;
  }
  int pidx;
  double actual_time;
  tunit_t curtime;
  city_t next;

  double adt = ((get_dist(g, intermediate, intermediate_src) * 60.0) /
                ((double)VELOCITY));
  tunit_t dt = adt / 5.0;

  pidx = path->pidx + 1;
  curtime = path->curtime + dt;
  actual_time = path->actual_time_min + adt;

  path->pidx = pidx;
  path->curtime = curtime;
  path->actual_time_min = actual_time;
  if (intermediate == path->dst) {
    path->path[pidx] = intermediate + 'a';
    path->dtime[pidx] = curtime;
    return FOUND;
  }

  for (int i = ceil_tunit(path->curtime); i < MAXFLIGHT * MAXDAY; i++) {
    path->pidx = pidx;
    path->actual_time_min = i * 5;
    path->curtime = i;
    path->dtime[pidx] = i;
    next = g->v[intermediate].t.dsts[i];
    path->path[pidx] = intermediate + 'a';
    if (do_dfs(g, next, intermediate, path) == FOUND)
      return FOUND;
  }
  path->path[pidx] = '\0';
  path->dtime[pidx] = -1;
  path->pidx--;
  path->actual_time_min = actual_time - adt;
  path->curtime = curtime - dt;

  return UNFOUND;
}

int dfs(graph_t *g, city_t src, city_t dst, tunit_t curtime, path_t *path) {
  city_t next;
  path->src = src;
  path->dst = dst;
  path->curtime = curtime;
  path->actual_time_min = curtime * 5;
  memset(path->path, 0x0, sizeof(path->path));
  memset(path->dtime, 0x0, sizeof(path->dtime));

  for (int i = ceil_tunit(curtime); i < curtime + MAXFLIGHT; i++) {
    path->pidx = 0;
    next = g->v[src].t.dsts[i];
    path->curtime = i;
    path->actual_time_min = i * 5;
    path->dtime[0] = i;
    path->path[0] = src + 'a';
    if (do_dfs(g, next, src, path) == FOUND)
      return FOUND;
  }

  return UNFOUND;
}

void print_acutual_time(double acutual_time) {
  mhd_t t;
  t.d = (int)((int)(acutual_time / 60) / 24) + 1;
  t.m = ((int)acutual_time) % 60;
  t.h = (((int)acutual_time) / 60) % 24;
  print_mhd(t);
}

void print_path(path_t *p) {
  int len = strlen(p->path);
  if (len == 0)
    return;
  int i;
  for (i = 0; i < len - 1; i++) {
    printf("%c(", p->path[i]);
    print_tunit(p->dtime[i]);
    printf(")-");
  }
  printf("%c(", p->path[i]);
  print_acutual_time(p->actual_time_min);
  printf(")");
}

int cnt = 0;
bool __is_connected_(graph_t *g, city_t cur, city_t dst) {
  cnt++;
  if (cur == dst)
    return true;
  if (cnt >= MAXPATH)
    return false;
  ghead_t *h = &g->v[cur];
  gnode_t *n = h->head.next;
  for (; n; n = n->next)
    if (__is_connected_(g, n->dst, dst)) {
      cnt--;
      return true;
    }
  cnt--;
  return false;
}

bool is_connected(graph_t *g, city_t src, city_t dst) {
  cnt = 0;
  ghead_t *h = &g->v[src];
  gnode_t *n = h->head.next;
  for (; n; n = n->next)
    if (__is_connected_(g, n->dst, dst))
      return true;
  return true;
}

int find_path(graph_t *g, city_t src, city_t dst, int day, path_t *p) {
  if (src == dst) {
    printf("src == dst\n");
    return UNFOUND;
  }
  extern int MAXPATH;
  mhd_t time;
  tunit_t curtime;
  time.d = day;
  time.h = 0;
  time.m = 0;
  curtime = get_tunit(time);

  MAXPATH = 1;
LOOP:
  if (MAXPATH > MAXDEPTH)
    goto ERROR;

  if (is_connected(g, src, dst))
    if (dfs(g, src, dst, curtime, p) == FOUND)
      goto DONE;
  MAXPATH *= 2;
  goto LOOP;
ERROR:
  return UNFOUND;
DONE:
  return FOUND;
}

void load_graph(graph_t *g, bool mark[][MAXNODE]) {
  FILE *file_point_dat = fopen("./pathinfo/node_locations.dat", "rb");
  FILE *file_graph_mark = fopen("./pathinfo/node_adj.dat", "rb");
  assert(file_point_dat != NULL);
  assert(file_graph_mark != NULL);
  point_t p_save[MAXNODE];
  init_graph(g);
  fread(p_save, sizeof(point_t), MAXNODE, file_point_dat);
  for (int i = 0; i < MAXNODE; i++) {
    g->v[i].p = p_save[i];
  }
  fread(mark, sizeof(bool) * MAXNODE * MAXNODE, 1, file_graph_mark);
  for (int src = 0; src < MAXNODE; src++)
    for (int dst = 0; dst < MAXNODE; dst++)
      if (mark[src][dst] && src != dst)
        ginsert(g, src, dst, get_dist(g, src, dst));

  gprint(g);
  fclose(file_point_dat);
  fclose(file_graph_mark);
}

void init_flight_system(graph_t *g, bool mark[][MAXNODE], bool isrand) {
  if (isrand) {
    get_rand_graph(g, mark);
    for (int i = 0; i < MAXNODE; i++)
      get_rand_table(&(g->v[i].t), i, mark);
  } else {
    load_graph(g, mark);
    for (int i = 0; i < MAXNODE; i++)
      load_table(&(g->v[i].t), i, mark);
  }
}
