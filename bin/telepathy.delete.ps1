if ($null -eq $args[0]) {
    Write-Error "Please specify the path"
    Write-Host " Help -> telepathy.help" -ForegroundColor Green
} else {
    $path = $env:Path + ";"
    $splited_path = ($env:Path -split ";")
    if ($splited_path -notcontains $args[0]) {
        $Env:Path -split ';'
        Write-Warning ("`"" + $args[0] + "`" not founded")
        Write-Host "Please check the environment variables above." -ForegroundColor Green
    } else {
        $deleted_path = $path.Replace(( ";" + $args[0] + ";"), "" )
        [Environment]::SetEnvironmentVariable("Path", $deleted_path, "User")
    }
}
