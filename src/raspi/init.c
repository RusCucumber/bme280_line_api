#include "mods_p.h"

Obsv observation;

char *username;
char *pw;
char *cafile;
char *host;
int port;
char *id;
char *topic;
char *message;

dict *head;
inner_dict *inner_head;
char *config_file;

void init(void)
{
    observation.temp = 0.0;
    observation.press = 0.0;
    observation.humd = 0.0;
    
    username = NULL;
    pw = NULL;
    cafile = NULL;
    host = NULL;
    port = 0;
    id = NULL;
    topic = NULL;
    message = NULL;
    
    head = NULL;
    inner_head = NULL;
    config_file = my_strdup("config.ini");
}
