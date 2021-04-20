//
// Created by Richard Spindler on 21.03.21.
//

#include "CountryDatabase.hpp"
#include "config.h"
#include <iostream>
#include <cstring>
#include <exception>

CountryDatabase::CountryDatabase() {
    int status = MMDB_open(GEOLITE2_COUNTRY_DATABASE_FILENAME, MMDB_MODE_MMAP, &mmdb);

    if (MMDB_SUCCESS != status) {
        std::cerr << "Can't open " << GEOLITE2_COUNTRY_DATABASE_FILENAME << " - " << MMDB_strerror(status) << "\n";

        if (MMDB_IO_ERROR == status) {
            std::cerr << "    IO error: " << std::strerror(errno) << "\n";
        }
        throw std::runtime_error("could not open countrydb");
    }
}

std::string CountryDatabase::lookupIsoCode(const std::string &ip) {
    //Test cases: https://lite.ip2location.com/ip-address-ranges-by-country
    /*auto germany = "82.82.55.4";
    auto france = "2.0.0.0";
    auto uk  = "2.20.133.0";*/

    //auto my_ip = germany;
    int gai_error, mmdb_error;
    MMDB_lookup_result_s result =
            MMDB_lookup_string(&mmdb, ip.c_str(), &gai_error, &mmdb_error);
    if (MMDB_SUCCESS != mmdb_error) {
        std::cerr << "\n  Got an error from the maxminddb library: " <<
                  MMDB_strerror(mmdb_error) << "\n";

        throw std::runtime_error("Got an error from the maxminddb library");
    }
    int status;
    if (result.found_entry) {
        MMDB_entry_data_list_s *entry_data_list = NULL;
        status = MMDB_get_entry_data_list(&result.entry, &entry_data_list);
        fprintf(stdout, "\n");
        //MMDB_dump_entry_data_list(stdout, entry_data_list, 2);
        fprintf(stdout, "\n");
        //"country", "iso_code"
        MMDB_entry_data_s entry_data;
        int status =
                MMDB_get_value(&result.entry, &entry_data,
                               "country", "iso_code", NULL);
        if (MMDB_SUCCESS != status) {  }
        if (entry_data.has_data) {
            switch (entry_data.type) {
                case MMDB_DATA_TYPE_UTF8_STRING: {
                    std::string iso_code(entry_data.utf8_string, entry_data.data_size);
                    std::cout << "iso_code: " << iso_code << "\n";
                    return iso_code;

                }
            }
        }

//		return EXIT_SUCCESS;
    }
    return std::string();
}
