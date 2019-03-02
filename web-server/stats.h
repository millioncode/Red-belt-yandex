#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

class Stats {
    public:
        Stats(): method_  {
                {"GET", 0},
                {"PUT", 0},
                {"POST", 0},
                {"DELETE", 0},
                {"UNKNOWN", 0},
            },
                 uri_ {
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0}
}
        {}
        void AddMethod(string_view method) {
            while (1) {
                size_t space = method.find(' ');
                if (space == method.npos) {
                    break;
                }
                else {
                    auto word = method.substr(0, space);
                    auto it = method_.lower_bound(word);
                    if ( (*it).first == word  ){
                        method_.at(word)++;
                    }
                    else {
                        if (word!="") {
                            method_.at("UNKNOWN")++;
                        }
                    }
                    method.remove_prefix(space+1);
                }
            }
        }
        void AddUri(string_view uri) {
            //cout << uri << endl;
            while (1) {
                size_t space = uri.find(' ');
                if (space == uri.npos) {
                    break;
                }
                else {
                    auto word = uri.substr(0, space);
                    auto it = uri_.lower_bound(word);
                    if ( (*it).first == word  ){
                        uri_.at(word)++;
                    }
                    else {
                        if (word!="") {
                            uri_.at("unknown")++;

                        }
                    }
                    uri.remove_prefix(space+1);
                    //cout << uri << endl;
                }
            }
        }
        const map<string_view, int>& GetMethodStats() const {
            return method_;
        }
        const map<string_view, int>& GetUriStats() const {
            return uri_;
        }

    private:
        map<string_view, int> method_;
        map<string_view, int> uri_;

};

HttpRequest ParseRequest(string_view line) {
    HttpRequest result;
    static string methods;
    methods.clear();
    static string uri;
    uri.clear();
    while (1) {
        size_t space = line.find(' ');
        if (space==line.npos) {
            methods += line.substr(0, space);
            methods += " ";
            break;
        }
        else {
            //result.method = line.substr(0, space);
            methods += line.substr(0, space);
            methods += " ";
            line.remove_prefix(space+1);
        }
        space = line.find(' ');
        if (space==line.npos) {
            uri += line.substr(0, space);
            uri += " ";
            break;
        }
        else {
            //result.uri = line.substr(0, space);
            uri += line.substr(0, space);
            uri += " ";
            line.remove_prefix(space+1);
        }
        space = line.find(' ');
        if (space==line.npos) {
            break;
        }
        else {
            result.protocol = line.substr(0, space);
            line.remove_prefix(space+1);
        }
    }
    result = {methods, uri, ""};
    return result;
}
