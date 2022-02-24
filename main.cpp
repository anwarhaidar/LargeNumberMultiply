
/**
 * Coursera: Divide and Conquer, Sorting and Searching, and Randomized Algorithm by Stanford University
 * Implementing multiplication for very large numbers using traditional multiplication approach
 * (iterative) instead of Karatsuba algorithm (recursive)
 *
 * Platform: CLion 2021.3.3 by JetBrains, macOS Monterey 12.2.1
 *
 * @author Anwar S Haidar
 * @version Beta 2/24/2022
 * @contact anwar.haidar@gmail.com
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int make_same_size(string & s_1, string & s_2) {
    int l_1 = (int) s_1.size();
    int l_2 = (int) s_2.size();

    if (l_1 == l_2) return l_1;

    int diff = abs(l_1 - l_2);

    if (l_1 > l_2)
        for (int i=0; i < diff; i++)
            s_2.insert(0, 1,'0'); // overloaded "char insert" takes 3 param
    else
        for (int i=0; i < diff; i++)
            s_2.insert(0, 1,'0');

    return (int) s_1.size();
}

string stringify_vector(vector<int> const& v) {
    string s;

    for (auto c : v)
        s.push_back(char('0' +  c) );

    int i = 0;
    while (s[i] == '0') i++; // loop to offset leading zeros

    return s.substr(i, s.length());
}

void set_vector_to_zero(vector<int> & v){

    for (auto & c : v)
        c = 0;
}

bool is_string_number(string & s) {

    if (any_of(s.begin(),s.end(),[] (char c) { return !isdigit(c); }))
        return false;

    return true;
}

int main(int argc, char** argv) {
    string str_num_1, str_num_2;

    if (argc == 3) {
        str_num_1 = argv[1];
        str_num_2 = argv[2];
    } else {
        str_num_1 = "3141592653589793238462643383279502884197169399375105820974944592";
        str_num_2 = "2718281828459045235360287471352662497757247093699959574966967627";
    }

    if (!is_string_number(str_num_1) || !is_string_number(str_num_2)) {
        cout << "Error in string -- not a number";
        return -1;
    }

    int l = make_same_size(str_num_1, str_num_2);
    int value_1, value_2, product, remainder, index = 0;
    vector<int> v(l + 1);               // temporary container to hold intermediate results
    vector<int> result((2 * l) + 1);    // container holding final result
    string s = str_num_2;                  // copy string to keep entry intact

    while (!s.empty()) {
        value_2 = stoi(string(1, s.back()));
        remainder = 0;
        set_vector_to_zero(v);
        int j = (2 * l);
        for (int i = l - 1; i >= 0; i--) {
            value_1 = stoi(string(1, str_num_1[i]));
            product = result[j - index] + (value_1 * value_2) + remainder;
            result[j - index] = (product > 9 ? product % 10 : product);
            remainder = product / 10;
            j--;
        }
        result[j - index] = remainder;
        s.pop_back();
        index++;
    }

    result[0] = remainder;

    cout << endl << stringify_vector(result) << endl;

    return 0;
}
