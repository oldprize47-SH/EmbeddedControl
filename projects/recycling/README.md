# 자동 분리수거함 · 임베디드 제어 구성요소

[한국어](#korean) · [English](#english)

<a id="korean"></a>
## 한국어

이 저장소는 [임베디드 제어 프로젝트](https://github.com/oldprize47-SH/stm32-embedded-controller)의 자동 분리수거함 구성요소입니다. 전체 과목 프로젝트의 목표와 RC카·분리수거함 구성을 함께 살펴보려면 대표 문서에서 시작할 수 있습니다. 이곳에는 해당 구성요소의 비공개 구현 코드와 세부 기록을 보관합니다.

이 프로젝트는 하나의 투입구로 물품을 받아 등록된 바코드 정보에 따라 수거함을 선택하고, 사용자에게 포인트를 부여하며, 수거함이 가득 차면 알리는 분리수거함 시제품입니다. 2024년 임베디드 컨트롤러 수업에서 STM32F411RE 컨트롤러 두 개, 분류용 문, 투입 감지 센서, 초음파 적재 수준 센서를 사용해 제작했습니다.

[팀 시연 영상 보기](https://www.youtube.com/watch?v=dkphMHEKzxE).

### 프로젝트 목표

등록된 물품을 바코드로 식별하고, 해당 수거함으로 보내며, 수거함이 가득 차면 알립니다.

![프로젝트 목표: stm32-automatic-recycling-system](docs/goals/project-focus-v1.png)

AI로 생성한 개념도입니다. 장치의 외형, 인터페이스 배치, 예시 그래픽은 설명을 위한 표현이며, 실제 프로젝트 사진이나 측정 결과가 아닙니다.

### 활용할 수 있는 곳

이와 유사한 시스템은 수거 대상 물품의 바코드를 알고 있는 대학이나 사무실의 실내 분리수거 공간에서 활용할 수 있습니다. 바코드 조회로 분류 항목을 선택하고, 초음파 기반 만재 알림으로 관리자가 비울 수거함을 판단하도록 도울 수 있습니다. 이 프로젝트는 등록된 물품으로 이러한 아이디어를 시연합니다. 임의의 폐기물, 읽을 수 없는 바코드, 더 다양한 용기 형상을 처리하려면 추가 개발이 필요합니다.

### 한눈에 보기

![자동 분리수거 시스템](docs/flowcharts/recycling.png)

프로젝트 문서와 코드를 바탕으로 재구성한 개요입니다. 아래 설명에서 결과와 함께 확인된 범위와 검증의 한계를 살펴볼 수 있습니다. [SVG](docs/flowcharts/recycling.svg)

### 시스템 구성과 팀 역할

첫 번째 컨트롤러는 사용자·물품 입력, 스테퍼 모터 두 개, 서보 모터 한 개, 투입 감지 센서를 처리합니다. UART로 두 번째 컨트롤러에 사용자 인덱스를 보냅니다. 두 번째 컨트롤러는 초음파 센서 세 개를 읽고, 포인트를 갱신하며, 블루투스/UART로 상태 메시지를 전송합니다. 두 보드는 시스템의 하드웨어 구분이며, 팀 업무는 보드를 한 명씩 전담하는 방식이 아니라 기능별로 나누었습니다.

방준혁은 바코드 기반 회원·재활용품 분류 인식과 UART 송신을 개발했습니다. 박상헌은 스테퍼 모터, 서보 구동 투입구, 적외선 투입 감지를 포함한 투입 및 분류 순서를 개발했습니다. 또한 초음파 기반 만재 감지, 사용자 포인트, 블루투스 메시지, LED 상태 표시를 담당했습니다. 두 팀원은 기구 조립, 보드 연결, 완성된 시제품 시험을 함께 수행했습니다.

두 팀원 모두 애플리케이션 완성과 통합에 기여했습니다. 저장소에는 수업 지원 코드도 포함되어 있습니다. 각 보드는 자체 지원 라이브러리 변형본을 유지합니다.

### 한 번의 투입이 처리되는 과정

투입은 등록된 회원 및 제품 바코드 입력으로 시작합니다. 선택한 분류 항목에 따라 분류 경로가 결정됩니다. 기구는 경로와 투입구를 열고 투입 감지 센서를 확인한 다음, 기구를 닫고 두 번째 컨트롤러에 사용자 인덱스를 전송합니다. 두 번째 컨트롤러는 포인트를 갱신하고 완료 상태를 알립니다. 초음파 적재 수준 감시를 통해 별도로 수거함 만재 알림을 제공합니다.

이렇게 같은 시스템 안에서 실행되는 두 흐름, 즉 한 번의 투입을 처리하는 순서와 수거함의 남은 용량을 지속적으로 확인하는 과정을 구분할 수 있습니다. 보고서의 알고리즘 절과 두 보드의 애플리케이션이 이 흐름을 설명합니다. 물리적인 보드 경계가 어느 한 팀원의 단독 담당 범위를 뜻하지는 않습니다.

초음파 센서 세 개는 내용물 위에 남은 공간을 측정합니다. 이는 거리 기반 만재 표시이며, 무게 측정이나 영상 기반 재질 분류가 아닙니다. 시제품은 알려진 바코드 정보로 분류 항목을 결정합니다.

개별 시험을 마친 부품들을 실제 기구로 조립하고, 통합 동작에 맞게 센서와 배선을 배치했습니다. 수업 보고서에는 등록된 사용자와 제품 처리, 문 동작, 투입 감지, 수거함 만재 알림이 정상 작동했다고 기록되어 있습니다. 경사 구조의 기구는 둥근 플라스틱 용기와 캔 등의 물품을 기준으로 설계했으며, 다른 형상은 시연 범위에 포함되지 않았습니다.

### 소스

애플리케이션은 [보드 1](firmware/board-1/app/main.c)과 [보드 2](firmware/board-2/app/main.c)에 있습니다. 각 보드에는 자체 지원 라이브러리 변형본이 있으므로, 두 보드는 하나의 타깃으로 합치지 않고 각각의 타깃으로 유지해야 합니다.

코드는 GPIO, PWM, 타이머, 입력 캡처, UART를 사용합니다. 일부 제어 경로에는 블로킹 지연이 사용되며, 보드 간 1바이트 페이로드에는 프레이밍, 체크섬 또는 최신 데이터인지 확인할 정보가 없습니다. 이는 원래 시제품의 한계입니다.

### 펌웨어를 읽는 방법

첫 번째 보드에서는 투입 처리 순서를, 두 번째 보드에서는 상태 및 적재 수준 감시를 중심으로 읽으면 흐름을 이해하기 쉽습니다. UART 수신에서 시작해 입력에 따른 판단, 이어지는 모터 동작 또는 메시지 출력을 차례로 살펴볼 수 있습니다. 이 흐름과 주변장치 보조 라이브러리를 함께 읽으면 각 함수가 시스템에서 맡은 역할을 이해하는 데 도움이 됩니다.

배선을 살펴볼 때는 보관된 보고서와 소스의 일부 핀 및 UART 표기가 서로 다르다는 점을 함께 확인해야 합니다. 이 불일치가 있어 현재 자료를 검증된 배선 지침으로 사용할 수는 없습니다. 보고서에는 초음파 센서 세 개를 함께 사용할 때 발생한 오류도 기록되어 있지만, 현재 근거만으로는 실험적으로 입증된 단일 원인을 확정할 수 없습니다. 시연과 소스는 시제품을 설명하는 자료이며, 다시 제작하려면 보드 구성을 대조해 불일치를 해소해야 합니다.

### 빌드 참고 사항

빌드를 준비하려면 현재 자료에 없는 원래 IDE 프로젝트, 시작 파일, 링커 스크립트, 완전한 STM32Cube/CMSIS 환경이 필요합니다. 이 저장소를 별도로 컴파일하거나 펌웨어를 보드에 기록하거나 하드웨어에서 다시 시험하지 않았습니다. [BUILDING.md](BUILDING.md)에 누락된 의존성을 기록했으며, [기술 노트](docs/기술-요약.md)에는 소스와 배선에 대한 설명이 있습니다.

개인 바코드 테스트 데이터는 합성 값으로 교체했습니다. 공동 작성 코드와 수업 라이브러리의 재배포 권리가 해결되지 않은 동안 저장소는 비공개로 유지됩니다. [ATTRIBUTION.md](ATTRIBUTION.md)와 [NOTICE.md](NOTICE.md)에서 관련 내용을 확인할 수 있습니다.

---

<a id="english"></a>
## English

**Automatic Recycling System**

This repository holds the automatic recycling component of [Embedded Control Projects](https://github.com/oldprize47-SH/stm32-embedded-controller). For the course goals and the RC car and recycling system together, the main documentation is a helpful starting point. This repository keeps the private implementation and records for the recycling component.

This project is a recycling-bin prototype that accepts an item through one entrance, selects a bin from registered barcode information, awards user points and reports when a bin is full. It was built for the 2024 Embedded Controller course using two STM32F411RE controllers, sorting doors, a deposit sensor and ultrasonic level sensors.

[Watch the team demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

### Project goal

Identify a registered item from its barcode, direct it to the matching bin and report when a bin is full.

![Project goal: stm32-automatic-recycling-system](docs/goals/project-focus-v1.png)

AI-generated concept illustration. Device appearance, interface layout and example graphics are illustrative, not project photographs or measured results.

### Where it could be used

A similar system could support an indoor recycling station in a university or office where accepted items have known barcodes. Barcode lookup would select the sorting category, while ultrasonic fullness reports could help staff decide which bin to empty. The project demonstrates these ideas with registered items; handling arbitrary waste, unreadable barcodes or a wider range of container shapes would require further development.

### At a glance

![Automatic recycling system](docs/flowcharts/recycling.png)

This overview is reconstructed from the project documentation and code. The sections below explain the results, what was checked and the limits of that verification. [SVG](docs/flowcharts/recycling.svg)

### System configuration and team

The first controller handles user/item input, two stepper motors, a servo and the deposit sensor. It sends a user index to the second controller over UART. The second controller reads three ultrasonic sensors, updates points and sends status messages over Bluetooth/UART. The boards provide the system's hardware division; the team's work was divided by function rather than by exclusive ownership of a board.

방준혁 developed barcode-based member and recyclable-category recognition and UART transmission. Sangheon Park developed the deposit and sorting sequence, including the stepper motors, servo entrance and infrared deposit detection. He also handled ultrasonic fullness detection, user points, Bluetooth messages and LED status indication. Both members assembled the mechanism, connected the boards and tested the complete prototype.

Both team members contributed to the completed application and integration. The repository also contains course support code. Each board retains its own support-library variant.

### A deposit through the system

A deposit begins with registered member and product barcode input. The selected category determines the sorting path. The mechanism opens the path and entrance, checks the deposit sensor, then closes the mechanism and sends the user index to the second controller. That controller updates points and reports completion. Ultrasonic level monitoring provides the separate full-bin notification.

This separates two flows that run in the same system: the sequence for one deposit and the continuing check of bin capacity. The report's algorithm section and the two board applications describe these flows; physical board boundaries do not represent exclusive ownership by either team member.

The three ultrasonic sensors measure the remaining space above the contents. This is a distance-based indication of fullness, not a measurement of weight or an image-based classification of the material. The prototype uses known barcode information for its sorting category.

The separately tested parts were assembled into a physical mechanism, with sensors and wiring positioned for integrated operation. The course report records successful operation for registered users and products, door movement, deposit detection and full-bin notifications. Its sloped mechanism was designed around items such as rounded plastic containers and cans; other shapes were outside the demonstrated scope.

### Source

The applications are in [board 1](firmware/board-1/app/main.c) and [board 2](firmware/board-2/app/main.c). Each board has its own support-library variant, so the two need to remain separate targets rather than being combined into one.

The code uses GPIO, PWM, timers, input capture and UART. Some control paths use blocking delays, and the one-byte inter-board payload has no framing, checksum or freshness information. These are limitations of the original prototype.

### How to read the firmware

A helpful way into the firmware is to follow the deposit sequence on the first board and status and level monitoring on the second. Starting at UART reception, you can trace the decision made from the input and the resulting motor or message output. Reading the peripheral helpers alongside that flow makes their role in the system easier to understand.

When reviewing the wiring, keep the archived report and source side by side: some pin and UART labels differ. Those differences mean the material cannot yet serve as a verified wiring guide. The report also records errors when using three ultrasonic sensors together, but the available evidence does not establish a single experimentally proven cause. The demonstration and the source explain the prototype; rebuilding it requires reconciling the board setup.

### Build notes

Preparing a build requires the original IDE project, startup file, linker script and complete STM32Cube/CMSIS environment, which are missing from the archive. The repository has not been independently compiled, flashed or retested on hardware. [BUILDING.md](BUILDING.md) records the missing dependencies, and the [technical notes](docs/기술-요약.md) describe the source and wiring.

Personal barcode fixtures have been replaced with synthetic values. The repository remains private while joint-code and course-library redistribution rights are unresolved. Details are available in [ATTRIBUTION.md](ATTRIBUTION.md) and [NOTICE.md](NOTICE.md).
