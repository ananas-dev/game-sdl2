#!/usr/bin/env bash
set -euo pipefail

cdProject() {
    PARENT_PATH=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
    cd "$PARENT_PATH/.."
}

Build() {
    mkdir build && cd build
    /bin/cmake ..
    make
}

cdProject
Build
