#ifndef KHTTPD_HTTP_SERVER_H
#define KHTTPD_HTTP_SERVER_H

#include <net/sock.h>
//#include <unistd.h>

#define RECV_BUFFER_SIZE 4096
extern mempool_t *http_buf_pool;
extern struct workqueue_struct *khttpd_wq;  // workqueue

struct http_server_param {
    struct socket *listen_socket;
};

extern int http_server_daemon(void *arg);

static inline void *http_buf_alloc(gfp_t gfp_mask, void *pool_data)
{
    return kzalloc(RECV_BUFFER_SIZE, gfp_mask);
}

static inline void http_buf_free(void *element, void *pool_data)
{
    kfree(element);
}

// 伺服器的管理資訊
struct httpd_service {
    bool is_stopped;        // 是否收到中止訊號
    char *dir_path;         // 伺服器根目錄
    struct list_head head;  // 串列首節點
};
extern struct httpd_service daemon_list;  // 伺服器的管理資料

#endif
