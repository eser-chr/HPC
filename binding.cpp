#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include "source.h" // Assuming your source.cpp functions are declared here

// void initialize(std::vector<bool>& matrix, int N, int M);
int count_neighbors(const std::vector<bool>& matrix, int i, int N);
bool get_new_state(const std::vector<bool>& matrix, int i, int N);
void update(std::vector<bool>& old_state, 
    std::vector<bool> & new_state, 
    int N, int M);
void make_false(std::vector<bool> & vec, int N);

namespace py = pybind11;

PYBIND11_MODULE(game, m) {
    m.doc() = "Python binding for source functions"; // Optional module docstring

    m.def("should_cell_change", &get_new_state, "Check if cell state should change based on neighbors");
    m.def("count_neighbors", &count_neighbors, "Counts active cells");
    m.def("update", &update, "Update matrix state");
    m.def("falsify", &make_false, "falsify elements in boolean list");
}
