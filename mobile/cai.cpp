#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <zip.h>
#include <dirent.h>

// 解压函数和检查 addon.xml 函数同上

// 获取文件夹中的所有文件名
std::vector<std::string> getFilesInFolder(const std::string& folderPath) {
    std::vector<std::string> files;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                files.push_back(ent->d_name);
            }
        }
        closedir(dir);
    }
    return files;
}

// 删除文件夹及其内容
void removeFolder(const std::string& folderPath) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                std::string filePath = folderPath + "/" + ent->d_name;
                remove(filePath.c_str());
            }
        }
        closedir(dir);
    }
    rmdir(folderPath.c_str());
}

int main() {
    int choice;
    bool running = true;
    std::string moduleFolder = "mobile_mokuan";

    while (running) {
        std::cout << "1. 启动模块" << std::endl;
        std::cout << "2. 卸载模块" << std::endl;
        std::cout << "3. 安装模块（zip格式）" << std::endl;
        std::cout << "4. 退出" << std::endl;
        std::cout << "请选择操作：";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // 启动模块
            {
                std::vector<std::string> installedModules;
                std::cout << "已安装的模块包名：" << std::endl;
                // 获取 mobile_mokuan 文件夹中的所有文件夹
                std::vector<std::string> moduleFolders = getFilesInFolder(moduleFolder);
                for (const auto& folder : moduleFolders) {
                    if (folder != "." && folder != "..") {
                        std::cout << folder << std::endl;
                        installedModules.push_back(folder);
                    }
                }

                std::string packageName;
                std::cout << "请输入要启动的模块包名：";
                std::cin >> packageName;

                // 检查用户输入的包名是否存在，如果存在则显示模块信息
                if (std::find(installedModules.begin(), installedModules.end(), packageName) != installedModules.end()) {
                    std::string addonXMLPath = moduleFolder + "/" + packageName + "/addon.xml";
                    if (checkAddonXML(addonXMLPath)) {
                        std::cout << "成功解析 addon.xml 文件" << std::endl;
                    } else {
                        std::cout << "未找到 addon.xml 文件或解析失败" << std::endl;
                    }
                } else {
                    std::cout << "未找到要启动的模块：" << packageName << std::endl;
                }
            }
            break;
            case 2:
                // 卸载模块
            {
                std::vector<std::string> installedModules;
                std::cout << "已安装的模块包名：" << std::endl;
                // 获取 mobile_mokuan 文件夹中的所有文件夹
                std::vector<std::string> moduleFolders = getFilesInFolder(moduleFolder);
                for (const auto& folder : moduleFolders) {
                    if (folder != "." && folder != "..") {
                        std::cout << folder << std::endl;
                        installedModules.push_back(folder);
                    }
                }

                std::string packageName;
                std::cout << "请输入要卸载的模块包名：";
                std::cin >> packageName;

                // 检查用户输入的包名是否存在，如果存在则删除该模块包
                if (std::find(installedModules.begin(), installedModules.end(), packageName) != installedModules.end()) {
                    removeFolder(moduleFolder + "/" + packageName);
                    std::cout << "成功卸载模块：" << packageName << std::endl;
                } else {
                    std::cout << "未找到要卸载的模块：" << packageName << std::endl;
                }
            }
            break;
            case 3:
                // 安装模块
            {
                std::string zipFile;
                std::cout << "请输入要安装的模块的zip文件名：";
                std::cin >> zipFile;

                // 解压模块
                if (unzip(zipFile, moduleFolder)) {
                    // 检查 addon.xml
                    std::string packageName = zipFile.substr(0, zipFile.find(".zip"));
                    std::string addonXMLPath = moduleFolder + "/" + packageName + "/addon.xml";
                    if (!checkAddonXML(addonXMLPath)) {
                        std::cout << "addon.xml 文件不存在或格式错误，安装失败" << std::endl;
                    }
                } else {
                    std::cout << "解压模块失败" << std::endl;
                }
            }
            break;
            case 4:
                // 退出
                running = false;
                break;
            default:
                std::cout << "无效的选项" << std::endl;
                break;
        }
    }

    return 0;
}