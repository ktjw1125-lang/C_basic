#include <stdio.h>
#include <windows.h>

// 시리얼 포트 설정
// 사용하고자 하는 포트 번호로 변경하세요.
// COM10 이상인 경우 "\\\\.\\COM10" 형식으로 사용해야 합니다.
#define SERIAL_PORT_NAME "COM6"
#define BAUD_RATE CBR_115200

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };
    char tx_buffer[] = "Hello, Serial!\r\n";
    char rx_buffer[256] = { 0 };
    DWORD dwBytesWritten = 0;
    DWORD dwBytesRead = 0;

    // 1. 시리얼 포트 열기
    hSerial = CreateFile(
        TEXT(SERIAL_PORT_NAME),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_FILE_NOT_FOUND) {
            printf("ERROR: Serial port '%s' not found. (Error Code: %lu)\n", SERIAL_PORT_NAME, dwError);
        }
        else if (dwError == ERROR_ACCESS_DENIED) {
            printf("ERROR: Serial port '%s' is already in use or access is denied. (Error Code: %lu)\n", SERIAL_PORT_NAME, dwError);
        }
        else {
            printf("ERROR: Could not open serial port '%s'. (Error Code: %lu)\n", SERIAL_PORT_NAME, dwError);
        }
        return 1;
    }

    printf("Serial port %s opened successfully.\n", SERIAL_PORT_NAME);

    // 2. 시리얼 포트 설정 가져오기
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("ERROR: Could not get serial port state. (Error Code: %lu)\n", GetLastError());
        CloseHandle(hSerial);
        return 1;
    }

    // 3. 시리얼 포트 설정 변경
    dcbSerialParams.BaudRate = BAUD_RATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("ERROR: Could not set serial port state. (Error Code: %lu)\n", GetLastError());
        CloseHandle(hSerial);
        return 1;
    }

    printf("Serial port configured (BaudRate: %d, ByteSize: %d, Parity: %d, StopBits: %d)\n",
        dcbSerialParams.BaudRate,
        dcbSerialParams.ByteSize,
        dcbSerialParams.Parity,
        dcbSerialParams.StopBits);

    // 4. 타임아웃 설정
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("ERROR: Could not set timeouts. (Error Code: %lu)\n", GetLastError());
        CloseHandle(hSerial);
        return 1;
    }

    // 5. 시리얼 포트로 데이터 쓰기
    if (WriteFile(hSerial, tx_buffer, sizeof(tx_buffer) - 1, &dwBytesWritten, NULL)) {
        printf("Successfully wrote %ld bytes to serial port.\n", dwBytesWritten);
    }
    else {
        printf("ERROR: Could not write to serial port. (Error Code: %lu)\n", GetLastError());
    }

    // 6. 시리얼 포트에서 데이터 읽기
    printf("Waiting for data from serial port...\n");
    Sleep(2000);

    if (ReadFile(hSerial, rx_buffer, sizeof(rx_buffer) - 1, &dwBytesRead, NULL)) {
        if (dwBytesRead > 0) {
            rx_buffer[dwBytesRead] = '\0';
            printf("Received %ld bytes: %s\n", dwBytesRead, rx_buffer);
        }
        else {
            printf("No data received.\n");
        }
    }
    else {
        printf("ERROR: Could not read from serial port. (Error Code: %lu)\n", GetLastError());
    }

    // 7. 시리얼 포트 닫기
    CloseHandle(hSerial);
    printf("Serial port closed.\n");

    return 0;
}