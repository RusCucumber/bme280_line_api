#include "mods_p.h"

static void dict_free(void)
{
    dict *tmp;
    inner_dict *inner_tmp;
    
    while (head != NULL) {
        tmp = head;
        inner_head = head->value;
        head = tmp->nord;
                
        while (inner_head != NULL) {
            inner_tmp = inner_head;
            inner_head = inner_tmp->nord;
            free(inner_tmp->key);
            free(inner_tmp->value);
            free(inner_tmp);
        }
        
        free(tmp->key);
        free(tmp);
    }
}

void finit(void)
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
    config_file = NULL;
    
    dict_free();
}
