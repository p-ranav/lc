param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

cmake -G "Visual Studio 16 2019" -A x64 ./
if ($LASTEXITCODE) {
    throw "Cannot configure vizdata for '${config}' build."
}

cmake --build . --config $config  -- /maxcpucount
if ($LASTEXITCODE) {
    throw "Cannot build vizdata using the '${config}' config."
}

ctest -j3
if ($LASTEXITCODE) {
    throw "vizdata's tests are failed for the '${config}' build."
}
