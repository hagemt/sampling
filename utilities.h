#ifndef UTILITIES_H
#define UTILITIES_H

inline int __default_driver(void);
inline void *__random_data(size_t);
void __log_print(int, const char *, const char *, ...);

#define DEFAULT __default_driver()
#define DATA(x) __random_data(x)
#define LOG(LEVEL,TAG,...) __log_print(LEVEL,TAG,__VA_ARGS__)

#ifdef NDEBUG
#define LOG_TAG "composer"
#else /* DEBUG */
#define LOG_TAG __PRETTY_FUNCTION__
#endif /* NDEBUG */

#define LOG_LEVEL_V 0x0000
#define LOG_LEVEL_D 0x0001
#define LOG_LEVEL_I 0x0002
#define LOG_LEVEL_W 0x0004
#define LOG_LEVEL_E 0x0008
#define LOG_LEVEL_F 0xFFFF

#define LOGV(...) LOG(LOG_LEVEL_V,LOG_TAG,__VA_ARGS__)
#define LOGD(...) LOG(LOG_LEVEL_D,LOG_TAG,__VA_ARGS__)
#define LOGI(...) LOG(LOG_LEVEL_I,LOG_TAG,__VA_ARGS__)
#define LOGW(...) LOG(LOG_LEVEL_W,LOG_TAG,__VA_ARGS__)
#define LOGE(...) LOG(LOG_LEVEL_E,LOG_TAG,__VA_ARGS__)
#define LOGF(...) LOG(LOG_LEVEL_F,LOG_TAG,__VA_ARGS__)

#define RANDOM_SOURCE "/dev/urandom"

#endif /* UTILITIES_H */
