# 분리수거 펌웨어 안내 / Recycling firmware guide

과목의 목표, 시제품 결과와 확인된 팀 역할은 [전체 프로젝트 안내](../../README.md)에 있습니다. 이 문서는 두 컨트롤러의 소스 연결과 재현할 때 확인할 항목을 다룹니다. 공개 재배포 제한은 [NOTICE](NOTICE.md)와 [귀속 기록](ATTRIBUTION.md)을 따릅니다.

## 한국어

### 보드별 책임과 소스

| 타깃 | 앱 | 지원 구현 | 주요 역할 |
|---|---|---|---|
| 보드 1 | [main.c](firmware/board-1/app/main.c) | [전용 support](firmware/board-1/support) | 사용자·제품 바코드, 스테퍼 2개, 서보, IR 투입 감지, LED, 사용자 인덱스 송신 |
| 보드 2 | [main.c](firmware/board-2/app/main.c) | [루트 lib](../../lib) 중 지정한 8개 C 파일 | 초음파 3개 입력 캡처, 사용자 포인트와 Bluetooth/UART 상태 메시지 |

두 보드는 별도 실행 파일입니다. 보드 1은 매크로 이름, 타이머 계산, GPIO·ADC·PWM 구성이 다르므로 루트 `lib`와 함께 링크하면 안 됩니다. 보드 2의 기존 지원 파일 20개는 루트 `lib`와 코드 토큰이 같아 하나로 합쳤고, 개인정보를 치환한 주석을 정본에 유지했습니다. [통합 기록](../../docs/consolidation.md)에 선택 근거가 있습니다.

### 입력에서 완료까지

1. 보드 1의 USART6는 바코드 입력을 받습니다. 등록 사용자 입력 후 제품 바코드로 분류 항목을 선택합니다.
2. 스테퍼·서보와 IR 감지 상태가 투입 순서를 구성하고 LED가 현재 상태를 표시합니다.
3. 완료 처리에서 USART1으로 사용자 인덱스 1바이트를 보드 2에 보냅니다.
4. 보드 2는 수신 인덱스의 배열 범위를 확인한 후 포인트를 갱신하고 USART6로 상태를 보냅니다.
5. 별도의 초음파 입력 캡처 경로는 세 수거함의 거리와 만재 조건을 감시합니다.

UART 설정은 보드 1 스캐너 USART6 115200 bps, 보드 간 USART1 9600 bps, 보드 2 상태 USART6 9600 bps입니다. USART2는 디버그/stdio 경로입니다. 이 값들은 현재 소스를 읽기 위한 안내이며 검증된 배선 지도가 아닙니다.

![보관된 회로 연결도](docs/images/circuit-diagram.png)

보고서와 소스의 핀·UART 표기가 일부 다릅니다. 이 회로도만으로 다시 배선하지 말고 보드별 소스와 실제 연결을 대조해야 합니다. [시스템 흐름](../../docs/flowcharts/recycling.png) · [벡터 도식](../../docs/flowcharts/recycling.svg)

### 현재 앱을 정본으로 선택한 이유

옛 `LAB` 앱 사본 대신 이 디렉터리의 앱만 유지합니다. 보드 1에는 합성 사용자 fixture, 문자열 버퍼 크기 및 사용자 수 기반 반복 범위가 반영되어 있고, 보드 2에는 합성 이름과 수신 인덱스 범위 검사가 있습니다. 이번 통합에서는 두 앱의 바이트를 바꾸지 않았습니다. 옛 앱은 보존 브랜치와 원본 이력에서 확인할 수 있습니다.

### 재현과 알려진 한계

[BUILDING.md](BUILDING.md)는 보드별 소스 목록, include 경로와 필요한 vendor 환경을 설명합니다. [기술 요약](docs/기술-요약.md)은 인터럽트·센서·상태 처리의 세부 기록입니다. 루트에서 `python projects/recycling/tests/test_source_contract.py`로 소스 구성을 검사할 수 있습니다.

블로킹 지연과 공유 상태, 프레이밍·체크섬·최신성 정보가 없는 1바이트 통신, 센서 timeout·보정의 부족이 남아 있습니다. 초음파 세 개 동시 사용 시 보고된 오류를 단일 원인으로 단정하지 않습니다. 알려진 바코드와 둥근 용기·캔을 이용한 수업 시연 범위를 넘어선 정확도·신뢰성 수치는 없습니다. 빌드·정적 검사는 새 실물 시험이 아니며 이번 통합에서 보드를 구동하지 않았습니다.

## English

### Source selection

[Board 1](firmware/board-1/app/main.c) handles barcode input, two steppers, the servo entrance, infrared deposit detection, LEDs and user-index transmission. Its [support variant](firmware/board-1/support) stays separate: macro names, timer calculations and peripheral configuration differ from the root library.

[Board 2](firmware/board-2/app/main.c) handles three ultrasonic capture inputs, user points and Bluetooth/UART status. Its former 20 support files have identical C tokens to the corresponding root [lib](../../lib) files. There is now one maintained implementation, retaining sanitized comments. Select the eight C files listed in [BUILDING.md](BUILDING.md); never combine the two boards into one executable.

### Reading the control paths

Follow board 1 USART6 reception through registered-user recognition, product-category selection, stepper/servo operation and infrared deposit detection. Completion sends a one-byte user index over USART1. Board 2 checks the index range, updates points and sends status through USART6, while timer input capture monitors bin distance independently.

The scanner uses USART6 at 115200 bps; the board link uses USART1 at 9600 bps; board 2 status uses USART6 at 9600 bps. USART2 supports debug/stdio. Some report/source pin and UART labels disagree, so the archived circuit diagram above is not a verified wiring guide.

The current apps replace the old `LAB` snapshots: board 1 already has synthetic user fixtures, revised string capacity and a user-count loop bound; board 2 already has synthetic names and an index bounds check. Both app files are unchanged in this integration. Earlier versions remain retrievable from preserved history.

### Reproduction limits

Run `python projects/recycling/tests/test_source_contract.py` from the root for source-selection and include checks. [Build notes](BUILDING.md) specify separate targets and vendor dependencies; [technical notes](docs/기술-요약.md) provide detailed source analysis. Blocking delays, shared state, a link without framing/checksum/freshness, and incomplete sensor timeout/calibration handling remain. The reported three-sensor errors do not have a single confirmed cause. The course demonstration covers registered items and constrained shapes, with no new accuracy or reliability measurements. No hardware was flashed or operated during consolidation.
