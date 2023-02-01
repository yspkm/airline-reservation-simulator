#define _CRT_SECURE_NO_WARNINGS
#include "inputgen.h"

char *cultures[] = {
    "american",
    "australian",
    "british",
    "canadian",
};

char *genders[] = {
    "female.names",
    "male.names"};

char *fname_surname = "sur.names";

int inputgen(void)
{
    char buf[BUFSIZE];
    char first_names[BUFSIZE][NAMELEN];
    char sur_names[BUFSIZE][NAMELEN];

    int len = MAX_INPUT;
    int gidx, cidx;
    int first_idx;
    int last_idx;
    int str_len;
    bool is_first;

    int fidx, lidx;

    FILE *f, *fcsv;

    char *cities = "abcdefghijklmnopqrstuvwxyz";
    int src_idx;
    int dst_idx;
    int day;

    srand((unsigned)time(NULL));
    fcsv = fopen(CSVFNAME, "w");
    assert(fcsv != NULL);

    for (int i = 1; i <= len; i++)
    {
        gidx = rand() % (sizeof(genders) / sizeof(genders[0]));
        cidx = rand() % (sizeof(cultures) / sizeof(cultures[0]));

        first_idx = 0;
        last_idx = 0;
        str_len = 0;

        memset(buf, 0x0, BUFSIZE);
        strcpy(buf, "./resources");
        strcat(buf, "/");
        strcat(buf, cultures[cidx]);
        strcat(buf, "/");
        strcat(buf, genders[gidx]);

        is_first = true;
        f = fopen(buf, "r");
        assert(f != NULL);
        for (first_idx = 0; feof(f) == 0 && first_idx < BUFSIZE; first_idx++)
        {
            if (is_first)
            {
                is_first = false;
                first_idx--;
                continue;
            }

            memset(first_names[first_idx], 0x0, NAMELEN);
            fgets(first_names[first_idx], NAMELEN, f);
            str_len = strlen(first_names[first_idx]);
            if (str_len == 0)
                continue;
            first_names[first_idx][str_len - 1] = '\0';
        }
        fclose(f);

        first_idx--;

        memset(buf, 0x0, BUFSIZE);
        strcpy(buf, "./resources");
        strcat(buf, "/");
        strcat(buf, cultures[cidx]);
        strcat(buf, "/");
        strcat(buf, fname_surname);

        is_first = true;

        f = fopen(buf, "r");
        assert(f != NULL);
        for (last_idx = 0; feof(f) == 0 && last_idx < BUFSIZE; last_idx++)
        {
            if (is_first)
            {
                is_first = false;
                last_idx--;
                continue;
            }

            memset(sur_names[last_idx], 0x0, NAMELEN);
            fgets(sur_names[last_idx], NAMELEN, f);
            str_len = strlen(sur_names[last_idx]);
            if (str_len == 0)
                continue;
            sur_names[last_idx][str_len - 1] = '\0';
        }
        fclose(f);
        last_idx--;

        fidx = rand() % (first_idx + 1);
        lidx = rand() % (last_idx + 1);

        src_idx = rand() % 26;
        while (true)
        {
            dst_idx = rand() % 26;
            if (dst_idx != src_idx)
                break;
        }
        day = rand() % 31 + 1;
        fprintf(fcsv, "%s %s,%c,%c,%d,\n", first_names[fidx], sur_names[lidx], cities[src_idx], cities[dst_idx], day);
    }

    fclose(fcsv);

    return 0;
}