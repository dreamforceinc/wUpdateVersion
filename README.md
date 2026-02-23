# wUpdateVersion

Программа для автоматического обновления номера версии компилируемого приложения.

_**Файл ресурсов должен быть в ANSI или UTF-8 кодировке.**_


## Назначение программы ##
`wUpdateVersion` служит для автоматического обновления версии разрабатываемого приложения перед этапом компиляции в среде разработки Microsoft Visual Studio. Программа извлекает значение версии из файла, содержащего макрос или определение `APP_VERSION`, и записывает эту версию в блок `VERSIONINFO` файла ресурсов.

## Что делает программа? ##

1. Извлекает версию приложения из заданного файла (*например `version.h`*), содержащего строку вида `#define APP_VERSION "X.Y.Z.W"`.

2. Обновляет в указанном файле ресурсов (*например `resources.rc`*) блок `VERSIONINFO`, содержащий строки `FileVersion` и `ProductVersion`, соответственно.

## Параметры запуска ##

Запускайте программу командой в консоли:

```bash
path\to\wUpdateVersion.exe arg1 arg2
```
Параметры:

`path\to\wUpdateVersion.exe`: Полный путь к программе.

`arg1`: Путь к файлу, содержащему определение версии (`version.h`).

`arg2`: Путь к файлу ресурсов (`resources.rc`).

Например:

```bash
C:\Utils\wUpdateVersion.exe C:\Project\version.h C:\Project\resources.rc
```

## Автоматизация запуска программы перед сборкой проекта ##

Вы можете добавить вызов программы в качестве предкомпиляционного шага в проекте Microsoft Visual Studio, выполнив следующие шаги:

1. Щёлкните правой кнопкой мыши по проекту в Solution Explorer и выберите пункт Properties.

2. Перейдите на вкладку Build Events, раздел Pre-Build Event, Command Line.

3. Добавьте туда следующий код:
```bash
"$(SolutionDir)wUpdateVersion.exe" "$(ProjectDir)version.h" "$(ProjectDir)resources.rc"
```
> *В данном примере программа `wUpdateVersion.exe` находится в папке решения, а файлы `version.h` и `resources.rc` - в папке проекта.*

4. Обновите определение макроса `APP_VERSION` в файле `version.h` (Например `APP_VERSION "1.0"` -> `APP_VERSION "1.1"`).

Таким образом, каждый раз перед компиляцией проекта версия программы будет автоматически обновляться.

_(c) 2026 Vladislav Salikov aka W0LF aka 'dreamforce'_

> _Этот текст создан с помощью Giga.Chat._
-----

# wUpdateVersion

A program for automatically updating the version number of a compiled application.

_**The resource file must be in ANSI or UTF-8 encoding.**_

## Purpose of the Program ##
`wUpdateVersion` is used to automatically update the version of an application being developed before compilation in the Microsoft Visual Studio development environment. The program extracts the version value from a file containing the `APP_VERSION` macro or definition and writes this version to the `VERSIONINFO` block of the resource file.

## What does the program do? ##

1. Extracts the application version from the specified file (*e.g. `version.h`*) containing the string `#define APP_VERSION "X.Y.Z.W"`.

2. Updates the `VERSIONINFO` block in the specified resource file (*e.g. `resources.rc`*), containing the strings `FileVersion` and `ProductVersion`, respectively.

## Launch Parameters ##

Run the program with the following command in the console:

```bash
path\to\wUpdateVersion.exe arg1 arg2
```
Parameters:

`path\to\wUpdateVersion.exe`: Full path to the program.

`arg1`: Path to the file containing the version definition (`version.h`).

`arg2`: Path to the resource file (`resources.rc`).

For example:

```bash
C:\Utils\wUpdateVersion.exe C:\Project\version.h C:\Project\resources.rc
```

## Automating Program Launch Before Building the Project ##

You can add a program call as a pre-compile step in a Microsoft Visual Studio project by following these steps:

1. Right-click the project in Solution Explorer and select Properties.

2. Go to the Build Events tab, Pre-Build Event section, Command Line.

3. Add the following code:
```bash
"$(SolutionDir)wUpdateVersion.exe" "$(ProjectDir)version.h" "$(ProjectDir)resources.rc"
```
> *In this example, the `wUpdateVersion.exe` program is located in the solution folder, and the `version.h` and `resources.rc` files are in the project folder.*

4. Update the `APP_VERSION` macro definition in the `version.h` file (e.g. `APP_VERSION "1.0"` -> `APP_VERSION "1.1"`).

This way, the program version will be automatically updated each time the project is compiled.

_(c) 2026 Vladislav Salikov aka W0LF aka 'dreamforce'_

> _This text was created using Giga.Chat._
-----
