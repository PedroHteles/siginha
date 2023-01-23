param (
    [string]$folderPath,
    [string]$folderName
)

# Creating the folder "Telas" in the specified path
New-Item -ItemType directory -Path "$folderPath\Telas" -Force

# Creating the folder with the name passed as parameter
New-Item -ItemType directory -Path "$folderPath\Telas\$folderName" -Force

# Creating the index.css file
New-Item -ItemType file -Path "$folderPath\Telas\$folderName\index.css" -Force

# Creating the jsx component file with the content passed as parameter
$jsxText = "import React from ""react"";
import ""./index.css""

const $folderName = () => (

  <>
    <p> Tela Nova </p>
  </>

);

export default  $folderName()"

New-Item -ItemType file -Path "$folderPath\Telas\$folderName\$folderName.jsx" -Force
Add-Content -Path "$folderPath\Telas\$folderName\$folderName.jsx" -Value $jsxText

# Updating the React component name
(Get-Content "$folderPath\Telas\$folderName\$folderName.jsx") | 
Foreach-Object {$_ -replace "const TelaNova", "const $folderName"} |
Set-Content "$folderPath\Telas\$folderName\$folderName.jsx"

# Adding the object in the Menus.js file
$stringInKebabCase = $folderName -replace ' ', '-'
$menusJsText = 
"
  {
  funcao: funcoes.get('funcao'), 
  sistema: sistemas.get('setor'),
    url: '$stringInKebabCase', 
    texto: '$folderName', 
    component: $folderName
  },"
(Get-Content "$folderPath\Menus.js") | 
Foreach-Object {
    if($_ -match "const menus = \[")
    {
        $_ + $menusJsText
    }
    else
    {
        $_
    }
} | 
Set-Content "$folderPath\Menus.js"