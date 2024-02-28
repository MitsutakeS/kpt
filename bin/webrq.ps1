$global:url = $Args[0]
$global:path = $Args[1]
Write-Host $global:url
Write-Host $global:path
function rq_save_file {
    (Invoke-WebRequest $global:url).Content | Out-File -FilePath $global:path -Force
}
function rq_out {

    (Invoke-WebRequest $global:url).Content | Write-Host
}

if ($global:url -eq $null) {
    exit
} elseif ($global:path -eq $null) {
    rq_out
} else {
    rq_save_file
}
<# 結局また使うことになりました Webリクエストが簡単すぎる#>