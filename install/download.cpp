#include <iostream>
#include <curl/curl.h>

// 回调函数，用于写入下载的数据
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
        return 1;
    }

    CURL *curl;
    FILE *fp;

    // 初始化 libcurl
    curl = curl_easy_init();
    if (curl) {
        // 打开文件，用于保存下载的数据
        fp = fopen("downloaded_file.txt", "wb");
        if (fp == NULL) {
            std::cerr << "Error opening file for writing." << std::endl;
            return 1;
        }

        // 设置要下载的 URL
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        // 设置写入数据的回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        // 设置写入数据的文件指针
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // 执行 HTTP 请求并下载内容
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to download: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }

        // 清理资源
        curl_easy_cleanup(curl);
        fclose(fp);
    } else {
        std::cerr << "Failed to initialize libcurl." << std::endl;
        return 1;
    }

    std::cout << "Download completed successfully." << std::endl;

    return 0;
}
