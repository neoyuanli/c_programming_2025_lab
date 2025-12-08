# test_otp.ps1
[CmdletBinding()]
param(
	[Parameter(Position = 0)]
	[string]$ToolName
)

if ( [string]::IsNullOrWhiteSpace($ToolName))
{
	Write-Host "FAIL: The path to the executable file shouldbe provided." -ForegroundColor Red
	Write-Host "Usage: pwsh ./test_otp.ps1 <path_to_otp_tool>"
	exit 1
}

$resolved = Resolve-Path -LiteralPath $ToolName -ErrorAction SilentlyContinue
if (-not $resolved)
{
	Write-Host "FAIL: No executable file found at path: $ToolName" -ForegroundColor Red
	Write-Host "Current working directory: $( Get-Location )"
	exit 1
}
$ToolPath = $resolved.Path

$item = Get-Item -LiteralPath $ToolPath -ErrorAction SilentlyContinue
if (-not $item -or $item -isnot [System.IO.FileInfo])
{
	Write-Host "FAIL: Path is not a file: $ToolPath" -ForegroundColor Red
	exit 1
}

Write-Host "[Test] Using Path: $ToolPath"

$TestDir = Join-Path -Path (Get-Location) -ChildPath "test_temp_files"

function Write-Pass([string]$Message)
{
	Write-Host "PASS: $Message" -ForegroundColor Green
}

$global:Failed = $false
function Write-Fail([string]$Message)
{
	Write-Host "FAIL: $Message" -ForegroundColor Red
	$global:Failed = $true
}


function Cleanup
{
	Write-Host "Cleaning up..."
	if (Test-Path -LiteralPath $TestDir)
	{
		Remove-Item -LiteralPath $TestDir -Recurse -Force -ErrorAction SilentlyContinue
	}
}

function Invoke-Tool([object[]]$Arguments, [bool]$ShouldFail = $false)
{
	& $ToolPath @Arguments *> $null
	$code = $LASTEXITCODE

	if ($ShouldFail)
	{
		if ($code -eq 0)
		{
			Write-Fail "Command '$( $Arguments -join ' ' )'(Expect Fail) but succeed (exit 0)"
			return $false
		}
		return $true
	}
	else
	{
		if ($code -ne 0)
		{
			Write-Fail "Command '$( $Arguments -join ' ' )'(Expect Success) but failed (exit $code)"
			return $false
		}
		return $true
	}
}

function Assert-Files-Different([string]$A, [string]$B)
{
	$h1 = Get-FileHash -Algorithm SHA256 -LiteralPath $A
	$h2 = Get-FileHash -Algorithm SHA256 -LiteralPath $B
	if ($h1.Hash -eq $h2.Hash)
	{
		Write-Fail "Expect Same Content: `n$A`n$B"
		return $false
	}
	return $true
}

function Assert-Files-Equal([string]$A, [string]$B)
{
	$h1 = Get-FileHash -Algorithm SHA256 -LiteralPath $A
	$h2 = Get-FileHash -Algorithm SHA256 -LiteralPath $B
	if ($h1.Hash -ne $h2.Hash)
	{
		Write-Fail "Expect same content: `n$A`n$B"
		return $false
	}
	return $true
}

try
{
	Write-Host "--- OTP Tool Test Runner (PowerShell) ---"

	Write-Host "1. Setting up test directory..."
	if (Test-Path -LiteralPath $TestDir)
	{
		Remove-Item -LiteralPath $TestDir -Recurse -Force
	}
	New-Item -ItemType Directory -Path $TestDir | Out-Null
	Write-Pass "Test directory created."

	if (Invoke-Tool @() -ShouldFail $true)
	{
		Write-Pass "Test 2.1: No arguments"
	}
	else
	{
		Write-Fail "Test 2.1: No arguments should fail"
	}

	if (Invoke-Tool @("-invalid_command") -ShouldFail $true)
	{
		Write-Pass "Test 2.2: Invalid command"
	}
	else
	{
		Write-Fail "Test 2.2: Invalid command should fail"
	}

	if (Invoke-Tool @("-generate_key", "foo.key") -ShouldFail $true)
	{
		Write-Pass "Test 2.3: Missing arguments"
	}
	else
	{
		Write-Fail "Test 2.3: Missing arguments should fail"
	}

	if (Invoke-Tool @("-generate_key", "foo.key", "-10") -ShouldFail $true)
	{
		Write-Pass "Test 2.4: Negative length"
	}
	else
	{
		Write-Fail "Test 2.4: Negative length should fail"
	}    # 3) -generate_key
	Write-Host "3. Testing -generate_key..."
	$KeyFile = Join-Path $TestDir "test.key"
	$KeyLen = 50
	Invoke-Tool @("-generate_key", $KeyFile, $KeyLen) | Out-Null

	if (-not (Test-Path -LiteralPath $KeyFile))
	{
		Write-Fail "Test 3.1: Key file was not created"
	}
	else
	{
		Write-Pass "Test 3.1: File created"
	}

	$FileSize = (Get-Item -LiteralPath $KeyFile).Length
	if ($FileSize -ne $KeyLen)
	{
		Write-Fail "Test 3.2: Key file size is $FileSize, expected $KeyLen"
	}
	else
	{
		Write-Pass "Test 3.2: File size correct"
	}

	Write-Host "4. Testing full roundtrip (encrypt/decrypt)..."
	$PlainFile = Join-Path $TestDir "plain.txt"
	$CipherFile = Join-Path $TestDir "cipher.bin"
	$DecryptedFile = Join-Path $TestDir "decrypted.txt"
	$OriginalText = "Hello, this is the secret message for OTP!"

	Set-Content -LiteralPath $PlainFile -Value $OriginalText -NoNewline
	$PlainLen = (Get-Item -LiteralPath $PlainFile).Length

	$RoundtripKey = Join-Path $TestDir "rt.key"
	Invoke-Tool @("-generate_key", $RoundtripKey, $PlainLen) | Out-Null

	Invoke-Tool @("-encrypt", $RoundtripKey, $PlainFile, $CipherFile) | Out-Null
	if (-not (Test-Path -LiteralPath $CipherFile))
	{
		Write-Fail "Test 4.1: Encrypt did not create cipher file"
	}
	else
	{
		Write-Pass "Test 4.1: Cipher file created"
	}

	if (Assert-Files-Different $PlainFile $CipherFile)
	{
		Write-Pass "Test 4.2: Ciphertext differs from plaintext"
	}
	else
	{
		Write-Fail "Test 4.2: Ciphertext should differ from plaintext"
	}

	Invoke-Tool @("-decrypt", $RoundtripKey, $CipherFile, $DecryptedFile) | Out-Null
	if (-not (Test-Path -LiteralPath $DecryptedFile))
	{
		Write-Fail "Test 4.3: Decrypt did not create decrypted file"
	}
	else
	{
		Write-Pass "Test 4.3: Decrypted file created"
	}

	if (Assert-Files-Equal $PlainFile $DecryptedFile)
	{
		Write-Pass "Test 4.4: Roundtrip successful (files match)"
	} else {
		Write-Fail "Test 4.4: Roundtrip failed (files do not match)"
	}

	Write-Host "5. Testing key length error..."
	$ShortKey = Join-Path $TestDir "short.key"
	Invoke-Tool @("-generate_key", $ShortKey, 10) | Out-Null
	if (Invoke-Tool @("-encrypt", $ShortKey, $PlainFile, (Join-Path $TestDir "fail.bin")) -ShouldFail $true)
	{
		Write-Pass "Test 5.1: Encrypt correctly failed (key too short)"
	}
	else
	{
		Write-Fail "Test 5.1: Encrypt should have failed (key too short)"
	}

	Write-Host ""
	if ($global:Failed)
	{
		Write-Host "--- SOME TESTS FAILED ---" -ForegroundColor Red
		exit 1
	}
	else
	{
		Write-Host "--- ALL TESTS PASSED SUCCESSFULLY ---" -ForegroundColor Green
		exit 0
	}
	Write-Host ""
	exit 0
}
finally
{
	Cleanup
}
