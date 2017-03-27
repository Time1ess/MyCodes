// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-27 21:50
// Last modified: 2017-03-27 21:50
// Filename: solution.cpp
// Description:
class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        int ra,va,rb,vb, pp, pi, rans, vans;
        pp = a.find('+');
        pi = a.find('i');
        ra = stoi(a.substr(0, pp));
        va = stoi(a.substr(pp+1, pi-pp-1));
        pp = b.find('+');
        pi = b.find('i');
        rb = stoi(b.substr(0, pp));
        vb = stoi(b.substr(pp+1, pi-pp-1));
        rans = ra * rb - va * vb;
        vans = ra * vb + rb * va;
        return to_string(rans) + "+" + to_string(vans) + "i";
    }
};
