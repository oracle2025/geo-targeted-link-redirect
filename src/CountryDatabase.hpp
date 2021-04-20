//
// Created by Richard Spindler on 21.03.21.
//

#pragma once
#include <maxminddb.h>
#include <string>

struct CountryDatabase {
    CountryDatabase();
    std::string lookupIsoCode(const std::string &ip);
    MMDB_s mmdb;

};


