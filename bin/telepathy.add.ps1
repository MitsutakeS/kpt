<# TelePathy.add "YourPath" #>
<# Add to environment variables #>
$item = Get-Item -Path $path
if ($Args[0] -eq $null) {
    throw "Please specify the path"
} elseif (-not (Test-Path -Path $Args[0])) { <# Pathが存在しない #>
    if ($item.PSIsContainer) {
        New-Item -Path $Args[0] -ItemType Directory
        Write-Warning ("存在しないディレクトリ: " + $Args[0] + " <-作成しました")
        Write-Host "環境変数Pathに変更はありません" -ForegroundColor Green
    } else {
        throw "無効なファイルパスです。`n有効なディレクトリパスを渡してください"\
    }
} else {
    if ($item.PSIsContainer) {
        $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
        [Environment]::SetEnvironmentVariable("Path", $currentPath + ";" + $Args[0], "User")
        Write-Host "環境変数Pathを追加しました" -ForegroundColor Green
    } else {
        $parentPath = Split-Path -Path $Args[0] -Parent
        $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
        [Environment]::SetEnvironmentVariable("Path", $currentPath + ";" + $parentPath, "User")
        Write-Host "環境変数Pathを追加しました" -ForegroundColor Green
    }

}
