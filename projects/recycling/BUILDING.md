# 빌드 및 검증 경계

## 이번 로컬 통합에서 확인한 것 (2026-09-29)

설치되어 있던 GNU Arm 도구와 CMSIS 헤더로 보드 1의 10개, 보드 2의 9개 translation unit을 각각 object로 컴파일했습니다(앱 포함, 모두 exit 0). 보드 1은 전용 support include 경로만, 보드 2는 루트 lib만 사용했습니다. 기존 경고는 남아 있습니다. 이는 include/API 호환성과 개별 컴파일 확인이며 startup·linker를 포함한 두 실행 파일의 링크 성공이나 실물 동작 검증은 아닙니다. RC카만 PlatformIO clean build까지 확인했습니다. 정확한 도구 경로·flags·명령·로그는 checkout 옆 `embedded-receipt.json`에 있습니다.

During local consolidation, all 10 board-1 and 9 board-2 translation units compiled to objects using the installed GNU Arm compiler and CMSIS headers, with separate support include paths. Existing warnings remain. No recycling executable was linked or flashed; only the RC target received a complete PlatformIO clean build.

## 현재 상태

이 저장소는 STM32F411RE용 응용 코드와 해당 응용 코드가 참조하는 최소 course/shared support 소스를 포함합니다. 그러나 vendor startup/CMSIS 전체, linker script, IDE project, 확정된 compiler version이 없어 **checkout 직후 독립 빌드할 수 있는 상태가 아닙니다**.

이 문서는 누락을 숨기지 않고, 재현 가능한 빌드 패키지를 만들 때 필요한 경계를 명시합니다. 아래 절차는 구성 가이드이며 실제 성공한 build log가 아닙니다.

## Target 분리

Board 1은 전용 support 변형을, Board 2는 RC카와 같은 루트 `lib`를 사용합니다. 동일한 이름의 함수가 있어도 두 구현을 섞으면 안 됩니다. 반드시 별도 executable target으로 구성합니다.

### Board 1 source set

응용:

- `firmware/board-1/app/main.c`

구현:

- `ecADC2.c`
- `ecGPIO2.c`
- `ecPWM2.c`
- `ecPinNames.c`
- `ecRCC2.c`
- `ecStepper.c`
- `ecSysTick2.c`
- `ecTIM2.c`
- `ecUART2.c`

헤더는 `firmware/board-1/support/*.h` 전체를 include path에 둡니다. `ecADC2.h`와 `ecSTM32F4v2.h`의 집합 include 관계 때문에, 구현을 링크하지 않는 `ecEXTI2.h`와 `ecICAP2.h`도 전처리에 필요합니다.

### Board 2 source set

응용:

- `firmware/board-2/app/main.c`

구현:

- `ecGPIO2.c`
- `ecICAP2.c`
- `ecPWM2.c`
- `ecPinNames.c`
- `ecRCC2.c`
- `ecSysTick2.c`
- `ecTIM2.c`
- `ecUART2.c`

위 Board 2 구현 8개는 저장소 루트 `lib`에서 선택합니다. 헤더 include path 역시 루트 `lib`이며 컴포넌트 기준으로는 `../../lib`입니다. 집합 헤더가 선언 헤더들을 연쇄 포함하기 때문입니다.

Board 1 support와 루트 lib를 하나의 include path 또는 target source list에 동시에 넣지 마세요. 동일 심볼의 구현이 충돌하거나 잘못된 보드 변형이 선택될 수 있습니다.

## 외부에서 준비해야 할 항목

STM32CubeIDE, Keil MDK 또는 `arm-none-eabi-gcc` 기반 환경 중 하나를 선택한 뒤 다음 요소를 **공식 STM32CubeF4 배포물과 그 라이선스 조건에 따라** 준비해야 합니다.

1. STM32F411xE device headers와 CMSIS Core
2. `startup_stm32f411xe.s`
3. `system_stm32f4xx.c`
4. STM32F411RE flash/RAM layout에 맞는 linker script
5. target 정의 `STM32F411xE`
6. Cortex-M4F CPU/FPU/ABI flags
7. C library와 math library (`round` 사용 경로 때문에 `libm` 고려)
8. programmer/debugger 설정과 NUCLEO-F411RE board profile

vendor 파일을 이 저장소에 복사하기 전에 해당 배포물의 재배포 조건을 확인하세요. 이 저장소는 vendor 매뉴얼과 vendor source에 새 라이선스를 부여하지 않습니다.

## 권장 project 구성

```text
board-1 target
  app:     firmware/board-1/app/main.c
  support: firmware/board-1/support/*.c 중 위 9개
  include: firmware/board-1/support + CMSIS/Device include

board-2 target
  app:     firmware/board-2/app/main.c
  support: ../../lib/*.c 중 위 8개 (전체 glob 금지)
  include: ../../lib + CMSIS/Device include
```

Clock 관련 support 코드는 84 MHz PLL을 전제로 작성되어 있습니다. 실제 clock tree와 flash wait state 설정이 target board, voltage와 맞는지 reference manual/board configuration으로 다시 확인해야 합니다.

## 컴파일 전 확인

- Board 1과 Board 2 source/include path가 완전히 분리되었는가
- `stm32f411xe.h`와 `stm32f4xx.h`가 동일 Cube/CMSIS version에서 오는가
- startup의 vector table에 사용 ISR 이름이 연결되는가
- USART1/2/6 alternate-function pin이 실제 board와 일치하는가
- `printf` retarget과 C library syscall 설정이 toolchain에 맞는가
- math symbol이 link되는가
- warnings를 숨기는 광범위한 compiler flag를 추가하지 않았는가

## 빌드 검증을 완료했다고 말할 수 있는 조건

1. 두 target 각각 clean configure/build 명령과 exit code 0이 기록됨
2. map 파일에서 중복 HAL 변형이 링크되지 않았음
3. linker undefined symbol이 없음
4. 생성된 ELF의 target MCU/메모리 layout가 STM32F411RE와 일치함
5. firmware size가 flash/RAM 한도 내임
6. board별 binary와 source revision/hash가 기록됨

분리수거 두 타깃의 독립 compile/link 빌드는 이번 통합에서도 완료하지 않았습니다. RC카 PlatformIO 빌드 결과와 혼동하지 마세요. 소스 계약 테스트의 진입점은 통합 저장소 루트에서 `python projects/recycling/tests/test_source_contract.py`입니다.

## 실물 검증 안전 순서

1. 모터/서보 전원을 분리한 상태에서 두 보드 UART와 LED부터 확인
2. logic analyzer 또는 serial log로 baud와 1-byte 사용자 인덱스 확인
3. current-limited supply에서 서보 1개, 스테퍼 1개씩 순차 연결
4. IR ADC와 초음파 pulse width를 실제 계측값과 대조
5. 구동부에 손이나 물체가 끼이지 않는 fixture에서 전체 state transition 확인
6. 만재 threshold와 메시지를 실제 거리 fixture로 확인

실물 구동, 고전류 연결, 모터/서보 동작은 별도 안전 확인 없이 자동 수행하면 안 됩니다.

## 정적 저장소 검증

저장소 정리 시 다음 항목을 검사했습니다.

- 각 보드 앱의 quoted include가 해당 support 또는 vendor/표준 헤더로 해석되는지
- 선택한 구현 파일의 호출 closure에 필요한 course support 구현이 포함되는지
- 원 사용자 바코드, 학생 식별자와 실명 패턴이 없는지
- 모든 Markdown/C/H 파일이 UTF-8로 decode되는지
- Unicode replacement character와 반복 물음표 손상이 없는지

이 검사는 compile/link 또는 hardware 검증을 대체하지 않습니다.
