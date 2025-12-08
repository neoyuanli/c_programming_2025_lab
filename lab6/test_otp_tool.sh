#!/bin/bash

# Ensure script runs in its own directory
cd "$(dirname "$0")"

echo "=========================================="
echo "  Simple One-Time Pad (OTP) Test Script"
echo "=========================================="

TOOL="./otp_tool.exe"
KEY="key.txt"
PLAIN="plain.txt"
CIPHER="cipher.txt"
DECRYPTED="decrypted.txt"

# Clean up old files
rm -f "$KEY" "$CIPHER" "$DECRYPTED"

# 1. Generate Key
echo "[1] Generating key..."
$TOOL -generate_key "$KEY" 50
if [ ! -f "$KEY" ]; then
    echo "FAIL: key.txt not created!"
    exit 1
fi
echo "PASS: key.txt created successfully."

# 2. Create plaintext file
echo "[2] Creating plaintext..."
echo "Hello, this is a simple OTP encryption test." > "$PLAIN"
if [ ! -f "$PLAIN" ]; then
    echo "FAIL: plaintext file not created!"
    exit 1
fi
echo "PASS: plaintext created."

# 3. Encrypt
echo "[3] Encrypting..."
$TOOL -encrypt "$KEY" "$PLAIN" "$CIPHER"
if [ ! -f "$CIPHER" ]; then
    echo "FAIL: cipher file not created!"
    exit 1
fi
echo "PASS: ciphertext generated."

# 4. Decrypt
echo "[4] Decrypting..."
$TOOL -decrypt "$KEY" "$CIPHER" "$DECRYPTED"
if [ ! -f "$DECRYPTED" ]; then
    echo "FAIL: decrypted file not created!"
    exit 1
fi
echo "PASS: decrypted file created."

# 5. Compare plaintext and decrypted text
echo "[5] Comparing plaintext and decrypted text..."

if cmp -s "$PLAIN" "$DECRYPTED"; then
    echo "PASS: decrypted text matches original."
else
    echo "FAIL: decrypted text does NOT match original!"
    exit 1
fi

echo "------------------------------------------"
echo "All tests completed."
echo "------------------------------------------"
