#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = boost::filesystem;

// 获取 Homebrew 安装路径下的存储文件路径
fs::path get_storage_file() {
    const char* storage_dir_env = getenv("GREET_STORAGE");
    if (!storage_dir_env) {
        std::cerr << "Error: GREET_STORAGE environment variable is not set!" << std::endl;
        exit(1);
    }
    fs::path storage_dir = fs::path(storage_dir_env);
    return storage_dir / "greet.txt";
}

// 读取问候语
std::string read_greeting() {
    fs::path storage_file = get_storage_file();
    if (fs::exists(storage_file)) {
        std::ifstream file(storage_file.string());
        std::string greeting;
        std::getline(file, greeting);
        return greeting.empty() ? "Hello, World!" : greeting;
    }
    return "Hello, World!";
}

// 保存问候语
void save_greeting(const std::string& greeting) {
    fs::path storage_file = get_storage_file();
    std::ofstream file(storage_file.string());
    file << greeting;
}

// 主函数
int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command = argv[1];
        if (command == "change" && argc > 2) {
            std::string new_greeting = argv[2];
            save_greeting(new_greeting);
            std::cout << "Greeting changed to: " << new_greeting << std::endl;
        } else {
            std::cerr << "Usage: greet change <new greeting>" << std::endl;
        }
    } else {
        std::cout << read_greeting() << std::endl;
    }
    return 0;
}
