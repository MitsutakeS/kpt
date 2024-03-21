<# telepathy.add "YourPath" #>
<# Add to environment variables #>

$currentChcp = chcp | Out-String
if ($currentChcp -notmatch "65001") {
    chcp 65001
}

if ($null -eq $Args[0]) { <# Pathが与えられなかった場合 #>
    Write-Error "Please specify the path"
    Write-Host " Help -> telepathy.help" -ForegroundColor Green
} elseif (-not (Test-Path -Path $Args[0])) { <# 与えられたPathにフォルダが存在しない #>
    $item = Get-Item -Path $Args[0]
    if ($item.PSIsContainer) { <# Pathがファイルか判別 #>
        New-Item -Path $Args[0] -ItemType Directory
        Write-Warning ("存在しないディレクトリ: " + $Args[0] + " <-作成しました")
        Write-Host "環境変数Pathに変更はありません" -ForegroundColor Green
    } else {
        Write-Error "無効なファイルパスです。有効なディレクトリパスを渡してください"
    }
} else {
    $path = $env:Path -split ';'
    if ($path -contains $args[0]) {
        Write-Error "パスは既に存在します"
    } else {
        $item = Get-Item -Path $Args[0]
        if ($item.PSIsContainer) { <# 値がフォルダへのパスだった場合 #>
            $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
            [Environment]::SetEnvironmentVariable("Path", $currentPath + ";" + $Args[0], "User")
            Write-Host "環境変数Pathを追加しました" -ForegroundColor Green
        } else { <# 値がファイルへのパスだった場合 #>
            $parentPath = Split-Path -Path $Args[0] -Parent
            $currentPath = [Environment]::GetEnvironmentVariable("Path", "User")
            [Environment]::SetEnvironmentVariable("Path", $currentPath + ";" + $parentPath, "User")
            Write-Host "環境変数Pathを追加しました" -ForegroundColor Green
        }
    }
}
