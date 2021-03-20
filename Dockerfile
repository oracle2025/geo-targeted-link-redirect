# The new base image to contain runtime dependencies
# source: https://www.jmoisio.eu/en/blog/2020/06/01/building-cpp-containers-using-docker-and-cmake/

FROM debian:buster AS base

RUN set -ex;         \
    apt-get update;  \
    apt-get install -y procps

# The first stage will install build dependencies on top of the
# runtime dependencies, and then compile

FROM base AS builder

RUN set -ex;                                                                      \
    apt-get install -y g++ curl cmake git;                                        \
    mkdir -p /usr/src;                                                            \
    mkdir -p /usr/local/share


COPY . /usr/src/geo-targeted-link-redirect

RUN set -ex;              \
    cd /usr/src/geo-targeted-link-redirect;  \
    cp share/GeoLite2-Country.mmdb /usr/local/share/GeoLite2-Country.mmdb;  \
    cmake -DCMAKE_BUILD_TYPE=Release -DGEOLITE2_COUNTRY_DATABASE_FILENAME=/usr/local/share/GeoLite2-Country.mmdb .; make; make install

# The second stage will already contain all dependencies, just copy
# the compiled executables

FROM base AS runtime

COPY --from=builder /usr/local/bin /usr/local/bin
COPY --from=builder /usr/local/share /usr/local/share

EXPOSE 8080/tcp

ENTRYPOINT ["server"]
