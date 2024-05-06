#include <iostream>
#include <stdio.h>
#include <vector>

// void initialize(std::vector<bool>& matrix, int N, int M){
//     for(auto element: matrix){
//         element=false;
//     }
// }

int count_neighbors(const std::vector<bool>& matrix, int i, int N){
    int sum=0;
    int my_row = i/N;
    int my_col = i%N;

    int ul = (my_row-2)*N+my_col-2;
    int cl = (my_row)*N+my_col-2;
    int dl = (my_row+2)*N+my_col-2;

    int um = (my_row-1)*N+my_col;
    int dm = (my_row+2)*N+my_col;

    int ur = (my_row-1)*N+my_col+1;
    int cr = (my_row)*N+my_col+1;
    int dr = (my_row+2)*N+my_col+2;
    
    sum +=matrix[ul];
    sum +=matrix[cl];
    sum +=matrix[dl];
    sum +=matrix[um];
    sum +=matrix[dm];
    sum +=matrix[ur];
    sum +=matrix[cr];
    sum +=matrix[dr];

    return sum;
};


bool get_new_state(const std::vector<bool>& matrix, int i, int N){
    int Q = count_neighbors(matrix, i, N);
    bool am_i_alive = matrix[i];
    bool if_alive = ((Q-3)*(Q-2)==0);
    bool if_not_alive = ((Q-3)==0);

    bool new_state = static_cast<bool>( am_i_alive*if_alive +(1-am_i_alive)*if_not_alive);
    if (new_state!=if_alive){
        std::cout<<"I change"<<std::endl;
    }
    return new_state;
}

void update(std::vector<bool>& old_state, 
    std::vector<bool> & new_state, 
    int N, int M){

    // std::copy(new_state.begin(), new_state.end(), old_state.begin());

    for(int i=0; i<N*M; i++){
        // std::cout<<"ok"<<std::endl;
        // new_state[i] = get_new_state(old_state, i, N);
        new_state[i] = true;
    }
}


// std::vector<bool> make_false(std::vector<bool> & vec, int N){
//     for (size_t i=0; i<N; i++){
//         vec[i]=false;
//     }
//     return vec;
// }

std::vector<bool> make_false(std::vector<bool>& vec, int N) {
    std::fill(vec.begin(), vec.end(), false);
    return vec;
}



// void update_boundaries();




// int main() {
//     const int N = 10;
//     const int M = 10;
//     std::vector<bool> old_state (N*M, false);
//     std::vector<bool> new_state (N*M, false);
//     initialize(old_state, N, M);

    

//     // delete[] matrix;
//     return 0;
// }