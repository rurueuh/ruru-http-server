/*
** EPITECH PROJECT, 2024
** codecrafters-http-server-cpp
** File description:
** Http
*/

#pragma once

#include <bits/stdc++.h>

class Http {
    public:

        static std::string getPath(std::string request) {
            std::string path = request.substr(4, request.find("HTTP") - 5);
            return path;
        }
    protected:
    private:
};
