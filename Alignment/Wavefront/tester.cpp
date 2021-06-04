//
// Created by lixin on 2021/6/1.
//

#include <iostream>
#include <random>
#include <sstream>
#include <ctime>
#include <fstream>

extern "C"
{
#include <gap_affine/affine_wavefront_align.h>
}


std::string reference(const int& length) {

    std::string alphabet = "ATCG";
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> dis(0, alphabet.length()-1);
    auto dice = std::bind(dis, engine);

    std::stringstream res;

    for(int i  = 0;i < length;i++)
    {
        res << alphabet[dice()];
    }

    return res.str();
}


std::string read_reference(const std::string& refer) {

    std::string alphabet = "ATCG";
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> dis(0, alphabet.length()-1);
    std::uniform_real_distribution<> real_dis(0,1);
    auto dice = std::bind(dis, engine);
    auto coin = std::bind(real_dis,engine);

    int L = refer.length();
    double same_odd = 0.7;

    double mismatch_odd = 0.2;
    double insertion_odd = 0.4;
    double deletion_odd = 0.4;

    std::stringstream res;

    int i = 0;
    while(i < L)
    {
        if(coin() <= same_odd)
        {
            res << refer[i];
        }
        else
        {
            double temp = coin();
            // mismatch
            if(temp <= mismatch_odd)
            {
                for(int j = 0;j < alphabet.length();j++)
                {
                    if( alphabet[j] != refer[i])
                    {
                        res << alphabet[j];
                        break;
                    }
                }
            }
            // insertion
            else if(temp <= mismatch_odd+insertion_odd)
            {
                res << alphabet[dice()];
                res << refer[i];
            }
            // deletion
        }
        i++;
    }

    return res.str();
}

int main() {

    std::ofstream of("WFA_res");
    int repeat = 10;
    for(int i = 10;i < 51;i++)    // reference length from 10 to 50
    {
        std::cout << i << std::endl;
        for(int j = 0;j < repeat;j++)
        {
            std::string refer = reference(i);
            std::string read = read_reference(refer);
            auto start = clock();
            // Allocate MM
            mm_allocator_t* const mm_allocator = mm_allocator_new(BUFFER_SIZE_8M);
            // Set penalties
            affine_penalties_t affine_penalties = {
                    .match = 0,
                    .mismatch = 4,
                    .gap_opening = 6,
                    .gap_extension = 2,
            };

            // Init Affine-WFA
            affine_wavefronts_t* affine_wavefronts = affine_wavefronts_new_complete(
                   refer.length(),read.length(),&affine_penalties,NULL,mm_allocator);
            // Align
            affine_wavefronts_align(
                    affine_wavefronts,refer.c_str(),refer.length(),read.c_str(),read.length());
            // Free
            affine_wavefronts_delete(affine_wavefronts);
            mm_allocator_delete(mm_allocator);
            double time = (clock()*1.0 - start)/(CLOCKS_PER_SEC*1.0);
            of << time << " ";
        }
        of << '\n';
    }
    return 0;
}
