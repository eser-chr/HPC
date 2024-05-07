#include <iostream>
#include <stdio.h>
#include <vector>
#include <random>

std::vector<bool> initialize(int size, int percentage_of_positives){
    std::mt19937 mt_engine;
    std::vector<bool> matrix(size);
    mt_engine.seed(69); // To be modified when in production
    std::uniform_int_distribution<int> distribution(0,100);
    
    for(size_t i =0; i<matrix.size(); i++){
        matrix[i] = (distribution(mt_engine)<percentage_of_positives);
    }
    return matrix;
}

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
    return new_state;
}

void update(std::vector<bool>& old_state, 
    std::vector<bool> & new_state, 
    int N, int M){


    for(size_t i=2; i<N-2; i++){
        for(size_t j=2; j<M-2; j++)
            new_state[i*N+j] = get_new_state(old_state, i*N+j, N);

    }

    // UPDATE GHOSTLAYERS(Maybe reverse the order to have better L1 access)

    for(size_t i =0; i<2; i++){
        for(size_t j=2; j<M-2; j++)
            new_state[i*N+j] = new_state[(N-4+i)*N+j];
    }
    for(size_t i =N-2; i<N; i++){
        for(size_t j=2; j<M-2; j++)
            new_state[i*N+j] = new_state[(4-N+i)*N+j];
    }
    
    for(size_t i=0; i<N; i++){
        for(size_t j=0; j<2; j++)
            new_state[i*N+j] = new_state[i*N+(N-4)+j];
    }

    for(size_t i=0; i<N; i++){
        for(size_t j=N-2; j<N; j++)
            new_state[i*N+j] = new_state[i*N-(N-4)+j];

    }

    // UPDATE STATE
    std::copy(new_state.begin(), new_state.end(), old_state.begin());
}


std::vector<bool> run_simulation(const std::vector<bool>& init_state,
                                 int N, size_t iterations){
    
    std::vector<bool> old_state(init_state);
    std::vector<bool> new_state(init_state);
    for(size_t iter=0; iter<iterations; iter++){
        update(old_state, new_state, N, N);
    }
    return new_state;
}



