#include "input.h"

bool is_right_input(input_t *in)
{
    return 1 <= in->day && in->day <= 31 && isalpha(in->dst) &&
           isalpha(in->src) && strlen(in->name) > 0;
}

void delete_space_for_search(char s[])
{
    char *str = (char *)malloc(sizeof(char) * MAX_LINE);
    int i, k = 0;
    for (i = 0; i < strlen(s); i++)
        if (isalnum(s[i]) || s[i] == ',')
            str[k++] = s[i];

    str[k] = '\0';
    strcpy(s, str);
    free(str);
}
#define _CRT_SECURE_NO_WARNINGS

void delete_space(char s[])
{
    char *str = (char *)malloc(sizeof(char) * MAX_LINE);
    int i, k = 0;
    bool first_middle_space = true;
    bool after_first_alpha = false;
    bool after_first_comma = false;
    for (i = 0; i < strlen(s); i++)
    {
        if (!after_first_comma)
        {
            if (s[i] == ',')
                after_first_comma = true;
            if (s[i] == ' ')
                if (after_first_alpha && first_middle_space)
                {
                    first_middle_space = false;
                    str[k++] = s[i];
                }
            if (isalpha(s[i]) && !after_first_alpha)
                after_first_alpha = true;
        }
        if (isalnum(s[i]) || s[i] == ',')
            str[k++] = s[i];
    }

    str[k] = '\0';
    strcpy(s, str);
    free(str);
}

void getfield(char *line, struct data *d, int end_idx)
{
    delete_space(line);
    int idx = 0;
    char *token = strtok(line, ",");
    do
    {
        strcpy(d->s[idx++], token);
    } while (idx != end_idx && (token = strtok(NULL, ",")));
}
#define _CRT_SECURE_NO_WARNINGS

void get_test_inputs(input_t ds[MAX_INPUT], int len)
{
    FILE *stream = fopen("input.csv", "r");
    char line[MAX_LINE];
    int i = 0;
    struct data d;
    char src, dst;
    int day;

    while (fgets(line, MAX_LINE, stream))
    {
        if (i >= len)
            break;
        delete_space(line);
        getfield(line, &d, MAX_DATA);
        strcpy(ds[i].name, d.s[0]);
        src = d.s[1][0];
        dst = d.s[2][0];
        day = atoi(d.s[3]);
        ds[i].day = day;
        ds[i].dst = dst;
        ds[i].src = src;
        i++;
        memset(line, 0x0, sizeof(line));
    }
}

void get_input_for_search(input_t *in)
{
    char buf[512];
    struct data d;
RETRY:
    // printf("input(name,src,dst,day): ");
    scanf("%[^\n]s", buf);
    getchar();
    delete_space_for_search(buf);
    getfield(buf, &d, 3);
    in->src = d.s[0][0];
    in->dst = d.s[1][0];
    in->day = atoi(d.s[2]);
    if (!(isalpha(in->src) && isalpha(in->dst) && 1 <= in->day && in->day <= 31))
    {
        printf("wrong input\n");
        // free(in->name);
        goto RETRY;
    }
}

void get_input(input_t *in)
{
    char buf[512];
    struct data d;
RETRY:
    // printf("input(name,src,dst,day): ");
    scanf("%[^\n]s", buf);
    getchar();
    delete_space(buf);
    getfield(buf, &d, MAX_DATA);
    // in->name = strdup(d.s[0]);
    strcpy(in->name, d.s[0]);
    in->src = d.s[1][0];
    in->dst = d.s[2][0];
    in->day = atoi(d.s[3]);
    if (!is_right_input(in))
    {
        printf("wrong input\n");
        // free(in->name);
        goto RETRY;
    }
}

void print_input(input_t *in)
{
    printf("input(name,src,dst,day): ");
    printf("%s, %c, %c, %d\n", in->name, in->src, in->dst, in->day);
}

void get_input_for_search_schedule_table_entry(input_t *in)
{
    char buf[512];
    struct data d;
RETRY:
    // printf("input(name,src,dst,day): ");
    scanf("%[^\n]s", buf);
    getchar();
    delete_space(buf);
    getfield(buf, &d, 4);
    // in->name = strdup(d.s[0]);
    in->src = d.s[0][0];
    in->day = atoi(d.s[1]);
    in->hour = atoi(d.s[2]);
    in->min = atoi(d.s[3]);
    if (!(isalpha(in->src) && (1 <= in->day && in->day <= 31) && (0 <= in->hour && in->hour <= 23) && (0 <= in->min && in->min <= 59)))
    {
        printf("wrong input\n");
        // free(in->name);
        goto RETRY;
    }
}

void get_input_for_search_location_of_city(input_t *in)
{
    char buf[512];
    struct data d;
RETRY:
    // printf("input(name,src,dst,day): ");
    scanf("%[^\n]s", buf);
    getchar();
    delete_space(buf);
    getfield(buf, &d, 1);
    // in->name = strdup(d.s[0]);
    in->src = d.s[0][0];
    if (!(isalpha(in->src)))
    {
        printf("wrong input\n");
        // free(in->name);
        goto RETRY;
    }
}

void get_input_for_search_distance(input_t *in)
{
    char buf[512];
    struct data d;
RETRY:
    scanf("%[^\n]s", buf);
    getchar();
    delete_space(buf);
    getfield(buf, &d, 2);
    // in->name = strdup(d.s[0]);
    in->src = d.s[0][0];
    in->dst = d.s[1][0];
    if (!(isalpha(in->src) && isalpha(in->dst)))
    {
        printf("wrong input\n");
        // free(in->name);
        goto RETRY;
    }
}