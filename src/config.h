#ifndef CONFIG
#define CONFIG

struct config {
    short window_size;
};

struct config read_config(char *file_path);

#endif // CONFIG
