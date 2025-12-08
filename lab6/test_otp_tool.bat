@echo off
cd /d %~dp0
echo ==========================================
echo   Simple One-Time Pad (OTP) Test Script
echo ==========================================

set TOOL=otp_tool.exe
set KEY=key.txt
set PLAIN=plain.txt
set CIPHER=cipher.txt
set DECRYPTED=decrypted.txt

REM Clean up old files
if exist %KEY% del %KEY%
if exist %CIPHER% del %CIPHER%
if exist %DECRYPTED% del %DECRYPTED%

REM 1. Generate Key
echo [1] Generating key...
%TOOL% -generate_key %KEY% 50
if not exist %KEY% (
    echo FAIL: key.txt not created!
    goto END
)
echo PASS: key.txt created successfully.

REM 2. Create a plaintext file
echo [2] Creating plaintext...
echo Hello, this is a simple OTP encryption test. > %PLAIN%
if not exist %PLAIN% (
    echo FAIL: plaintext file not created!
    goto END
)
echo PASS: plaintext created.

REM 3. Encrypt
echo [3] Encrypting...
%TOOL% -encrypt %KEY% %PLAIN% %CIPHER%
if not exist %CIPHER% (
    echo FAIL: cipher file not created!
    goto END
)
echo PASS: ciphertext generated.

REM 4. Decrypt
echo [4] Decrypting...
%TOOL% -decrypt %KEY% %CIPHER% %DECRYPTED%
if not exist %DECRYPTED% (
    echo FAIL: decrypted file not created!
    goto END
)
echo PASS: decrypted file created.

REM 5. Compare plaintext and decrypted text
echo [5] Comparing plaintext and decrypted text...
fc /b %PLAIN% %DECRYPTED% >nul
if %errorlevel%==0 (
    echo PASS: decrypted text matches original.
) else (
    echo FAIL: decrypted text does NOT match original!
    goto END
)

echo ------------------------------------------
echo All tests completed.
echo ------------------------------------------

:END
pause
