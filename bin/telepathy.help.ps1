Write-Host "telepathy_v1_0_0_" -ForegroundColor Blue

Write-Host "telepathy.view" -ForegroundColor Green
Write-Host "_>> Obtains a list of environment variable Path"

Write-Host "telepathy.add `"YourPath`"" -ForegroundColor Green
Write-Host "_>> If Path is not given, throw an error"
Write-Host "If the directory indicated in Path does not exist,"
Write-Host " it creates the directory but does not affect the environment variable Path."
Write-Host "If Path is a file directory but a non-existent Path, throws an error"
Write-Host "If Path exists and is a file Path,"
Write-Host " register the parent directory in the environment variable Path."
Write-Host "If Path exists and it is a folder Path,"
Write-Host " register the directory in the environment variable Path."

Write-Host "telepathy.delete `"YourPath`"" -ForegroundColor Green
Write-Host "_>>"
