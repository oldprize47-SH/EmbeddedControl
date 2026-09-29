# 귀속 및 출처 경계

## 원칙

- 이 저장소는 **2인 팀의 공동 학술 프로젝트**를 포트폴리오 열람용으로 정리한 것입니다.
- 공동 응용 코드와 course/shared support의 공개 재배포 허가가 확인되기 전까지 GitHub 저장소 자체는 **비공개**로 유지합니다. 여기서 `공개본`은 개인정보를 제거한 공개 준비본을 뜻하며, 현재 원격 가시성을 뜻하지 않습니다.
- README의 구성 설명에는 원보고서에 기재된 공동 저자 Sangheon Park와 방준혁의 이름 및 확인된 담당 업무를 함께 표기합니다. 학생 식별번호와 개인 fixture는 계속 제외하며, 지원 코드의 익명화된 주석은 유지합니다.
- support 코드는 수업용 starter/HAL, 팀별 수정과 개인 실습 코드가 혼합된 계보입니다.
- 원 자료에서 적용 가능한 명시적 재배포 라이선스를 확인하지 못했으므로, 이 저장소는 해당 파일에 새 라이선스를 부여하지 않습니다.
- 파일을 이 저장소에 포함했다는 사실은 제3자에게 복제·수정·재배포 권한을 부여한다는 뜻이 아닙니다.

## 파일별 provenance

| 공개 경로 | 분류 | 확인된 출처/계보 | 공개본 처리 |
|---|---|---|---|
| `firmware/board-1/app/main.c` | 공동 응용 코드 | 최종 2인 팀 firmware의 공개용 sanitized Board 1 앱 | 사용자 fixture 치환본; 단독 저작 주장 없음 |
| `firmware/board-2/app/main.c` | 공동 응용 코드 | 최종 2인 팀 firmware의 공개용 sanitized Board 2 앱 | 이름 fixture 및 bounds 방어가 포함된 공개본 |
| `firmware/board-1/support/ecADC2.c` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecADC2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecEXTI2.h` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecGPIO2.c` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecGPIO2.h` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecICAP2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecPinNames.c` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecPinNames.h` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecPWM2.c` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecPWM2.h` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecRCC2.c` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecRCC2.h` | course/shared support | 팀원 측 course-library 변형; 학생 이름은 공개본 주석에서 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecStepper.c` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecStepper.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecSTM32F4v2.h` | course/shared support | iiLAB/Embedded Controller course 집합 헤더; 팀원 측 수정 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecSysTick2.c` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecSysTick2.h` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecTIM2.c` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecTIM2.h` | course/shared support | SSSLAB 표기가 있는 수업용 support/student exercise 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecUART2.c` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-1/support/ecUART2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecADC2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecEXTI2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecGPIO2.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecGPIO2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecICAP2.c` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecICAP2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecPinNames.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecPinNames.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecPWM2.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecPWM2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecRCC2.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecRCC2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecStepper2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecSTM32F4v2.h` | course/shared support | Embedded Controller course 집합 헤더의 포트폴리오 소유자 측 변형 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecSysTick2.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecSysTick2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecTIM2.c` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecTIM2.h` | course/shared support | 포트폴리오 소유자 측 course-library 변형; 학생 이름은 역할 표기로 치환 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecUART2.c` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `firmware/board-2/support/ecUART2.h` | course/shared support | 수업용/shared support; 원 헤더에서 명확한 개인 license를 확인하지 못함 | 기능 코드는 원 변형 유지; 새 라이선스 없음 |
| `docs/images/circuit-diagram.png` | 공동 문서 이미지 | 팀 제출 보고서의 GitHub attachment에서 확보한 회로 연결도 | 팀 공동 자산으로 취급; 재사용 권리 별도 확인 |

## 제외한 원 자료

- 학번과 학생 실명이 포함된 원 보고서/PDF/Markdown
- 보고서 page render 및 중복 추출 이미지
- 원 사용자 바코드와 사용자 이름
- STM32 reference manual, scanner specification 등 제3자 PDF
- Fritzing custom-part `.fzp`/`.svg`와 license가 불명확한 부품 artwork
- 관련 없는 수업 lab, RC car 파일, 단순 UART 변형
- 취업용 다중 프로젝트 portfolio와 다른 프로젝트 이미지

## 변경 성격

- 응용 코드는 기존 공개용 sanitized 버전을 보드별 `app/main.c`로 재배치했습니다.
- support 코드는 최종 자료의 board별 변형에서 include/call closure에 필요한 파일만 복사했습니다.
- support 주석에 있던 학생 및 개인 이름은 공개 개인정보 최소화를 위해 역할 표기로만 치환했습니다. 함수, 레지스터 설정, 상수와 동작 코드는 변경하지 않았습니다.
- 회로 이미지는 EXIF/GPS가 없는 단일 PNG만 포함했습니다.

원본 저작자·수업 제공자·팀원의 권리가 우선하며, 구체적인 재사용 허가가 필요하면 해당 권리자에게 별도로 확인해야 합니다.
