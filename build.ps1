param([string]$DevkitPro = 'C:\devkitPro', [ValidateSet('fr', 'en')][string]$Language = 'fr')
$ErrorActionPreference = 'Stop'
$bash = Join-Path $DevkitPro 'msys2\usr\bin\bash.exe'
if (!(Test-Path -LiteralPath $bash)) { throw "Shell devkitPro introuvable : $bash" }
$env:ASTRA_CPS2_PROJECT = $PSScriptRoot
$env:ASTRA_CPS2_LANGUAGE = $Language
& $bash -lc 'cd "$(cygpath -u "$ASTRA_CPS2_PROJECT")" && make -j6 UI_LANG="$ASTRA_CPS2_LANGUAGE"'
exit $LASTEXITCODE
