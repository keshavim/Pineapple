#!/usr/bin/env bash
set -e

# Go to the vendor directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VENDOR_DIR="${SCRIPT_DIR}/../vendor"

echo "=== Building vendor libraries in ${VENDOR_DIR} ==="
cd "$VENDOR_DIR"

# Run premake5 to generate Makefiles (you can change 'gmake2' to 'ninja' if needed)
if command -v premake5 >/dev/null 2>&1; then
    premake5 gmake
else
    echo "Error: premake5 not found in PATH"
    exit 1
fi

# Build using make
make -j"$(nproc)"
echo "=== Vendor build complete ==="
