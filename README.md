# pio-renode-ci
This project consists of a simple hello world program developed using PlatformIO and built to run on STM32F4 and STM32L4 targets. In addition this project comes with scripts that can be used to simulate and test the program using the Renode platform.

## Screenshot:

![SharedScreenshot](https://user-images.githubusercontent.com/22129291/129455741-d0a1c98f-9910-4914-99cf-fefebee7d36b.jpg)

## How to simulate the project on Renode on Windows:
* Open **Windows Powershell** or **Powershell7** in the root directory of the project.
* Run the following command to simulate the firmware on an STM32F4 target:
``` powershell
> .\scripts\start_f4.ps1
```
* Run the following command to simulate the firmware on an STM32L4 target:
``` powershell
> .\scripts\start_l4.ps1
```

## TODO:
* Fix automated tests
* Make scripts more generic and target agnostic
* Add status badges (build/test/release/tag...) to the readme page
