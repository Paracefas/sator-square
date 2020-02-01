/*
 * Copyright 2020 Google LLC
 *
 * Writted by Emanuel Clur
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

auto generateRandomBounded(size_t lower_bound, size_t upper_bound)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(lower_bound, upper_bound);
    return dist6(rng);
}

template<typename T>
auto vecSum(T const& vec)
{
    return std::accumulate(begin(vec), end(vec), 0);
}

auto getColumnMat(std::vector<std::string> const& mat, size_t column)
{
    std::string r;
    for(auto const& row : mat)
        r += row[column];
    return r;
}

bool areAnagram(std::string str, std::string str2)
{
    std::sort(begin(str), end(str));
    std::sort(begin(str2), end(str2));
    return str == str2;
}

template<typename T>
bool isSatorSquare(T matrix)
{
    for(int i = 0; i < matrix.size(); ++i)
    {
        if(!(vecSum(matrix[i]) == vecSum(*(matrix.end()-(i+1))) && vecSum(getColumnMat(matrix, i)) == vecSum(getColumnMat(matrix, matrix.size()-(i + 1)))))
            return false;
        if(!(areAnagram(matrix[i], *(matrix.end()-(i+1))) && areAnagram(matrix[i], getColumnMat(matrix, i)) && areAnagram(matrix[i], getColumnMat(matrix, matrix.size()-(i + 1)))))
            return false;
    }
    return true;
}

#include<set>

std::set<std::vector<std::string>> mem;

void fillSquare(std::vector<std::string>& sqr, size_t M)
{
    sqr.resize(M);
    for(auto& row : sqr) row.resize(M);

    for(int j = 0; j < M; ++j)
        for(int i = 0; i < M; ++i)
            sqr[j][i] = (char)generateRandomBounded(65, 68);
    if(mem.count(sqr)) fillSquare(sqr, M); 
    mem.insert(sqr);
}

template<typename Mat>
void printMat(Mat const& mat)
{
    for(auto const& row : mat)
        std::cout << row << "\n";
}

int main(int argc, char const** argv)
{
    std::vector<std::string> sqr
    {
        "SATOR",
        "AREPO",
        "TENET",
        "OPERA",
        "ROTAS"
    };

    std::cout << (isSatorSquare(sqr) ? "It's the Sator's Square" : "It's not the Sator's Square") << '\n';

/**
 *  Above we have a little try of obtain the famous Sator's Square
 *  by taking random characters but with a promedium of 390µs it 
 *  takes about 9.6219425e+27 Hours in the worst case...
 * 
 * */
/*
    std::vector<std::string> sqr;

    fillSquare(sqr, 3);
    printMat(sqr);
    
    int i = 1;

    while(!isSatorSquare(sqr))
    {
        Timer t{"Iteration"};
        fillSquare(sqr, 3);
        std::cout << "====================================\n"
                  << "\tIteration N°: " << i ++ << '\n';
        printMat(sqr);
        std::cout << "\n====================================\n";
    }
*/
}