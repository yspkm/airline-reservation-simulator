#include "table.h"
#include <string.h>
#include <assert.h>

mhd_t get_mhd(tunit_t t)
{
    mhd_t ret;
    ret.m = (int)(t * 5) % 60;
    ret.h = (((int)(t * 5)) / 60) % 24;
    ret.d = ((int)(t * 5) / 1440) % 31 + 1;
    return ret;
}

enum ampm get_ampm(tunit_t in)
{
    mhd_t tmp = get_mhd(in);
    return get_ampm_mhd(tmp);
}

enum ampm get_ampm_mhd(mhd_t in)
{
    return in.h >= 12 ? PM : AM;
}

// without new line
void print_mhd_time_taken(mhd_t in);
void print_tunit_time_taken(tunit_t in);

void print_mhd_time_taken(mhd_t in)
{
    int hour = in.h;
    enum ampm a = get_ampm_mhd(in);
    assert(in.h < 24);
    if (a == PM && hour > 12)
        hour -= 12;
    printf("%d:%d%s", hour, in.m, get_ampm_mhd(in) == PM ? "pm" : "am");
    printf(", %d", in.d);
}

// without new line
void print_tunit_time_taken(tunit_t in)
{
    mhd_t tmp;
    tmp = get_mhd(in);
    print_mhd(tmp);
}

// without new line
void print_mhd(mhd_t in)
{
    int hour = in.h;
    enum ampm a = get_ampm_mhd(in);
    assert(in.h < 24);
    if (a == PM && hour > 12)
        hour -= 12;
    printf("%d:%d%s", hour, in.m, get_ampm_mhd(in) == PM ? "pm" : "am");
    printf(", %d", in.d);
}

// without new line
void print_tunit(tunit_t in)
{
    mhd_t tmp;
    tmp = get_mhd(in);
    print_mhd(tmp);
}

void print_table(table_t *t, city_t src)
{
    city_t cur = 0;
    for (int i = 0; i < MAXFLIGHT * MAXDAY; i++)
    {
        printf("%d: ", i);
        cur = t->dsts[i];
        printf("%c -> %c, ", src+'a', cur+'a');
        print_tunit(i);
        printf("\n");
    }
}

void fprint_mhd(FILE *f, mhd_t in)
{
    if (!f)
        return;

    int hour = in.h;
    enum ampm a = get_ampm_mhd(in);
    assert(in.h < 24);
    if (a == PM && hour > 12)
        hour -= 12;
    fprintf(f, "%d:%d%s", hour, in.m, get_ampm_mhd(in) == PM ? "pm" : "am");
    fprintf(f, ", %d", in.d);
}

void fprint_tunit(FILE *f, tunit_t in)
{
    if (!f)
        return;
    mhd_t tmp;
    tmp = get_mhd(in);
    fprint_mhd(f, tmp);
}
#define _CRT_SECURE_NO_WARNINGS

void fprint_table(table_t *t, city_t src)
{
    char buf[512];
    sprintf(buf, "./pathinfo/%c city_", src + 'a');
    strcat(buf, "one_month_table.txt");
    FILE * f = fopen(buf, "w");
    assert(f != NULL);
    city_t cur = 0;
    for (int i = 0; i < MAXFLIGHT * MAXDAY; i++)
    {
        fprintf(f, "%d: ", i);
        cur = t->dsts[i];
        fprintf(f, "%c -> %c, ", src+'a', cur+'a');
        fprint_tunit(f, i);
        fprintf(f, "\n");
    }
    fclose(f);
}

void get_rand_table(table_t *t, city_t src, bool adj[][MAXNODE])
{
    char fname[512] = {0};
    sprintf(fname, "./pathinfo/table_info_city_%c.dat", src+'a');
    FILE * file_table_dat = fopen(fname, "wb");
    assert(file_table_dat!=NULL);

    int dst;
    int dsts[MAXEDGE] = {0};

    int j = 0;
    int tmp;
    for (int i = 0; i < MAXNODE && j < MAXEDGE; i++)
        if (adj[src][i]) {
            dsts[j] = i;
            j++;
        }

    for (int i = 0; i < MAXFLIGHT * MAXDAY; i++)
    {
        srand((unsigned)time(NULL) + 3*src * i * src * i + src + 2*i*i);
        tmp = rand() % MAXEDGE;
        dst = dsts[tmp];
        t->dsts[i] = dst;
    }
    fwrite(t, sizeof(table_t), 1, file_table_dat);
    fprint_table(t, src);
    fclose(file_table_dat);
}

void load_table(table_t *t, city_t src, bool adj[][MAXNODE])
{
    char fname[512] = {0};
    sprintf(fname, "./pathinfo/table_info_city_%c.dat", src+'a');
    FILE * file_table_dat = fopen(fname, "rb");
    assert(file_table_dat!=NULL);
    fread(t, sizeof(table_t), 1, file_table_dat);
    fprint_table(t, src);
    fclose(file_table_dat);
}

int ceil_tunit(tunit_t t)
{
    int ret = t;
    return t > ret ? ret + 1 : ret;
}

int serach_path(table_t *t, city_t dst, tunit_t atime)
{
    int ret;
    int i0 = ceil_tunit(atime);
    for (ret = i0; ret < MAXFLIGHT * MAXDAY; ret++)
        if (t->dsts[ret] == dst)
            return ret;
    return -1;
}

int get_day(tunit_t tunit)
{
    mhd_t tmp = get_mhd(tunit);
    return tmp.d;
}

int get_min(tunit_t tunit)
{
    mhd_t tmp = get_mhd(tunit);
    return tmp.m;
}

int get_hour(tunit_t tunit)
{
    mhd_t tmp = get_mhd(tunit);
    return tmp.h;
}

tunit_t get_tunit(mhd_t in)
{
    return ((in.d-1) * 1440 + in.h * 60 + in.m) / (tunit_t) 5.0;
}
