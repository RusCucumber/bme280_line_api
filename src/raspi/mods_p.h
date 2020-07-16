#ifndef mods_p_h
#define mods_p_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for bme280 ///////////////////////////////
typedef struct Obsv_tag {
    float temp;
    float press;
    float humd;
} Obsv;

extern Obsv observation;
/////////////////////////////////////////////


// for mqtt /////////////////////////////////
extern char *username;
extern char *pw;
extern char *cafile;
extern char *host;
extern int port;
extern char *id;
extern char *topic;
extern char *message;
/////////////////////////////////////////////


// for read_config /////////////////////////
typedef struct inner_dict_tag {
    char *key;
    char *value;
    struct inner_dict_tag *nord;
} inner_dict;

typedef struct dict_tag {
    char *key;
    inner_dict *value;
    struct dict_tag *nord;
} dict;

extern dict *head;
extern inner_dict *inner_head;

extern char *config_file;
/////////////////////////////////////////////


char *my_strdup(char str[]);

#endif /* mods_p_h */
