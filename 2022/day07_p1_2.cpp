#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <map>

class File {
public:
    File(std::string name, int size) : name(name), size(size) {}

    std::string name;
    int size;
};

class Folder {
public:
    // Folder();
    Folder(std::string name) : name(name) {}

    Folder(std::string name, Folder *parent) : name(name), parent(parent) {}

    Folder *get_parent() { return parent; }

    Folder *get_subfolder(std::string name) {
      for (Folder *f: subfolders) {
        if (f->name == name) {
          return f;
        }
      }
      // std::cout << "Didn't find subfolder: " << name << std::endl;
      std::string except_text = "Didn't find subfolder " + name;
      throw std::invalid_argument(except_text);
      // return nullptr;
    }

    void add_folder(std::string name, Folder *parent) {
      Folder *f = new Folder(name, parent);
      subfolders.insert(f);
    }

    void add_file(std::string name, int size) {
      File *f = new File(name, size);
      files.insert(f);
    }

    std::set<Folder *> get_all_subfolders() { return subfolders; }

    std::set<File *> get_all_files() { return files; }

    std::string get_name() { return name; }
    int get_size() { return total_size; }

    static int calculate_sizes(Folder* pwd, std::map<std::string, int>& sizes) {
      int folder_size = 0;
      for (Folder *folder : pwd->get_all_subfolders()) {
        folder_size += calculate_sizes(folder, sizes);
      }

      for (File *file: pwd->get_all_files()) {
        folder_size += file->size;
      }

      std::cout << pwd->get_name() << ": " << folder_size << std::endl;
      pwd->total_size = folder_size;
      sizes[pwd->name] = folder_size;
      return folder_size;
    }

    static int folders_by_size_limit(Folder* pwd, int limit) {
      int result = 0;
      for (Folder* folder : pwd->get_all_subfolders()) {
        result += folder->folders_by_size_limit(folder, limit);
      }

      if (pwd->total_size <= limit) {
        result += pwd->total_size;
      }
      return result;
    }

private:
    std::string name;
    int total_size;
    Folder *parent;
    std::set<Folder *> subfolders;
    std::set<File *> files;
};

Folder *parse_command(const std::string &line, Folder &root, Folder *pwd) {
  std::stringstream stream(line);
  std::string tmp, cmd, name;
  stream >> tmp >> cmd >> name;
  // std::cout << cmd << " - " << name << std::endl;
  if (cmd == "cd") {
    // std::cout << cmd << " - " << name << std::endl;
    if (name == "/") {
      return &root;
    } else if (name == "..") {
      return pwd->get_parent();
    } else {
      return pwd->get_subfolder(name);
    }
  }

  return pwd;
}

void parse_output(const std::string line, Folder *pwd) {
  std::stringstream stream(line);
  std::string type, name;
  stream >> type >> name;
  if (type == "dir") {
    pwd->add_folder(name, pwd);
  } else {
    int size = std::stoi(type);
    pwd->add_file(name, size);
  }
}

int main() {
  std::ifstream input("input07.txt");
  std::string line;

  Folder root("/");
  Folder *pwd = &root;

  int it = 0;
  if (input.is_open()) {
    while (std::getline(input, line)) {
      if (line.at(0) == '$') {
        // command
        pwd = parse_command(line, root, pwd);
      } else {
        // command output
        parse_output(line, pwd);
      }
      it++;
    }
  }

  //std::cout << Folder::calculate_sizes(&root) << std::endl; // 45349983
  std::map<std::string, int> sizes;
  int root_size = Folder::calculate_sizes(&root, sizes);
  int disk_space = 70000000;
  int required = 30000000;
  int min = required - (disk_space - root_size);
  std::cout << "part1 answer: "
    << Folder::folders_by_size_limit(&root, 100000) << std::endl; // part 1 - 1555642

  int part2 = disk_space;
  for (auto pair : sizes) {
    if (pair.second < part2 && pair.second >= min) {
      part2 = pair.second;
    }
  }

  std::cout << "======= part2 =======" << std::endl;
  std::cout << "min space required: " << min << std::endl;
  std::cout << "part2 answer: " << part2 << std::endl;

  return 0;
}
