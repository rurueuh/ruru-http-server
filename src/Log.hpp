/*
** EPITECH PROJECT, 2024
** codecrafters-http-server-cpp
** File description:
** Log
*/

#pragma once

#include <bits/stdc++.h>

constexpr auto LOG_FILE = "../www/log.txt";

class Log {
    public:

    static void save(std::string log) {
        std::ofstream file;
        file.open(LOG_FILE, std::ios::app);
        file << log << std::endl;
        file.close();
    }

    static void save(std::stringstream log) {
        std::ofstream file;
        file.open(LOG_FILE, std::ios::app);
        file << log.str() << std::endl;
        file.close();
    }

    protected:
    private:
};
