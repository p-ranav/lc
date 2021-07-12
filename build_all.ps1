param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

cmake -G "Visual Studio 16 2019" -A x64 ./
if ($LASTEXITCODE) {
    throw "Cannot configure lc for '${config}' build."
}

cmake --build . --config $config  -- /maxcpucount
if ($LASTEXITCODE) {
    throw "Cannot build lc using the '${config}' config."
}

ctest -j3
if ($LASTEXITCODE) {
    throw "lc's tests are failed for the '${config}' build."
}
