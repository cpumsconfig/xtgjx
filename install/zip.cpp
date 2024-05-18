#include <iostream>
#include <fstream>
#include <zlib.h>

#define CHUNK_SIZE 16384

bool decompressZipFile(const char* zipFilename) {
    std::ifstream file(zipFilename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening zip file." << std::endl;
        return false;
    }

    z_stream strm;
    unsigned char in[CHUNK_SIZE];
    unsigned char out[CHUNK_SIZE];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    int ret = inflateInit2(&strm, 15 + 32);
    if (ret != Z_OK) {
        std::cerr << "inflateInit failed: " << ret << std::endl;
        return false;
    }

    do {
        file.read(reinterpret_cast<char*>(in), CHUNK_SIZE);
        strm.avail_in = static_cast<uInt>(file.gcount());
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK_SIZE;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            switch (ret) {
                case Z_NEED_DICT:
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    return false;
            }
            unsigned have = CHUNK_SIZE - strm.avail_out;
            std::cout.write(reinterpret_cast<const char*>(out), have);
        } while (strm.avail_out == 0);

    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);

    if (ret != Z_STREAM_END) {
        std::cerr << "Error: inflateEnd returned " << ret << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <zipFilename>" << std::endl;
        return 1;
    }

    const char* zipFilename = argv[1];
    if (!decompressZipFile(zipFilename)) {
        std::cerr << "Failed to decompress zip file." << std::endl;
        return 1;
    }

    std::cout << "Zip file decompressed successfully." << std::endl;

    return 0;
}
