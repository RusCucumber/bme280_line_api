#include "mods_p.h"

#define MAX (128)

static char *create_key(char readline[])
{
    char *key;
    int n = (int)strlen(readline);
    key = (char *)malloc(sizeof(char) * (n - 1));
    int i = 0;
    int j = 0;
    for (i = 0; i < n; i++) {
        if (readline[i] == '[') continue;
        if (readline[i] == ']') break;
        key[j] = readline[i];
        j++;
    }
    key[j] = '\0';
    return key;
}

static void my_split_one(char *array[], char str[], char sep)
{
    if (array == NULL || str == NULL) {
        perror("1st argument or 2nd argument must not be NULL\n");
    }
    
    int n = (int)strlen(str);
    int i = 0;
    int j = 0;
    char first_str[MAX];
    char second_str[MAX];
    int sep_flag = 0;
    
    for (i = 0; i < n; i++) {
        if (str[i] == sep) {
            sep_flag = 1;
            first_str[i] = '\0';
            continue;
        }
        if (!sep_flag) {
            first_str[i] = str[i];
        } else {
            second_str[j] = str[i];
            j++;
        }
    }
    second_str[j] = '\0';
    
    array[0] = my_strdup(first_str);
    array[1] = my_strdup(second_str);
}

static dict *create_dict(char key[])
{
    dict *new_dict;
    new_dict = (dict *)malloc(sizeof(dict));
    
    new_dict->key = my_strdup(key);
    new_dict->value = NULL;
    new_dict->nord = NULL;
    
    return new_dict;
}

static inner_dict *create_inner_dict(char inner_key[], char inner_value[])
{
    inner_dict *new_inner_dict;
    new_inner_dict = (inner_dict *)malloc(sizeof(inner_dict));
    
    new_inner_dict->key = my_strdup(inner_key);
    new_inner_dict->value = my_strdup(inner_value);
    new_inner_dict->nord = NULL;
    
    return new_inner_dict;
}

void read_config(void)
{
    FILE *f;
    char readline[MAX];
    char *cheker;
    int value_flag = 0;
    
    dict *now = NULL;
    inner_dict *inner_now = NULL;

    f = fopen(config_file, "r");
    if (f == NULL) {
        perror("Faild to read config file\n");
        exit(1);
    }
    
    while (1) {
        cheker = fgets(readline, MAX, f);
        if (cheker == NULL) break;
        if (readline[0] == '\n') continue;
        int n = (int)strlen(readline);
        if (readline[n - 1] == '\n') readline[n - 1] = '\0';
        n--;
        
        if (readline[0] == '[' && readline[n - 1] == ']') {
            char *key = create_key(readline);
            
            if (value_flag) {
                inner_head = NULL;
                inner_now = NULL;
            }
            
            if (head == NULL) {
                head = create_dict(key);
                now = head;
            } else {
                dict *tmp = create_dict(key);
                now->nord = tmp;
                now = tmp;
            }
            
        } else {
            value_flag = 1;
            char *tmp_array[2];
            my_split_one(tmp_array, readline, '=');
            
            if (inner_head == NULL) {
                inner_head = create_inner_dict(tmp_array[0], tmp_array[1]);
                now->value = inner_head;
                inner_now = inner_head;
            } else {
                inner_dict *tmp = create_inner_dict(tmp_array[0], tmp_array[1]);
                inner_now->nord = tmp;
                inner_now = tmp;
            }
        }
    }

    fclose(f);
}
