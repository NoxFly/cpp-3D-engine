#include "utils.hpp"

#include <random>
#include <algorithm>
#include <sstream>

using namespace std;


bool endsWith(string_view str, string_view suffix) {
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

bool startsWith(string_view str, string_view prefix) {
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

std::string basename(std::string path) {
    return path.substr(path.find_last_of("/\\") + 1);
}

std::string dirname(std::string path) {
    return path.substr(0, path.find_last_of("/\\") + 1);
}

std::string pathWithNoExt(std::string path) {
    return path.substr(0, path.find_last_of("."));
}

std::string repeat(char c, unsigned int n) {
    std::string s = "";

    for (unsigned int i = 0; i < n; i++) {
        s += c;
    }

    return s;
}

std::string repeat(std::string c, unsigned int n) {
    std::string s = "";

    for (unsigned int i = 0; i < n; i++) {
        s += c;
    }

    return s;
}

bool isInteger(const string& str) {
    for(char const &c : str) {
        if(isdigit(c) == 0)
            return false;
    }

    return true;
}

bool isFloat(const string& str) {
    std::istringstream iss(str);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail(); 
}

string replace(const string& str, const string& find, const string& replace) {
    string result;
    size_t find_len = find.size();
    size_t pos,from = 0;

    while(string::npos != (pos = str.find(find, from))) {
        result.append(str, from, pos-from);
        result.append(replace);
        from = pos + find_len;
    }

    result.append(str, from, string::npos);
    
    return result;
}

std::string ltrim(const std::string& str) {
    size_t start = str.find_first_not_of(" \n\r\t\f\v");
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string rtrim(const std::string& str) {
    size_t end = str.find_last_not_of(" \n\r\t\f\v");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string trim(const std::string& str) {
    return rtrim(ltrim(str));
}

vector<string> split(string sequence, string separator) {
    size_t pos = 0;
    vector<string> splitted = {};

    while((pos = sequence.find(separator)) != string::npos) {
        splitted.push_back(sequence.substr(0, pos));
        sequence.erase(0, pos + separator.length());
    }

    if(sequence.size() > 0)
        splitted.push_back(sequence);

    return splitted;
}

Color getColorFromString(string str) {
    Color color = { 0, 0, 0 };

    if(str != "") {
        std::vector<std::string> vColor = split(str, ",");

        if(vColor.size() == 3 || vColor.size() == 4) {
            float arr[] = { 0.f, 0.f, 0.f, 255.f };

            for(int i=0; i < (int)vColor.size(); i++) {
                string c = vColor[i];

                if(isInteger(c))
                    arr[i] = stoi(c) / 255.f;
                else
                    return color;
            }

            color.r = arr[0];
            color.g = arr[1];
            color.b = arr[2];
            color.a = arr[3];
        }
    }

    return color;
}


const std::string lut[] = {
    "00","01","02","03","04","05","06","07","08","09",
    "0a","0b","0c","0d","0e","0f","10","11","12","13",
    "14","15","16","17","18","19","1a","1b","1c","1d",
    "1e","1f","20","21","22","23","24","25","26","27",
    "28","29","2a","2b","2c","2d","2e","2f","30","31",
    "32","33","34","35","36","37","38","39","3a","3b",
    "3c","3d","3e","3f","40","41","42","43","44","45",
    "46","47","48","49","4a","4b","4c","4d","4e","4f",
    "50","51","52","53","54","55","56","57","58","59",
    "5a","5b","5c","5d","5e","5f","60","61","62","63",
    "64","65","66","67","68","69","6a","6b","6c","6d",
    "6e","6f","70","71","72","73","74","75","76","77",
    "78","79","7a","7b","7c","7d","7e","7f","80","81",
    "82","83","84","85","86","87","88","89","8a","8b",
    "8c","8d","8e","8f","90","91","92","93","94","95",
    "96","97","98","99","9a","9b","9c","9d","9e","9f",
    "a0","a1","a2","a3","a4","a5","a6","a7","a8","a9",
    "aa","ab","ac","ad","ae","af","b0","b1","b2","b3",
    "b4","b5","b6","b7","b8","b9","ba","bb","bc","bd",
    "be","bf","c0","c1","c2","c3","c4","c5","c6","c7",
    "c8","c9","ca","cb","cc","cd","ce","cf","d0","d1",
    "d2","d3","d4","d5","d6","d7","d8","d9","da","db",
    "dc","dd","de","df","e0","e1","e2","e3","e4","e5",
    "e6","e7","e8","e9","ea","eb","ec","ed","ee","ef",
    "f0","f1","f2","f3","f4","f5","f6","f7","f8","f9",
    "fa","fb","fc","fd","fe","ff"
};

// TODO: fix this
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

std::string generateUUID() {
    const int d0 = (int)(dis(gen) * 0xffffffff) | 0;
    const int d1 = (int)(dis(gen) * 0xffffffff) | 0;
    const int d2 = (int)(dis(gen) * 0xffffffff) | 0;
    const int d3 = (int)(dis(gen) * 0xffffffff) | 0;

    const std::string uuid = lut[d0 & 0xff] +
        lut[d0 >> 8 & 0xff] +
        lut[d0 >> 16 & 0xff] +
        lut[d0 >> 24 & 0xff] + '-' +
        lut[d1 & 0xff] +
        lut[d1 >> 8 & 0xff] + '-' +
        lut[(d1 >> 16 & 0x0f) | 0x40] +
        lut[d1 >> 24 & 0xff] + '-' +
        lut[(d2 & 0x3f) | 0x80] +
        lut[d2 >> 8 & 0xff] + '-' +
        lut[d2 >> 16 & 0xff] +
        lut[d2 >> 24 & 0xff] +
        lut[d3 & 0xff] +
        lut[d3 >> 8 & 0xff] +
        lut[d3 >> 16 & 0xff] +
        lut[d3 >> 24 & 0xff];

    return uuid;
}

const std::string vecToString(const glm::vec2& v) {
    return std::to_string(v.x) + ", " + std::to_string(v.y);
}

const std::string vecToString(const glm::vec3& v) {
    return std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z);
}