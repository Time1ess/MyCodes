// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-06 20:26
// Last modified: 2017-03-06 20:26
// Filename: solution.cpp
// Description:
class Solution {
public:
    map<string, string> mapping;
    string keys="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int bias = 100000007;
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        int idx = mapping.size() + bias;
        string shortUrl = "";
        while(idx)
        {
            shortUrl = keys[idx % 64] + shortUrl;
            idx /= 64;
        }
        mapping[shortUrl] = longUrl;
        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        auto search = mapping.find(shortUrl);
        if(search != mapping.end())
            return search->second;
        return shortUrl;
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
