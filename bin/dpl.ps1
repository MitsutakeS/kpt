. "$PSScriptRoot\webrq.ps1"
function Detect-Language($str) {
    # 英語の文字のコードポイントの範囲
    $EnglishRange = 0x00..0x7F
    # 日本語の文字のコードポイントの範囲
    $JapaneseRange = (0x3040..0x309F) + (0x30A0..0x30FF) + (0x4E00..0x9FFF)
    foreach ($char in $str.ToCharArray()) {
        # 文字のコードポイントを取得
        $codepoint = [int][char]$char
        # 英語の範囲に含まれる場合
        if ($EnglishRange -contains $codepoint) {
            return "English"
        }
        # 日本語の範囲に含まれる場合
        elseif ($JapaneseRange -contains $codepoint) {
            return "Japanese"
        }
    }
    return "Languages unknown"
}

if ($Args[0] -eq $null) {
    Write-Host "<This is help>`n You can select the mode by specifying J-E or E-J as command line arguments.If there is no mode, the language to be translated is determined from the first character of the string specified as the argument.`n<これはヘルプです>`nJ-E、もしくはE-Jをコマンドライン引数に指定してモードを選択できます`nモードが無い場合、引数として指定された文字列の最初の文字から翻訳すべき言語を判断して翻訳します"
} elseif ($Args[0] -eq "j-e" -or $Args[0] -eq "J-E") {
    $global:mode = "je"
} elseif ($Args[0] -eq "e-j" -or $Args[0] -eq "j-e") {
    $global:mode = "ej"
} elseif (Detect-Language $Args[0] -eq "Japanese") {
    $global:mode = "je"
} elseif (Detect-Language $Args[0] -eq "English") {
    $global:mode = "ej"
} else {
    (Detect-Language $Args[0]) | Write-Host
    exit
}
if ($global:mode -eq "je") {
}

