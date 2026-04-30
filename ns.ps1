Get-ChildItem -Recurse -Include *.h,*.cpp | ForEach-Object {
    $content = Get-Content $_.FullName -Raw
    $newContent = $content -replace 'namespace TRIGA','namespace triga'
    Set-Content $_.FullName $newContent
}