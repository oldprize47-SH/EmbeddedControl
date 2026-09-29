# 임베디드 제어 프로젝트

[한국어](#korean) · [English](#english)

<a id="korean"></a>
## 한국어

이 문서는 임베디드 제어 과목의 대표 문서입니다. 주변장치 실습, RC카와 자동 분리수거함을 한 프로젝트 묶음으로 설명합니다. 별도 분리수거함 저장소는 구현 코드를 보관하는 비공개 구성요소 저장소이며, 별개의 포트폴리오 프로젝트로 구분하지 않습니다.

이 저장소에는 2024년 임베디드 컨트롤러 수업에서 수행한 STM32F411 주변장치 실습과 두 프로젝트인 라인 추종 RC카 및 자동 분리수거 시스템이 담겨 있습니다. GPIO, 타이머, PWM, 센서 입력, 직렬 통신을 C로 제어하는 실제 기구에 연결한 작업입니다.

### 프로젝트 목표

센서 입력을 물리적 동작으로 연결하는 임베디드 프로그램을 작성하고, 이를 RC카와 분리수거함 시제품으로 구현합니다.

![프로젝트 목표: stm32-embedded-controller](docs/goals/project-focus-v1.png)

AI로 생성한 개념도입니다. 장치의 외형, 인터페이스 배치, 예시 그래픽은 설명을 위한 표현이며, 실제 프로젝트 사진이나 측정 결과가 아닙니다.

### 활용할 수 있는 곳

RC카는 경로 추종, 수동 제어, 장애물 감지 시 정지 동작을 가르치는 소형 플랫폼으로 활용할 수 있습니다. 센서 입력에서 상태 판단을 거쳐 모터 동작으로 이어지는 흐름은 경로를 따라 이동하는 모바일 로봇 실습의 출발점으로도 삼을 수 있습니다. 분리수거 프로젝트는 같은 임베디드 기술을 고정식 기구에 적용한 또 다른 사례입니다. 두 프로젝트 모두 수업용 시제품이며, 실제 시설에 적용하려면 그에 맞는 별도 수준의 하드웨어 및 신뢰성 시험이 필요합니다.

### 주변장치 실습에서 동작하는 시제품까지

초기 실습에서는 마이크로컨트롤러의 각 기능을 하나씩 분리해 다룹니다. GPIO와 외부 인터럽트는 스위치와 간단한 출력을 처리합니다. 타이머는 일정한 시간 간격을 만들고, PWM은 모터 명령을 조절하며, 입력 캡처는 초음파 센서의 에코 펄스 지속 시간을 측정합니다. 이후 프로젝트에서는 이 기능들을 결합하여 센서 측정값이 프로그램의 상태에 영향을 주고, 그 상태가 액추에이터 출력으로 이어지도록 합니다.

이러한 순서로 자료를 살펴보면 이해하기 좋습니다. 개별 주변장치 실습에서 시작한 뒤, 같은 종류의 입력이나 출력이 RC카 또는 분리수거 시스템에서 어떻게 쓰이는지 확인할 수 있습니다. [lib](lib)의 지원 함수에는 수업 제공 자료와 과제에 사용한 작업 내용이 함께 포함되어 있습니다.

### 프로젝트 구성과 팀 역할

#### 라인 추종 RC카

![수동 및 자율 주행 RC카](docs/flowcharts/rc-car.png)

[벡터 도식](docs/flowcharts/rc-car.svg)

RC카는 DC 모터 두 개, 적외선 반사 센서, 초음파 센서, 블루투스 명령을 결합합니다. 수동 모드에서는 이동 및 속도 명령을 제공합니다. 자동 모드에서는 좌우 반사 측정값으로 라인을 따라가며, 초음파 입력으로 장애물 정지 조건을 판단합니다. 프로그램은 [LAB_RC_Final.c](LAB/LAB_RC_Final.c)에 있습니다.

보고서에서는 프로그램을 전체 흐름과 두 가지 모드별 흐름으로 나누어 설명합니다. 전체 흐름에서는 일반 이동에 앞서 장애물 정지 여부를 판단합니다. 이동이 허용되면 블루투스 입력에 따라 수동 또는 자동 운전을 선택합니다. 수동 모드에서는 명령으로 방향, 속도 또는 조향을 갱신하고, 자동 모드에서는 좌우 적외선 측정값의 차이로 조향 상태를 선택합니다. 선택한 상태는 모터 듀티 명령으로 변환됩니다.

![원본 팀 보고서의 RC카 전체 흐름](docs/images/rc-flow-overview.png)

전체 흐름도의 “Distance” 판단은 장애물 조건을 나타냅니다. 이는 보고서에서 단순화한 도식입니다. 실제 소스는 모든 상자를 하나의 블로킹 순서로 실행하는 대신, 인터럽트 핸들러를 통해 센서, 통신, 모터를 갱신합니다. 보고서에는 [수동 모드 흐름](docs/images/rc-flow-manual.png)과 [라인 추종 흐름](docs/images/rc-flow-auto.png)도 포함되어 있습니다.

박상헌은 수동 제어와 라인 추종을 구현했습니다. 김찬중은 하드웨어 배치와 배선을 담당했습니다. 두 팀원은 정지 동작을 함께 개발했으며, 센서 측정값과 모터 명령을 함께 확인해야 하는 주행 시험 과정에서 차량을 반복적으로 조정했습니다. 장애물 감지는 이 공동 개발의 일부였으며, 개인별 담당 범위는 확인되지 않았습니다.

#### 자동 분리수거 시스템

![자동 분리수거 시스템](docs/flowcharts/recycling.png)

[벡터 도식](docs/flowcharts/recycling.svg)

분리수거 시스템은 바코드 정보로 사용자와 물품을 인식하고, 분류 경로를 선택한 뒤 문을 열어 투입을 감지하고 완료 상태를 알립니다. 두 컨트롤러가 투입 기구 제어와 수거함의 적재 수준 및 상태 감시를 나누어 처리합니다. 애플리케이션은 [final_first_board.c](LAB/final_first_board.c)와 [final_second_board.c](LAB/final_second_board.c)에 있습니다.

방준혁은 바코드 기반 회원·재활용품 분류 인식과 UART 송신을 개발했습니다. 박상헌은 스테퍼 모터, 서보 구동 투입구, 적외선 투입 감지를 포함한 투입 및 분류 순서를 개발했습니다. 또한 초음파 기반 만재 감지, 사용자 포인트, 블루투스 메시지, LED 상태 표시를 담당했습니다. 두 팀원은 기구 조립, 보드 연결, 완성된 시제품 시험을 함께 수행했습니다.

[분리수거 시스템 시연 영상 보기](https://www.youtube.com/watch?v=dkphMHEKzxE).

#### 주변장치 실습과 공용 지원 코드

![STM32 주변장치 실습](docs/flowcharts/embedded-labs.png)

[벡터 도식](docs/flowcharts/embedded-labs.svg)

개별 실습은 박상헌의 수업 과제입니다. 지원 라이브러리에는 수업에서 제공한 자료와 공동 수정 사항도 포함되어 있습니다. 위에 명시한 애플리케이션 작성 역할이 어느 팀이든 모든 지원 함수를 독자적으로 작성했다는 뜻은 아닙니다.

### 파일

- [PWM 및 DC 모터 실습](LAB/LAB_PWM_DCmotor_21800275_SangheonPark.c)
- [초음파 입력 캡처 실습](LAB/LAB_Timer_InputCaputre_Ultrasonic_21800275_SangheonPark.c)
- [수업 지원 라이브러리](lib)

### 보존된 시연으로 확인할 수 있는 범위

분리수거 시연은 수업용 시제품이 등록된 물품을 처리하고 상태를 알리는 모습을 보여 줍니다. 물품 형상과 기구의 제약이 있는 소형 실물 시제품으로, 범용 폐기물 인식 시스템은 아닙니다. 소스는 바코드 정보로 분류 항목을 선택하며, 카메라 영상으로 재질을 추론하지 않습니다.

개별 실습과 팀 시연은 당시 수업에서 얻은 결과입니다. 아래 빌드는 포트폴리오 업데이트 중 수행한 별도의 확인입니다. 이 두 종류의 근거를 구분하면 현재 저장소에서 재현할 수 있는 범위가 명확해집니다.

### 빌드 참고 사항

RC카 프로그램, 일부 주변장치 실습, 지원 파일은 2026년 9월 28일 로컬 수업 자료 사본을 바탕으로 업데이트했습니다. [PlatformIO 설정](platformio.ini)은 CMSIS 프레임워크를 사용하여 Nucleo F411RE용 RC카 타깃을 빌드합니다.

```sh
pio run -e rc_car
```

업데이트 당시 이 저장소 설정으로 빌드에 성공했습니다. UART 심볼 중복을 피하기 위해 대체 구현인 `ecUART2_simple.c`는 제외합니다. ADC 포인터 자료형과 printf 인자 자료형 등을 포함한 기존 컴파일러 경고는 남아 있습니다. 이는 RC카 타깃의 컴파일 확인이며, 분리수거 애플리케이션, 보드 배선, 보정 또는 실제 동작을 검증한 것은 아닙니다. 펌웨어를 보드에 기록하지 않았습니다.

[원본 저장소](https://github.com/oldprize47/Embbadded_Controller_2024). 원래의 이력과 저작자 표기를 유지합니다.

### 보관된 프로젝트 예시

![프로젝트 목표: stm32-embedded-controller](docs/goals/project-goal.jpg)

원본 팀 보고서에 수록된 RC카 시제품입니다. 보관 자료에는 분리수거 시스템과 주변장치 실습도 포함되어 있습니다.

---

<a id="english"></a>
## English

**Embedded Control Projects**

This is the main documentation for the embedded-control course work, covering peripheral exercises, the RC car and the automatic recycling system. The separate recycling repository is a private implementation archive for one component, not another portfolio project.

This repository contains STM32F411 peripheral exercises and two projects from the 2024 Embedded Controller course: a line-following RC car and an automatic recycling system. The work connects GPIO, timers, PWM, sensor inputs and serial communication to physical mechanisms controlled in C.

### Project goal

Build embedded programs that connect sensor inputs to physical actions, culminating in an RC car and a recycling-bin prototype.

![Project goal: stm32-embedded-controller](docs/goals/project-focus-v1.png)

AI-generated concept illustration. Device appearance, interface layout and example graphics are illustrative, not project photographs or measured results.

### Where it could be used

The RC car is a small platform for teaching path following, manual control and obstacle-stop behaviour. Its sensor-to-state-to-motor sequence can also serve as a starting point for a guided mobile-robot exercise. The recycling project provides a second example of the same embedded skills in a stationary mechanism. These are classroom prototypes; adapting them to a working facility would require a different level of hardware and reliability testing.

### From peripheral exercises to a working prototype

The earlier labs isolate one part of the microcontroller at a time. GPIO and external interrupts handle switches and simple outputs. Timers provide repeatable timing, PWM changes the motor command, and input capture measures the duration of an ultrasonic sensor's echo pulse. The later projects combine these functions, so a sensor reading affects the program's state and then the actuator output.

This progression is the useful way to read the archive: begin with an individual peripheral exercise, then look at how the same kind of input or output appears in the RC car or recycling system. The support functions in [lib](lib) include course material as well as work used in the assignments.

### Project configuration and team

#### Line-following RC car

![Manual and autonomous RC car](docs/flowcharts/rc-car.png)

[Vector diagram](docs/flowcharts/rc-car.svg)

The RC car combines two DC motors, infrared reflectance sensors, an ultrasonic sensor and Bluetooth commands. Manual mode provides movement and speed commands. Automatic mode uses the left/right reflectance measurements to follow a line, with the ultrasonic input providing the obstacle-stop condition. The program is in [LAB_RC_Final.c](LAB/LAB_RC_Final.c).

The report separates the program into an overall flow and two mode-specific flows. The overview places the obstacle-stop decision before normal movement. When movement is allowed, Bluetooth input selects manual or automatic operation. In manual mode, commands update direction, speed or steering; in automatic mode, the difference between the left and right infrared readings selects a steering state. The selected state is converted into motor duty commands.

![Overall RC-car flow from the original team report](docs/images/rc-flow-overview.png)

The overview's “Distance” decision represents the obstacle condition. It is a simplified report diagram: the source performs sensor, communication and motor updates through interrupt handlers, rather than executing every box as a single blocking sequence. The report also includes the [manual-mode flow](docs/images/rc-flow-manual.png) and [line-following flow](docs/images/rc-flow-auto.png).

Sangheon Park implemented manual control and line following. 김찬중 arranged the hardware layout and wiring. Both members developed the stopping behaviour and repeatedly adjusted the car during driving tests, where sensor readings and motor commands needed to be checked together. Obstacle detection was part of this shared development; its individual attribution has not been confirmed.

#### Automatic recycling system

![Automatic recycling system](docs/flowcharts/recycling.png)

[Vector diagram](docs/flowcharts/recycling.svg)

The recycling system recognises a user and item from barcode information, selects a sorting path, opens the doors, detects the deposit and reports completion. Two controllers divide the deposit mechanism from bin-level and status monitoring. The applications are in [final_first_board.c](LAB/final_first_board.c) and [final_second_board.c](LAB/final_second_board.c).

방준혁 developed barcode-based member and recyclable-category recognition and UART transmission. Sangheon Park developed the deposit and sorting sequence, including the stepper motors, servo entrance and infrared deposit detection. He also handled ultrasonic fullness detection, user points, Bluetooth messages and LED status indication. Both members assembled the mechanism, connected the boards and tested the complete prototype.

[Watch the recycling system demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

#### Peripheral exercises and shared support

![STM32 peripheral exercises](docs/flowcharts/embedded-labs.png)

[Vector diagram](docs/flowcharts/embedded-labs.svg)

The individual labs are Sangheon Park's coursework. The support library also contains supplied course material and shared modifications. The application authorship above does not imply that either team independently authored every support function.

### Files

- [PWM and DC motor exercise](LAB/LAB_PWM_DCmotor_21800275_SangheonPark.c)
- [Ultrasonic input-capture exercise](LAB/LAB_Timer_InputCaputre_Ultrasonic_21800275_SangheonPark.c)
- [Course support library](lib)

### What the saved demonstrations establish

The recycling demonstration shows the course prototype handling its registered items and reporting status. It is a small physical prototype with a constrained item shape and mechanism, not a general waste-recognition system. The source uses barcode information to choose a category; it does not infer material from a camera image.

The individual labs and team demonstrations are historical course results. The build below is a separate check made during the portfolio update. Keeping those two kinds of evidence separate makes it clear what can be reproduced from this repository today.

### Build notes

The RC-car program, selected peripheral labs and supporting files were updated from the local coursework copy on 28 September 2026. The [PlatformIO configuration](platformio.ini) builds the RC-car target for the Nucleo F411RE with the CMSIS framework:

```sh
pio run -e rc_car
```

This repository configuration built successfully during the update. It excludes the alternative `ecUART2_simple.c` implementation to avoid duplicate UART symbols. Existing compiler warnings remain, including ADC pointer types and printf argument types. This is a compile check for the RC-car target; it does not validate the recycling applications, board wiring, calibration or physical operation. No firmware was flashed.

[Original repository](https://github.com/oldprize47/Embbadded_Controller_2024). Original history and attribution are retained.

### Archived project example

![Project goal: stm32-embedded-controller](docs/goals/project-goal.jpg)

The RC-car prototype from the original team report; the archive also contains the recycling system and peripheral exercises.
