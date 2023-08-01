# Car With Sensors
# Features
1. 블루투스 통신을 할 수 있는 파이썬 코드
2. 블루투스로 명령어를 받아서 작동하는 아두이노 코드

# Source
- 메인 프로젝트 소스 파일은 ./dev/car/
- ./dev/bt/ : 아두이노 Bluetooth Serial 통신 테스트용 파일
- ./python/ : 컴퓨터와 아두이노 사이에 블루투스 통신 파일
  - address.py: 블루투스 장치의 주소를 알아냄
  - bt.py: pybluez2 라이브러리를 사용해서 블루투스 신호를 보내고 받음

- (deprecated) ./include/SerialPrintf.cpp: 시리얼 통신 중 stdio.h의 printf 함수와 유사한 기능을 Serial.print로 하도록 하는 함수


# Bluetooth Command
## 1. Stop
  - 양쪽 모터의 작동을 멈춤
  - 모든 모터 작동 예약을 취소함
  - stop
## 2. Go
  - 주어진 방향으로 (ms) 동안 이동함
  - go (direction) (ms)
    - ms: Optional
    - direction
      - forward
      - backward

## 3. Speed
  - speed ( value 0 ~ 255 )
    - 양쪽 모터의 속력이 설정됨
    - 150 이상으로 설정할 것을 권장함 (기본값: 255)

## 4. Turn
  - 주어진 방향으로 포인트턴을 함
  - turn (direction)
    - direction
      - left
      - right

## 5. Sensor
  - TODO

# TODO
1. 적외선 센서 기능 만들기
2. 초음파 센서 기능 만들기
