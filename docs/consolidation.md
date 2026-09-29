# 통합 근거와 원본 보존 / Consolidation and provenance

## 로컬 통합 방식

공개 embedded 포크에서 새 로컬 브랜치 `consolidation/embedded-local-20260929`를 만들고, 비공개 recycling의 `main`을 로컬 파일 경로로 fetch했습니다. 두 부모를 갖는 subtree import 커밋을 만든 다음 중복을 정리했습니다. squash, history rewrite, 원격 push, 공개 전송이나 가시성 변경은 수행하지 않았습니다.

- embedded 원본: `d02d6d01d80dce9fb510901e1de003cc78785adf`
- recycling 원본: `702d06380c1fbecfebd83264d048751a8a63e260`
- 이력 병합: `e89d8b8` (부모는 위 두 원본 커밋)
- 로컬 보존 브랜치: `preservation/embedded-before-consolidation`, `preservation/recycling-source-20260929`
- 두 원래 `main` 브랜치는 그대로 보존합니다. recycling 원본 checkout은 수정하지 않습니다.

## 정본 선택

| 이전 경로 | 통합 정본 | 선택 근거 |
|---|---|---|
| embedded `LAB/final_first_board.c` | [보드 1 앱](../projects/recycling/firmware/board-1/app/main.c) | 합성 사용자 fixture, 수정된 문자열 용량과 사용자 수 기반 반복 범위가 있는 기존 정리본 |
| embedded `LAB/final_second_board.c` | [보드 2 앱](../projects/recycling/firmware/board-2/app/main.c) | 합성 이름과 수신 인덱스 범위 검사가 있는 기존 정리본 |
| recycling `firmware/board-2/support/*` 20개 | [루트 lib](../lib) 같은 파일명 | 주석·공백을 제외한 C 토큰 일치; 개인정보 치환 주석을 정본에 반영 |
| recycling `docs/flowcharts/recycling.png`, `.svg` | [루트 도식](flowcharts/recycling.png), [SVG](flowcharts/recycling.svg) | 바이트·SHA-256 일치 |
| 두 루트 README | [과목 안내](../README.md), [구현 안내](../projects/recycling/README.md) | 전체 이야기는 루트 한 곳, 세부 흐름·소스 연결은 컴포넌트 |
| embedded `README.original.md` | 원본 이력 | 두 줄짜리 초기 소개는 유지할 별도 문서가 아니므로 현재 트리에서 제외 |
| recycling의 나머지 파일 | `projects/recycling/<원래 경로>` | 보드 1 변형, 앱, 회로 이미지, 귀속과 기술 기록 보존 |

두 재활용 앱은 원본 recycling HEAD와 바이트가 같습니다. 옛 LAB 앱과 완전히 같다는 이유로 삭제한 것이 아닙니다. 개인정보 치환과 기존 방어가 있는 버전을 정본으로 선택했으며, 이전 버전은 원래 커밋으로 조회할 수 있습니다.

## 남긴 차이와 중복

보드 1의 `PUSH_PULL`/`NPUPD`와 공용 `PUSHPULL`/`NOPUPD`는 API 차이입니다. `ecTIM2.c`의 주기 계산, ADC 설정, PWM 설정과 GPIO 구현도 다릅니다. 보드 1의 9개 C 구현과 12개 헤더를 그대로 보존합니다. 보드 2는 루트 lib 중 8개 C 구현과 12개 헤더를 사용합니다. 필요한 compile unit을 삭제해 중복이 줄어든 것처럼 보이게 하지 않았습니다.

보드 1의 `ecICAP2.h`와 `ecUART2.h`는 공용 선언과 중복되지만, 따옴표 include가 같은 폴더의 보드별 `ecSTM32F4v2.h`, `ecGPIO2.h`, `ecRCC2.h`를 선택합니다. 이 두 헤더만 루트로 이동하면 다른 보드의 include closure가 섞이므로 의도적으로 유지합니다. 두 변형의 계약이 실제로 바뀔 때 각 보드 타깃에서 확인해야 합니다.

루트 `ecUART2_simple.c/.h`는 기존 대체 구현입니다. RC 빌드는 이를 제외하며 이번 과목 통합에서 새 정본으로 승격하지 않습니다. 실습 파일은 다른 학습 단계의 예제이므로 최종 앱과 함께 연결하지 않습니다.

전체 이전 경로→새 경로, 파일 해시, 정확한 커밋과 명령 결과는 checkout 옆의 `embedded-receipt.json` 및 `embedded-receipt.md`에 기록합니다.

## 원본 조회와 이관

다음 명령은 로컬 조회이며 과거 파일 내용에 비공개 정보가 있을 수 있습니다. 공개 로그에 원문을 출력하지 마세요.

```sh
git log preservation/recycling-source-20260929
git diff --stat preservation/embedded-before-consolidation HEAD
git merge-base --is-ancestor preservation/recycling-source-20260929 HEAD
```

권장 최종 목적지는 기존 비공개 recycling 저장소입니다. 소유자가 선택한 후, 리드는 이 통합 브랜치를 로컬 경로로 recycling에 fetch해 검토할 수 있습니다. 원본 recycling HEAD가 통합 HEAD의 조상이므로 이력 손실 없이 fast-forward 가능한 구조입니다. 기존 공개 embedded 포크는 그대로 보존합니다. 공개 포크의 가시성 전환 가능성에 의존하지 않습니다.

## English

The local integration preserves both original heads as parents of a non-squashed subtree import. Original main branches remain unchanged. Recycling is imported under `projects/recycling`, then its board-2 support is consolidated with token-identical root `lib` implementations. Sanitized comments are retained. Both recycling applications remain byte-identical to the imported source head; they supersede older LAB snapshots because the existing curated versions include privacy substitutions and bounds-related changes.

Board 1 retains its distinct 9 implementation files and 12 headers. Its API names, timer calculations and peripheral setup differ. Two duplicated declaration headers are intentionally retained because quoted includes must resolve within the board-1 support directory. Board 2 uses the specified 8 root implementation files and 12 headers, rather than linking all library alternatives.

Two identical recycling diagrams now have one root copy. The bilingual root tells the course story; component guides explain implementation details. Original attribution, photographs, circuit documentation and source history remain available. Exact per-file mappings, hashes and validation commands are in the adjacent local receipts.

**Destination recommendation:** use the existing private recycling repository for the complete course integration and preserve the public embedded fork. This merged history is private regardless of the original checkout's public remote. No remote operation is authorized by this preparation, and current-file sanitization does not sanitize historical commits. See [NOTICE](../NOTICE.md).
