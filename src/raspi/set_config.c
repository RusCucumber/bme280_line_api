#include "mods_p.h"

static inner_dict *get_value(char key[])
{
    dict *now = head;
    while (now != NULL) {
        if (!strcmp(now->key, key)) return now->value;
        now = now->nord;
    }
    return NULL;
}

// 辞書内辞書のキーから、辞書内辞書の値取得処理
static char *get_inner_value(char key[], inner_dict *value)
{
    inner_dict *now = value;
    while (now != NULL) {
        if (!strcmp(now->key, key)) return now->value;
        now = now->nord;
    }
    return NULL;
}

void set_config(void)
{
    username = get_inner_value("User", get_value("AUTH"));
    cafile = get_inner_value("Cafile", get_value("SECURITY"));
    host = get_inner_value("Host", get_value("CONNECT"));
    port = atoi(get_inner_value("Port", get_value("CONNECT")));
    id = (get_inner_value("Id", get_value("INIT")));
    topic = get_inner_value("Topic", get_value("CONNECT"));
    
    char tmp[128];
    sprintf(tmp, "temp:%f,press:%f,humd:%f", observation.temp, observation.press, observation.humd);
    message = my_strdup(tmp);
}
