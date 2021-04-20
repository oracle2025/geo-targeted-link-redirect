#!/bin/bash -ex
docker run -p 8080:8080 --env PORT=8080 --rm geo-targeted-link-redirect
