
class Compile {

    [string] $sorceFileName
    [string] $withoutExtensionFileName
    [string] $executableName
    [string] $cpp_cmd

    <# デフォルトコンストラクタ #>
    Compile() {
        if ($Args[0] -ne $null) {
            $this.sorceFileName = $Args[0]
        } else {
            $this.sorceFileName = $this.askFilePath()
        }
        $this.withoutExtensionFileName = $this.sorceFileName.TrimEnd(".cpp")
        $this.executableName = $this.withoutExtensionFileName + ".exe"
        $this.cpp_cmd = ""
    }
    <# デストラクタ (という機能がないので代用品)#>
    [string] destCompile() {

        if ($? -and $this.cpp_cmd -ne "") {
            Write-Host ""
            (Invoke-Expression $this.executableName) | Write-Host
            Write-Host "`nExit kpt. goodbye $env:USERNAME." -ForegroundColor DarkGreen
        } elseif ($this.cpp_cmd -eq "") {
            Write-Host "No executable file specified." -ForegroundColor Red
        }

        return ""
    }
    [string] run() {
        if ($this.cpp_cmd -eq "") {
            return ""
        } else {
            Write-Host
            $this.cpp_cmd = "g++ "
            $this.cpp_cmd += $this.sorceFileName
            $this.cpp_cmd += " -o `""
            $this.cpp_cmd += $this.executableName
            $this.cpp_cmd += "`"  -L `"$PSScriptRoot\lib`" -L `"$PSScriptRoot\include\Python310\libs`" -L `"$env:JAVA_HOME\lib`" -lstr -lnum -ljvm -lpython310 -loleaut32"
            (Invoke-Expression $this.cpp_cmd) | Write-Host
            return (
                $this.cpp_cmd
            )
        }
    }
    [string] runOptionalNoneJava() {

        Write-Host "`nTrying to compile for environments without Java`n" -ForegroundColor Yellow
        $this.cpp_cmd = "g++ `""
        $this.cpp_cmd += $this.sorceFileName
        $this.cpp_cmd += "`" -o `""
        $this.cpp_cmd += $this.executableName
        $this.cpp_cmd += "`" -L `"$PSScriptRoot\lib`" -L `"$PSScriptRoot\include\Python310\libs`" -lstr -lnum -lpython310 -loleaut32"
        (Invoke-Expression $this.cpp_cmd) | Write-Host
        return (
            $this.cpp_cmd
        )
    }
    [string] get_cmd() {
        return ($this.cpp_cmd)
    }
    [string] askFilePath() {
        Write-Host "`n実行するCppファイルのフルパスを入力してください:`n" -ForegroundColor Green
        return (Read-Host)
    }
}
#main
$compile = [Compile]::new()
$compile.run()
if (!$?) {
    $compile.runOptionalNoneJava()
}

$compile.destCompile()
<#

PowerShellを初めて書いてみて思ったんですが、
一部の機能はよかったわりに
オーバーロードが無かったり、デストラクタが無かったり、外部ファイル不可
これはちょっと私の性格に合いませんねぇ
しかも言語自体の処理速度が他のスクリプト言語と比べても各段に遅かったり。
状況によっては用途に合わせて使えば他言語に勝る部分は多いと思いますので
とんとんだな～って感じました。演算子が真新しく楽しかったです。
結論Cで組めばよかったですけど（今さら）
ﾃｲｳｶclassﾂｸﾙ ｲﾐ ﾅｶｯﾀ…

#>
