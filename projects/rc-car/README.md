# RC카 구현 안내 / RC implementation guide

과목 전체 이야기와 팀 역할은 [루트 README](../../README.md)에 있습니다. 여기서는 소스와 빌드 연결을 정리합니다.

## 소스와 실행 구조

- [LAB_RC_Final.c](../../LAB/LAB_RC_Final.c): 수동/자동 모드, 센서 읽기, 주행 상태와 인터럽트 처리.
- [lib](../../lib): GPIO, ADC, 타이머, 입력 캡처, PWM, UART 지원 함수. 분리수거 보드 2와 같은 구현을 사용합니다.
- [platformio.ini](../../platformio.ini): RC 앱 하나와 지원 구현을 선택하며 대체 UART 구현은 제외합니다.

Bluetooth 명령에서 모드·방향·속도·조향 상태로 이어지는 경로와, ADC의 좌우 반사값에서 자동 조향으로 이어지는 경로를 나누어 읽으면 좋습니다. 초음파 에코는 입력 캡처로 측정합니다. 보고서의 장애물 우선 판단은 의도한 동작의 요약이며, 실제 소스의 센서·통신·출력 갱신은 인터럽트별로 분산되어 있습니다.

[전체 흐름](../../docs/images/rc-flow-overview.png) · [수동 제어](../../docs/images/rc-flow-manual.png) · [자동 제어](../../docs/images/rc-flow-auto.png)

## 빌드와 한계

저장소 루트에서 `pio run -e rc_car`를 실행합니다. MCU 타깃은 Nucleo F411RE, 프레임워크는 CMSIS입니다. 기존 ADC 포인터와 `printf` 인자 자료형 등의 경고를 숨기지 않습니다. 빌드는 배선·센서 임계값·장애물 정지의 실물 검증을 대신하지 않습니다. 이번 통합에서 RC 앱의 동작 코드는 바꾸지 않았습니다.

## English

Start from [LAB_RC_Final.c](../../LAB/LAB_RC_Final.c). Follow Bluetooth input into mode, direction, speed and steering state, then trace the separate path from left/right ADC reflectance readings into automatic steering. Ultrasonic echoes use timer input capture. The report's obstacle-first overview describes intent; actual updates are distributed across interrupt handlers.

The root [PlatformIO configuration](../../platformio.ini) builds this one application with [lib](../../lib), excluding the alternative UART implementation. Run `pio run -e rc_car` from the repository root for Nucleo F411RE/CMSIS. Existing pointer/format warnings remain. Compilation does not establish correct wiring, calibration or physical stopping behaviour. Application behaviour was not modified during consolidation. See the [root guide](../../README.md) for the course narrative, photographs, results and confirmed team roles.
