#include "graph.h"

void Graph::LoadGraphFromFile(std::string path) {
  std::ifstream file(path);
  if (file.is_open()) {
    std::string line;
    std::getline(file, line);
    if (std::sscanf(line.c_str(), "%d", &size_) != 1) {
      throw std::invalid_argument("wrong input");
    }
    matrix_.resize(size_, std::vector<double>(size_));
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        if (!(file >> matrix_[i][j])) {
          throw std::invalid_argument("wrong input");
        }
      }
    }
    file.close();
  } else {
    throw std::invalid_argument("wrong path to file");
  }
}

void Graph::ExportGraphToDot(std::string path) {
  std::string filePath{path + ".dot"};
  std::fstream outfile;
  outfile.open(filePath, std::fstream::out);
  if (!outfile.is_open()) {
    throw std::runtime_error("Unable to write file");
  }
  std::string dotSeparator;
  std::string dotGraphType;
  dotSeparator = " -- ";
  dotGraphType = "graph ";
  outfile << dotGraphType << "dotfile"
          << " {" << std::endl;
  for (int i{0}; i < size_; ++i) {
    for (int j{0}; j < size_; ++j) {
      if (matrix_[i][j] > 0) {
        if (matrix_[i][j] == 1) {
          outfile << i + 1 << dotSeparator << j + 1 << ";" << std::endl;
        } else {
          outfile << i + 1 << dotSeparator << j + 1
                  << " [label=" << matrix_[i][j] << "];" << std::endl;
        }
      }
    }
  }
  outfile << "}";
}
