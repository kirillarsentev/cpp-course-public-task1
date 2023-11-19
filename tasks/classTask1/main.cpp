#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class KeyValueDB {
public:
    explicit KeyValueDB(const std::string& filename) : filename_(filename) {}

    bool insert(const std::string& key, const std::string& value) {
        data_[key] = value;
        return true;
    }

    bool remove(const std::string& key) {
        auto it = data_.find(key);
        if (it != data_.end()) {
            data_.erase(it);
            return true;
        }
        return false;
    }

    std::string find(const std::string& key) const {
        auto it = data_.find(key);
        if (it != data_.end()) {
            return "FOUND: " + it->second;
        }
        return "NOT FOUND";
    }

    std::string printKeys() const {
        std::stringstream ss;
        for (const auto& pair : data_) {
            ss << pair.first << "\n";
        }
        return ss.str();
    }

    std::string printValues() const {
        std::stringstream ss;
        for (const auto& pair : data_) {
            ss << pair.second << "\n";
        }
        return ss.str();
    }

    bool dropAll() {
        data_.clear();
        return true;
    }

    bool saveToFile() const {
        std::ofstream file(filename_);
        if (file.is_open()) {
            for (const auto& pair : data_) {
                file << pair.first << "=" << pair.second << "\n";
            }
            file.close();
            return true;
        }
        return false;
    }

    bool loadFromFile() {
        std::ifstream file(filename_);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string key, value;
                if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                    data_[key] = value;
                }
            }
            file.close();
            return true;
        }
        return false;
    }

private:
    std::map<std::string, std::string> data_;
    std::string filename_;
};

class ArgumentsParser {
public:
    explicit ArgumentsParser(int argc, char** argv) : arguments_(argv + 1, argv + argc) {}

    bool processNextCommand(KeyValueDB& db) {
        if (arguments_.empty()) {
            return false;
        }

        std::vector<std::string> commands;
        for (const auto& arg : arguments_) {
            if (arg.back() == end_command_delimiter) {
                commands.push_back(arg.substr(0, arg.size() - 1));
            }
        }

        for (const auto& cmd : commands) {
            std::istringstream iss(cmd);
            std::string operation;
            iss >> operation;
            if (operation == "INSERT") {
                std::string key, value;
                char equalSign;
                iss >> key >> equalSign >> value;
                db.insert(key, value);
            } else if (operation == "DELETE") {
                std::string key;
                iss >> key;
                db.remove(key);
            } else if (operation == "FIND") {
                std::string key;
                iss >> key;
                std::cout << db.find(key) << std::endl;
            } else if (operation == "PRINT") {
                std::string subCommand;
                iss >> subCommand;
                if (subCommand == "KEYS") {
                    std::cout << db.printKeys();
                } else if (subCommand == "VALUES") {
                    std::cout << db.printValues();
                }
            } else if (operation == "DROPALL") {
                db.dropAll();
            }
        }

        for (auto it = arguments_.begin(); it != arguments_.end();) {
            if (it->back() == end_command_delimiter) {
                it = arguments_.erase(it);
            } else {
                ++it;
            }
        }

        return true;
    }

private:
    std::vector<std::string> arguments_;
    constexpr static char end_command_delimiter{'?'};
};
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename> <commands ending with '?>'" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    KeyValueDB db(filename);
    if (!db.loadFromFile()) {
        std::cerr << "Failed to load database file: " << filename << std::endl;
        return 1;
    }

    ArgumentsParser ap(argc - 2, argv + 2);

    while (ap.processNextCommand(db)) {}

    if (!db.saveToFile()) {
        std::cerr << "Failed to save database file: " << filename << std::endl;
        return 1;
    }

    return 0;
}