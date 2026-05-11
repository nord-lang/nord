#!/bin/bash
set -e

REPO="nord-lang/nord"
BINARY="nordvm"

get_latest_release() {
    curl -s "https://api.github.com/repos/${REPO}/releases/latest" |
        grep "browser_download_url" |
        grep "${BINARY}" |
        cut -d '"' -f 4
}

install() {
    URL=$(get_latest_release)
    if [ -z "$URL" ]; then
        echo "No release found. Building from source..."
        git clone https://github.com/${REPO}.git
        cd nord
        make
        sudo cp nordvm /usr/local/bin/
        return
    fi
    
    echo "Installing from release: $URL"
    curl -L "$URL" -o /tmp/${BINARY}
    sudo chmod +x /tmp/${BINARY}
    sudo mv /tmp/${BINARY} /usr/local/bin/
    echo "Installed ${BINARY}"
}

install