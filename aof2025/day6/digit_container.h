#ifndef DIGIT_CONTAINER_H
#define DIGIT_CONTAINER_H

#include <string>
#include <vector>

class DigitContainer {
  public: 
    void add_blocks(const std::vector<int>&);
    void add_cols(const std::string&);
    long long grand_sum(const std::vector<std::vector<int>>&) const;
    std::vector<std::vector<int>> convert_cols() const;
    void operations(const std::string&);

    std::vector<std::vector<int>> blocks() const;

  private: 
    void initialize_cols(const int size);
    void shrink_cols();

    std::vector<std::vector<int>> blocks_;
    std::vector<std::vector<char>> cols_;
    std::vector<char> operations_;
};

#endif 
