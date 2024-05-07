#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <iostream>

// DECLERATIONS -- SMALL HEADER FILE
int count_neighbors(const std::vector<bool>& matrix, int i, int N);
bool get_new_state(const std::vector<bool>& matrix, int i, int N);
void update(std::vector<bool>& old_state, 
    std::vector<bool> & new_state, 
    int N, int M);
std::vector<bool> initialize(int size, int percentage_of_positives);
std::vector<bool> run_simulation(const std::vector<bool>& init_state,
                                 int N, size_t iterations);
// -------------------------------------------------------
namespace py = pybind11;


py::array_t<bool> py_init(int size, int percentage){
    auto res = py::array_t<bool>(size);
    auto buffer = res.request();
    auto ptr = (bool*) buffer.ptr;
    auto temp = initialize(size, percentage);
    for(int i = 0; i<size; i++){

        ptr[i]=temp[i];
    }
    return res;
}

int py_count_neighbors(py::array_t<bool, py::array::c_style> &matrix, int i, int N){
    auto buffer = matrix.request();
    bool *ptr = (bool*) buffer.ptr;
    std::vector<bool> vec(ptr, ptr+buffer.size);
    return count_neighbors(vec, i, N);
}

bool py_get_new_state(py::array_t<double, py::array::c_style> &array, int i, int N){
    auto buffer = array.request();
    bool* ptr = (bool*) buffer.ptr;
    std::vector<bool> temp(ptr, ptr+buffer.size);
    return get_new_state(temp, i, N);
}


void py_update(py::array_t<bool, py::array::c_style> &input,
                py::array_t<bool, py::array::c_style> &output,
                int N, int M){

    auto buffer_in = input.request();
    auto buffer_out = output.request();
    bool* ptr_in = (bool*) buffer_in.ptr;
    bool* ptr_out = (bool*) buffer_out.ptr;

    std::vector<bool> old_state(ptr_in, ptr_in+buffer_in.size);

    for(size_t i=2; i<N-2; i++){
        for(size_t j=2; j<M; j++)
            ptr_out[i*N+j] = get_new_state(old_state, i*N+j, N);

    }

}

py::array_t<bool> py_run_sim(py::array_t<bool, py::array::c_style> &init_state, int N, int iterations){
    int size=N*N;
    auto buffer = init_state.request();
    auto ptr = (bool*) buffer.ptr;
    std::vector<bool> temp(ptr, ptr+buffer.size);
    std::vector<bool> out = run_simulation(temp, N, iterations);

    auto res = py::array_t<bool>(size);
    auto buffer_res = res.request();
    auto ptr_res = (bool*) buffer_res.ptr;
    for(int i = 0; i<size; i++){
        ptr_res[i]=out[i];
    }

    return res;

}







PYBIND11_MODULE(game, m) {
    m.doc() = "Python binding for source functions"; // Optional module docstring
    m.def("init", &py_init, "Initialize randomly");
    m.def("new_state", &get_new_state, "Check if cell state should change based on neighbors");
    m.def("count_neighbors", &py_count_neighbors, "Counts active cells");
    m.def("py_update", &py_update, "Update matrix state");
    m.def("py_run_sim", &py_run_sim, "RUN BABY RUN");
}
